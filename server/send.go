package main

import (
	"fmt"
	"log"
	"net/http"
	"strconv"
)

// sendHandler 함수는 /send로 들어온 인자를 저장합니다.
func sendHandler(w http.ResponseWriter, r *http.Request) {
	var err error // Error Handling을 위한 변수

	if r.FormValue("number1") != "" { // "number1" 필드가 있을 시
		numbers := []string{} // 인자를 저장하기 위한 슬라이스

		for n := 1; n <= 4; n++ { // 1-4까지 반복
			key := fmt.Sprintf("number%d", n)           // number + n
			numbers = append(numbers, r.FormValue(key)) // key라는 이름의 필드 값을 불러와 numbers에 합침
		}

		copy(data.Numbers, numbers) // numbers의 값을 data.Numbers로 복사
	}

	if numWinners := r.FormValue("NumWinners"); numWinners != "" { // 만약 "NumWinners" 필드가 있을 시
		data.NumWinners, err = strconv.Atoi(numWinners) // int로 변환

		if err != nil { // str를 int로 바꾸는 중 에러 발생 시
			log.Println("Error: NumWinners cannot be int") // 알림
			w.WriteHeader(400)                             // http: 잘못된 요청
			return
		}
	}

	if remainWinners := r.FormValue("RemainWinners"); remainWinners != "" {
		data.RemainWinners, err = strconv.Atoi(remainWinners)

		if err != nil {
			log.Println("Error: RemainWinners cannot be int")
			w.WriteHeader(400)
			return
		}
	}

	if nextTime := r.FormValue("NextTime"); nextTime != "" { // "NextTime" 필드가 있을 시
		nextTimeInt, err := strconv.Atoi(nextTime) // str -> int

		if err != nil { // int로 변환 시 에러 발생 시
			log.Println("Error: NextTime cannot be int") // 알림
			w.WriteHeader(400)                           // http: 잘못된 요청
			return
		}

		data.NextTime = &nextTimeInt
	}

	if msg := r.FormValue("Msg"); msg != "" {
		data.Msg = msg
	}

	logger(r) // 로그

	w.WriteHeader(200) // http: OK
	return

}
