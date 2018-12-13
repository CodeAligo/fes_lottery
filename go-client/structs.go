package main

import (
	"time"
)

// Admin쨩이에요
type Admin struct {
	ID       string `gorm:"primary_key"`
	Name     string
	Password string // 암호화 되어서 저장될 거예요
}

type Lottery struct {
	ID       int    `gorm:"AUTO_INCREMENT;primary_key"`
	Owner    string // 소유자의 학번 ex) 2826
	Passcode string // 8자리의 패스코드
	Date     time.Time

	Winned bool `gorm:"default:false"`
	Active bool `gorm:"default:true"`

	// 아니 왜 sqlite3에는 배열이 없는거죠?
	Number1 int
	Number2 int
	Number3 int
	Number4 int
}
