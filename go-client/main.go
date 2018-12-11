package main

import (
	"fmt"

	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/sqlite"
)

var db *gorm.DB

func init() {
	var err error
	db, err = gorm.Open("sqlite3", "theworldisallone.db")
	if err != nil {
		panic(err)
	}

	db.AutoMigrate(&Admin{}, &Lottery{})

}

func main() {
	admins := GetAdmins()
	if len(admins) == 0 {
		fmt.Print("There's no admin here. Do you want to add an new admin? (y/n) ")
		answer := ""

		fmt.Scan(&answer)
		if answer == "y" || answer == "yes" {
			RegisterAdmin().Create()
		} else if answer == "n" || answer == "no" {
			fmt.Println("OK, Bye.")
			return
		} else {
			fmt.Println("Ha? If you are just bored now, go outside and get some foods.")
		}
		fmt.Println("end")

	} else {
		fmt.Println("OK")
	}
}
