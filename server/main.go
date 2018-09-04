package main

import (
	"html/template"
	"log"
	"net/http"
	"os"
)

type Result struct {
	Number  []int
	Winners int
}

var (
	Port   string
	result Result
)

func index(w http.ResponseWriter, r *http.Request) {
	result.Number = []int{}
	result.Winners = 0

	if r.URL.Path[1:] == "a" {
		result.Number = []int{24, 9, 8, 7}
		result.Winners = 25
	}

	log.Println("Request:", r.URL.Path, "| From", r.RemoteAddr)
	t := template.Must(template.ParseFiles("template/main.html"))
	t.Execute(w, result)
}

func main() {
	if len(os.Args) == 1 {
		panic("No port")
	}
	Port = ":" + os.Args[1]
	log.Println("Staring Server... Port", Port)

	static := http.FileServer(http.Dir("static"))
	http.Handle("/static/", http.StripPrefix("/static/", static))
	http.HandleFunc("/", index)
	http.ListenAndServe(Port, nil)

}
