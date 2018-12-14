package main

import (
	"fmt"
	"time"
)

func AskYesOrNo(question string, a ...interface{}) bool {
	for {
		fmt.Printf("\n"+question+" (y/n) ", a...)
		answer := ""
		fmt.Scanln(&answer)

		switch answer {
		case "y", "yes", "응", "네", "ㅇ":
			return true
		case "n", "no", "아니", "ㄴ":
			return false
		default:
			continue
		}
	}
}

func Interpreter() {
	for {
		if currentAdmin.ID == "" {
			fmt.Println("Please Login first.")
			LoginConsole()
			continue
		}

		fmt.Print("> ")
		input := ""
		fmt.Scanln(&input)

		switch input {
		case "register":
			RegisterAdmin().Create()
		case "logout":
			currentAdmin = Admin{}

		case "lottery":
			NewLotteryConsole()
		case "status":
			PrintStatus()
		case "win":
			CheckOwner()
		case "pick":
			PickNumbers()
			fmt.Println(TruthNumbers)
		case "set":
			SetNumbers()
		case "server":
			SetServerConsole()
		case "sendnum":
			SendNumber()

		case "newsess":
			NewSession()

		case "exit":
			return
		case "help":
			fmt.Println("register, logout, lottery, status, pick, win, server, sendnum, newsess, exit")
		case "":
			continue
		default:
			fmt.Println("Unknown Command. Please enter 'help' to know commands.")
		}
	}
}

func PrintStatus() {
	var activeLotteries, allLotteries []Lottery
	db.Where("active = true").Find(&activeLotteries)
	db.Find(&allLotteries)

	format := "\nCurrent Admin: %s\nActive Lotteries: %d(All %d)\nTime Now: %v\n"
	fmt.Printf(format, currentAdmin.Name, len(activeLotteries), len(allLotteries), time.Now().Local())
}
