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
		for {
			fmt.Print("\nEnter Your Password: ")
			bytePass, _ = terminal.ReadPassword(int(syscall.Stdin))
			fmt.Print("\nType Again: ")
			retype, _ := terminal.ReadPassword(int(syscall.Stdin))
			if string(bytePass) == string(retype) {
				break
			}
			fmt.Print("\nWrong. Type Again: ")
		}

		if AskYesOrNo("\nID: %s, Name: %s. Is it you?", admin.ID, admin.Name) {
			fmt.Println("Success.")
			break
		} else {
			fmt.Println("Let's try again.")
		}

	}

	fmt.Println()

	admin.Password = string(bytePass)
	return
}

func Login(ID, password string) (ok bool) {
	var admin Admin
	admin.ID = ID
	db.Find(&admin)
	if admin.Password == Encrypt(password) {
		currentAdmin = admin
		ok = true
	}
	return
}

func LoginConsole() {
	var ID string
	fmt.Println("\n-Logging in-")
	fmt.Print("ID: ")
	fmt.Scanln(&ID)
	fmt.Print("Password: ")
	bytePass, _ := terminal.ReadPassword(int(syscall.Stdin))

	ok := Login(ID, string(bytePass))
	if ok {
		fmt.Printf("\nLogin Success. Welcome %s.\n", currentAdmin.Name)
	} else {
		fmt.Println("\nLogin Failed.")
	}
}

// 伊織ちゃん　このみさん　桃子先輩　響ちゃん　春香がか
