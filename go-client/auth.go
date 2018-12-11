package main

import (
	"crypto/sha1"
	"fmt"
	"syscall"

	"golang.org/x/crypto/ssh/terminal"
)

func GetAdmins() (admins []Admin) {
	db.First(&admins)
	return
}

func (admin Admin) Create() {
	admin.Password = Encrypt(admin.Password)
	db.Create(&admin)
}

func Encrypt(plaintext string) (cryptext string) {
	cryptext = fmt.Sprintf("%x", sha1.Sum([]byte(plaintext)))
	return
}

func RegisterAdmin() (admin Admin) {
	var bytePass []byte
	for {
		fmt.Print("Enter Your ID: ")
		fmt.Scanln(&admin.ID)
		fmt.Print("Enter Your Name: ")
		fmt.Scanln(&admin.Name)
		fmt.Print("Enter Your Password: ")
		bytePass, _ = terminal.ReadPassword(int(syscall.Stdin))
		for {
			fmt.Print("Type Again: ")
			retype, _ := terminal.ReadPassword(int(syscall.Stdin))
			if string(bytePass) == string(retype) {
				return
			}
			fmt.Print("Wrong. Type Again: ")
		}

		answer := ""
		fmt.Printf("ID: %s, Name: %s. Is it you? (y/n) ")
		fmt.Scan(&answer)
		if answer == "n" {
			fmt.Println("OK! Let's Do it Again.")
		} else {
			fmt.Println("Register Complete.")
		}
	}

	fmt.Println()

	admin.Password = string(bytePass)
	return
}
