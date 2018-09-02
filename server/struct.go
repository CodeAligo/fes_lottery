package main

import (
	"time"
)

type Result struct {
	Number  []int
	Winners int
}

type Student struct {
	ID   int    `sql:"not null" gorm:"primary_key"`
	Name string `sql:"not null"`

	Tickets []Ticket

	CreatedAt time.Time
}

type Ticket struct {
	ID        int
	StudentID int
	Number    []int `gorm:"type:integer[]"`
	CreatedAt time.Time
}
