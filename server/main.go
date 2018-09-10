package main

import (
	"flag"
	"fmt"
	"html/template"
	"log"
	"net/http"
	"os"
	"strconv"
)

// Result 구조체는 이번 회차의 결과를 저장합니다.
type Result struct {
	Numbers    []string // Numbers 필드는 당첨 번호를 저장합니다.
	NumWinners int      // NumWinners 필드는 당첨자가 몇명인지를 저장합니다.
}

// Timer 구조체는 당첨 번호까지 남은 시간을 저장합니다.
type Timer struct {
	NextTime int    // NextTime 필드는 현재 시간부터 몇시까지 타이머를 구동할 건지를 저장합니다.
	Msg      string // Msg 필드는 안내 문구를 저장합니다. 필수는 아닙니다.
}

var (
	result Result
	timer  Timer
)

// logger 함수는 요청이 들어올 시 요청에 따른 로그를 출력합니다.
func logger(r *http.Request) {
	log.Print("Request: ", r.URL.Path, " | From ", r.RemoteAddr,
		"\nNextTime = ", timer.NextTime, ", NumWinners = ", result.NumWinners,
		", Numbers = ", result.Numbers, "\n")
}

// resultHandler 함수는 /result의 요청을 처리합니다.
func resultHandler(w http.ResponseWriter, r *http.Request) {

	logger(r)                                                       // 로그
	t := template.Must(template.ParseFiles("template/result.html")) // result.html 불러옴
	t.Execute(w, result)                                            // 응답
}

// timerHandler 함수는 /timer의 요청을 처리합니다.
func timerHandler(w http.ResponseWriter, r *http.Request) {
	logger(r)                                                      // 로그
	t := template.Must(template.ParseFiles("template/timer.html")) // timer.html 로드 및 파싱
	t.Execute(w, timer)                                            // 응답
}

// sendHandler 함수는 /send로 들어온 인자를 저장합니다.
func sendHandler(w http.ResponseWriter, r *http.Request) {
	var err error // Error Handling을 위한 변수

	if r.FormValue("number1") != "" { // "number1" 필드가 있을 시
		numbers := []string{} // 인자를 저장하기 위한 슬라이스

		for n := 1; n <= 4; n++ { // 1-4까지 반복
			key := fmt.Sprintf("number%d", n)           // number + n
			numbers = append(numbers, r.FormValue(key)) // key라는 이름의 필드 값을 불러와 numbers에 합침
		}

		copy(result.Numbers, numbers) // numbers의 값을 result.Numbers로 복사
	}

	if numWinners := r.FormValue("NumWinners"); numWinners != "" { // 만약 "NumWinners" 필드가 있을 시
		result.NumWinners, err = strconv.Atoi(numWinners) // int로 변환

		if err != nil { // str를 int로 바꾸는 중 에러 발생 시
			log.Println("Error: NumWinners cannot be int") // 알림
			w.WriteHeader(400)                             // http: 잘못된 요청
			return
		}
	}

	if nextTime := r.FormValue("NextTime"); nextTime != "" { // "NextTime" 필드가 있을 시
		timer.NextTime, err = strconv.Atoi(nextTime) // str -> int

		if err != nil { // int로 변환 시 에러 발생 시
			log.Println("Error: NextTime cannot be int") // 알림
			w.WriteHeader(400)                           // http: 잘못된 요청
			return
		}
	}

	logger(r) // 로그

	w.WriteHeader(200) // http: OK
	return

}

// ajaxHandler 함수는 JS의 ajax가 /ajax로 요청을 보내는 것을 처리합니다.
func ajaxHandler(w http.ResponseWriter, r *http.Request) {
	log.Print("ajax: NumWinners = ", result.NumWinners, " from ", r.RemoteAddr, "\n")
	fmt.Fprint(w, result.NumWinners) // result.NumWinners만 응답
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
		logFile string
		port    string
	)

	// 커맨드라인 인자들
	flag.StringVar(&logFile, "log", "access.log", "A file for logging")
	flag.IntVar(&timer.NextTime, "nt", 10, "NextTime")
	flag.StringVar(&port, "port", "8080", "A port number for the Server")

	flag.Parse() // 인자 파싱

	port = ":" + port // ":" + port

	fpLog, err := os.OpenFile(logFile, os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0666) // 있으면 사용, 없으면 생성
	if err != nil {
		panic(err)
	}
	defer fpLog.Close()

	log.Println("Server Log is in", logFile) // Server 시작 로그

	log.SetOutput(fpLog)                               // 로그를 파일에 기록
	log.Print("Staring Server... Port ", port, "\n\n") // Server 시작 로그

	result.Numbers = []string{"24", "09", "08", "07"} // Default Value
	result.NumWinners = 25                            // Default Value

	static := http.FileServer(http.Dir("static"))                 // Static 파일의 디렉터리: ./static
	http.Handle("/static/", http.StripPrefix("/static/", static)) // /static의 요청들을 static 디렉터리 파일들로 보냄
	http.HandleFunc("/ajax", ajaxHandler)                         // /ajax -> ajaxHandler
	http.HandleFunc("/result", resultHandler)                     // /result -> resultHandler
	http.HandleFunc("/timer", timerHandler)                       // /timer -> timerHandler
	http.HandleFunc("/send", sendHandler)                         // /send -> sendHander
	http.HandleFunc("/", redirectHandler)                         // 편의상 / -> /timer

	http.ListenAndServe(port, nil) // localhost:Port로 서버 실행

}
