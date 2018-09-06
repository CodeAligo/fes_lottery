package main

import (
	"fmt"
	"html/template"
	"log"
	"net/http"
	"os"
	"strconv"
)

type Result struct {
	Numbers    []string
	NumWinners int
}

type Timer struct {
	NextTime int
	Msg      string
}

var (
	Port   string
	result Result
	timer  Timer
)

func logger(r *http.Request) {
	log.Println("Request:", r.URL.Path, "| From", r.RemoteAddr, "\nNextTime =", timer.NextTime, "NumWinners = ", result.NumWinners, "\n")
}

func resultHandler(w http.ResponseWriter, r *http.Request) {

	logger(r)
	t := template.Must(template.ParseFiles("template/result.html"))
	t.Execute(w, result)
}

func timerHandler(w http.ResponseWriter, r *http.Request) {
	logger(r)
	t := template.Must(template.ParseFiles("template/timer.html"))
	t.Execute(w, timer)
}

func sendHandler(w http.ResponseWriter, r *http.Request) {
	/*
		numbers := []string{}
		for n := 1; n <= 4; n++ {
			key := fmt.Sprint("number%d", n)
			numbers = append(numbers, r.FormValue(key))
			fmt.Println(r.FormValue(key))
		}

		copy(result.Numbers, numbers)
	*/

	fmt.Println(r.FormValue("number1"))

	w.WriteHeader(200)
	return

}

func main() {
	if len(os.Args) < 3 {
		fmt.Println("Usage: ./server port nexttime")
		fmt.Println("Eg.    ./server 8080 10")
		return
	}
	Port = ":" + os.Args[1]

	var err error
	timer.NextTime, err = strconv.Atoi(os.Args[2])
	if err != nil {
		fmt.Println("nexttime is not int")
		return
	}
	log.Println("Staring Server... Port", Port, "\n")

	result.Numbers = []string{"24", "09", "08", "07"}
	result.NumWinners = 25

	static := http.FileServer(http.Dir("static"))
	http.Handle("/static/", http.StripPrefix("/static/", static))
	http.HandleFunc("/result", resultHandler)
	http.HandleFunc("/timer", timerHandler)
	http.HandleFunc("/send", sendHandler)
	http.ListenAndServe(Port, nil)

}
