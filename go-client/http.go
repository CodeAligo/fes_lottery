package main

import (
	"fmt"
	"net/http"
	"time"
)

var (
	Api = "http://10.92.96.233/send"
)

func init() {
	domain := ""
	fmt.Print("Server(blank for default): ")
	fmt.Scanln(&domain)
	if domain != "" {
		SetServer(domain)
	}
	format := Api + "?NextTime=%d"

	fmt.Print("NextTime(blank for an hour later): ")
	nextTime := 0
	fmt.Scan(&nextTime)
	if nextTime == 0 {
		nextTime = time.Now().Hour() + 1
	}

	link := fmt.Sprintf(format, nextTime)

	resp, err := http.Get(link)
	if err != nil {
		fmt.Println(err)
	}

	if resp.StatusCode == 200 {
		fmt.Println("NextTime was set", nextTime)
	} else {
		fmt.Println("Failed.")
	}
}

func SetServerConsole() {
	fmt.Print("Enter server location: ")
	domain := ""
	fmt.Scanln(&domain)
	SetServer(domain)
}

func SetServer(domain string) {
	Api = "http://" + domain + "/send"
}

func SendNumber() {
	format := Api + "?number1=%d&number2=%d&number3=%d&number4=%d&NumWinners=%d&NextTime=%d"
	numWinners := len(GetWinners())
	now := time.Now()
	address := fmt.Sprintf(format, TruthNumbers[0], TruthNumbers[1], TruthNumbers[2], TruthNumbers[3], numWinners, now.Hour()+1)
	resp, err := http.Get(address)
	if err != nil {
		fmt.Println(err)
		return
	}
	if resp.StatusCode == 200 {
		fmt.Println("Sending Success.")
	} else {
		fmt.Println("Somethings Wrong.")
	}

	SendRemainWinners()
}

func SendRemainWinners() {
	format := Api + "?RemainWinners=%d"
	remainWinner := GetRemainWinners()
	link := fmt.Sprintf(format, remainWinner)

	resp, err := http.Get(link)
	if err != nil {
		fmt.Println("Error:", err)
	}

	if resp.StatusCode == 200 {
		fmt.Println("Sending Success.")
	} else {
		fmt.Println("Somethings Wrong")
	}

	if remainWinner == 0 {
		fmt.Println("Remain Winners == 0, so starting new session...")
		NewSession()
	}
}

func SendMessage() {
	format := Api + "?Msg=%s"
	message := ""
	fmt.Print("Enter a message to send to a server: ")
	fmt.Scanln(&message)
	link := fmt.Sprintf(format, message)
	resp, err := http.Get(link)
	if err != nil {
		fmt.Println("Error:", err)
	}

	if resp.StatusCode == 200 {
		fmt.Println("Success.")
	} else {
		fmt.Println("Failed.")
	}
}
