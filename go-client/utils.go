package main

import (
	"bufio"
	"os"
)

func (lottery *Lottery) PutNumbersIn(numbers [4]int) {
	lottery.Number1 = numbers[0]
	lottery.Number2 = numbers[1]
	lottery.Number3 = numbers[2]
	lottery.Number4 = numbers[3]
}

func ScanLine(input *string) {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	*input = scanner.Text()
}
