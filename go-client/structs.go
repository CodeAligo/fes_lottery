package main

import (
	"time"
)

type Admin struct {
	ID       string `gorm:"primary_key"`
	Name     string
	Password string
}

type Lottery struct {
	Owner   string
	Key     string `gorm:"primary_key"`
	Numbers [5]int `gorm:"type:integer[5]"`
	Date    time.Time
}
