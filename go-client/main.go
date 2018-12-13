package main

import (
	"fmt"
	"os"

	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/sqlite"
)

var db *gorm.DB
var currentAdmin Admin

// DB를 초기화 시킵니다.
func init() {
	var err error
	db, err = gorm.Open("sqlite3", "theworldisallone.db") // the world is all one !!
	if err != nil {
		panic(err)
	}

	// 자동으로 테이블을 생성
	db.AutoMigrate(&Admin{}, &Lottery{})

}

func main() {
	// Admin은 몇 명일까?
	admins := GetAdmins()
	if len(admins) == 0 { // 아무도 없으면
		if AskYesOrNo("It seems there's no admin. Do you want to register a new admin?") {
			RegisterAdmin().Create() // 회원가입
		} else {
			fmt.Println("OK, call me later.") // 뭐야 왜부름
			os.Exit(0)                        // 퇴장
		}
	}
	LoginConsole() // 로그인
	Interpreter()  // 명령어 이해하기

}
