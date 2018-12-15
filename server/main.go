package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"html/template"
	"log"
	"net/http"
	"os"
	"strconv"
)

// Data 구조체는 이번 회차의 결과를 저장합니다.
type Data struct {
	Numbers []string `json:"Numbers"` // Numbers 필드는 당첨 번호를 저장합니다.

	NumWinners    int `json:"NumWinners"` // NumWinners 필드는 당첨자가 몇명인지를 저장합니다.
	RemainWinners int `json:"RemainWinners"`

	NextTime *int   `json:"NextTime"` // NextTime 필드는 현재 시간부터 몇시까지 타이머를 구동할 건지를 저장합니다.
	Msg      string `json:"Msg"`      // Msg 필드는 안내 문구를 저장합니다. 필수는 아닙니다.
}

var data Data

// logger 함수는 요청이 들어올 시 요청에 따른 로그를 출력합니다.
func logger(r *http.Request) {
	log.Print("Request: ", r.URL.Path, " | From ", r.RemoteAddr,
		"\nNextTime = ", data.NextTime, ", NumWinners = ", data.NumWinners,
		", Numbers = ", data.Numbers, "\n")
}

// resultHandler 함수는 /result의 요청을 처리합니다.
func resultHandler(w http.ResponseWriter, r *http.Request) {

	logger(r)                                                       // 로그
	t := template.Must(template.ParseFiles("template/result.html")) // result.html 불러옴
	t.Execute(w, data)                                              // 응답
}

// timerHandler 함수는 /timer의 요청을 처리합니다.
func timerHandler(w http.ResponseWriter, r *http.Request) {
	logger(r)                                                      // 로그
	t := template.Must(template.ParseFiles("template/timer.html")) // timer.html 로드 및 파싱
	t.Execute(w, data)                                             // 응답
}

// ajaxHandler 함수는 JS의 ajax가 /ajax로 요청을 보내는 것을 처리합니다.
func ajaxHandler(w http.ResponseWriter, r *http.Request) {
	log.Print("ajax: NumWinners = ", data.NumWinners, " from ", r.RemoteAddr, "\n")
	marshalledJson, err := json.MarshalIndent(data, "", "\t")
	if err != nil {
		log.Println("Error! Marshaling Error!")
	}

	w.Write(marshalledJson)
	return
}

func redirectHandler(w http.ResponseWriter, r *http.Request) {
	url := "http://" + r.Host + "/timer"
	log.Println("Redirecting:", r.URL.Path, "-> /timer")
	http.Redirect(w, r, url, http.StatusMovedPermanently)
	return
}

func main() {
	var (
		logFile        string
		port           string
		nextTimeString string
	)

	// 커맨드라인 인자들
	flag.StringVar(&logFile, "log", "access.log", "A file for logging")
	flag.StringVar(&nextTimeString, "nt", "", "NextTime")
	flag.StringVar(&port, "port", "8080", "A port number for the Server")

	flag.Parse() // 인자 파싱

	if nextTimeString != "" {
		nextTimeInt, err := strconv.Atoi(nextTimeString)

		if err != nil {
			fmt.Println("NextTime should be int.")
			os.Exit(1)
		}

		data.NextTime = &nextTimeInt

	}

	port = ":" + port // ":" + port

	fpLog, err := os.OpenFile(logFile, os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0666) // 있으면 사용, 없으면 생성
	if err != nil {
		panic(err)
	}
	defer fpLog.Close()

	log.Println("Server Log is in", logFile) // Server 시작 로그

	log.SetOutput(fpLog)                               // 로그를 파일에 기록
	log.Print("Staring Server... Port ", port, "\n\n") // Server 시작 로그

	data.Numbers = []string{"24", "09", "08", "07"} // Default Value
	data.NumWinners = 25                            // Default Value
	data.RemainWinners = 24

	static := http.FileServer(http.Dir("static"))                 // Static 파일의 디렉터리: ./static
	http.Handle("/static/", http.StripPrefix("/static/", static)) // /static의 요청들을 static 디렉터리 파일들로 보냄
	http.HandleFunc("/ajax", ajaxHandler)                         // /ajax -> ajaxHandler
	http.HandleFunc("/result", resultHandler)                     // /result -> resultHandler
	http.HandleFunc("/timer", timerHandler)                       // /timer -> timerHandler
	http.HandleFunc("/send", sendHandler)                         // /send -> sendHander
	http.HandleFunc("/", redirectHandler)                         // 편의상 / -> /timer

	err = http.ListenAndServe(port, nil) // localhost:Port로 서버 실행
	if err != nil {
		panic(err)
	}

}
