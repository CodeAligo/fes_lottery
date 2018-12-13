package main

import (
	"fmt"
	"net/http"
)

var (
	Api = "http://10.92.96.233/send"
)

func SetServer() {
	fmt.Print("Enter server location: ")
	fmt.Scanln(&Api)
	Api = "http://" + Api + "/send"
}

func SendTruthNumbers() {
	format := Api + "?number1=%d&number2=%d&number3=%d&number4=%d"
	address := fmt.Sprintf(format, TruthNumbers[0], TruthNumbers[1], TruthNumbers[2], TruthNumbers[3])
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
}
