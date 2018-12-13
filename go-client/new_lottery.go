package main

import (
	"fmt"
	"math/rand"
	"sort"
	"syscall"
	"time"

	"golang.org/x/crypto/ssh/terminal"
)

var (
	Limit        = 35
	TruthNumbers [4]int
)

// 로터리를 만듭니다.
// 제일 길어요.
// 분리를 어떻게 시켜야할지...
func NewLotteryConsole() (lottery Lottery) {
	for {
		fmt.Print("Lottery Owner(ex 2826): ") // 소유자
		fmt.Scanln(&lottery.Owner)

		var numbersSlice []int
		if AskYesOrNo("Do you want to custom your numbers?") {
			fmt.Print("\nEnter Four Numbers: ")
			for i := 0; i < 4; i++ {
				var number int
				fmt.Scan(&number)
				if number > Limit { // 더 높으면...
					fmt.Printf("A number should be below %d.", Limit)
					i--
					continue
				}
				numbersSlice = append(numbersSlice, number)
			}
		} else {
			rand.Seed(time.Now().UnixNano()) // 시드 생성
			numbersSlice = rand.Perm(Limit)[:4]
			for i := range numbersSlice {
				numbersSlice[i] += 1
			}
		}

		sort.Ints(numbersSlice) // 소트
		var numbers [4]int
		copy(numbers[:], numbersSlice)
		lottery.PutNumbersIn(numbers)

		// 암호 만들기
		for {
			fmt.Print("\nEnter 8-digit Passcode: ")
			bytePass, _ := terminal.ReadPassword(int(syscall.Stdin))

			// 8자리 입력하라고
			if len(string(bytePass)) != 8 {
				fmt.Println("\nPasscode should be 8-digit.")
				continue
			}

			fmt.Print("\nType Again: ")
			retype, _ := terminal.ReadPassword(int(syscall.Stdin))

			if string(bytePass) == string(retype) {
				lottery.Passcode = string(bytePass)
				break
			}

			fmt.Println("\nWrong.")
		}

		// チェク
		format := "Owner: %s, Numbers: %v %v %v %v. Is it right?"
		if AskYesOrNo(format, lottery.Owner, lottery.Number1, lottery.Number2, lottery.Number3, lottery.Number4) {
			break
		} else {
			fmt.Println("\nOk, Let's try again.")
		}
	}
	fmt.Println()

	lottery.Date = time.Now().Local()
	lottery.Active = true
	lottery.Winned = false
	db.Create(&lottery)
	return
}
