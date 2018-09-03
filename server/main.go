package main

import (
	//"github.com/jasonlvhit/gocron"
	//"github.com/jinzhu/gorm"
	//_ "github.com/lib/pq"
	"html/template"
	"log"
	//"math/rand"
	"net/http"
	"os"
	//"time"
)

var (
	Port string
	//Db     *gorm.DB
	result Result
)

/*
func init() {
	Db, err := gorm.Open("postgres", "user=golang dbname=fes_lottery password=ilovegolang sslmode=disable")
	if err != nil {
		panic(err)
	}

	Db.AutoMigrate(&Student{}, &Ticket{})

}

func picker() {
	result.Number = []int{}
	rand.Seed(time.Now().UnixNano())
	r := rand.Perm(25)

	n := 0
	for n < 4 {
		result.Number = append(result.Number, r[n]+1)
		n++
	}
}
*/

func index(w http.ResponseWriter, r *http.Request) {
	if r.URL.Path[1:] == "a" {
		result.Number = []int{24, 9, 8, 7}
		result.Winners = 25
	} else {
		result.Number = []int{}
		result.Winners = 0
	}

	log.Println("index Func")
	t := template.Must(template.ParseFiles("template/main.html"))
	t.Execute(w, result)
}

func main() {
	if len(os.Args) == 1 {
		panic("No port")
	}
	Port = ":" + os.Args[1]
	log.Println("Staring Server... Port", Port)

	http.HandleFunc("/", index)
	http.FileServer(http.Dir("./static"))
	http.ListenAndServe(Port, nil)

}
