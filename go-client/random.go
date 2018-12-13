package main

import (
	"fmt"
	"math/rand"
	"sort"
	"syscall"
	"time"

	"golang.org/x/crypto/ssh/terminal"
)

func Winners() (lotteries []Lottery) {
	db.Where("number1 = ? AND number2 = ? AND number3 = ? AND number4 = ?", TruthNumbers[0], TruthNumbers[1], TruthNumbers[2], TruthNumbers[3]).Find(&lotteries)
	return
}

func PickNumbers() {
	rand.Seed(time.Now().UnixNano())
	numbersSlice := rand.Perm(Limit)[:4]
	sort.Ints(numbersSlice)
	for i, value := range numbersSlice {
		TruthNumbers[i] = value + 1
	}
}

func CheckOwner() {
	owner := ""
	fmt.Print("Owner: ")
	fmt.Scanln(&owner)

	var lotteries []Lottery
	format := "owner = ? AND winned = false AND number1 = ? AND number2 = ? AND number3 = ? AND number4 = ?"
	db.Where(format, owner, TruthNumbers[0], TruthNumbers[1], TruthNumbers[2], TruthNumbers[3]).Find(&lotteries)
	if len(lotteries) == 0 {
		fmt.Printf("Cannot find a correct lottery with Owner %s.\n", owner)
	} else if len(lotteries) == 1 {
		fmt.Print("Type passcode: ")
		bytePass, _ := terminal.ReadPassword(int(syscall.Stdin))

		if lotteries[0].Passcode == string(bytePass) {
			fmt.Println("\nAuth Success.")
			lotteries[0].Winned = true
			db.Table("lotteries").Save(&lotteries[0])

		} else {
			fmt.Println("\nAuth Failed.")
		}

	} else {
		fmt.Printf("There're %d lottries that has the truth numbers and you bought.\n", len(lotteries))

		n := 0
		for n < len(lotteries) {
			lotteries[n].Winned = true
			db.Save(&lotteries[n])
		}

	}
}

func SetNumbers() {
	fmt.Print("\nEnter Four Numbers: ")
	for i := 0; i < 4; i++ {
		var number int
		fmt.Scan(&number)
		if number > Limit { // 더 높으면...
			fmt.Printf("A number should be below %d.", Limit)
			i--
			continue
		}
		TruthNumbers[i] = number
	}
}

func NewSession() {
	var lotteries []Lottery
	db.Where("active = true").Find(&lotteries)

	n := 0
	for n < len(lotteries) {
		lotteries[n].Active = false
		db.Save(&lotteries[n])
		n++
	}

}
