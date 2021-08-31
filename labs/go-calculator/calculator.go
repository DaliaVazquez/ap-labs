package main

import (
	"fmt"
	"os"
	"strconv"
)

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)

func calc(operator int, values []int) int {
	res := values[0]
	fmt.Print(res)
	for i := 1; i < len(values); i++ {
		if operator == 1 {
			fmt.Print(" + ", values[i])
			res += values[i]
		} else if operator == 2 {
			fmt.Print(" - ", values[i])
			res -= values[i]
		} else {
			fmt.Print(" * ", values[i])
			res *= values[i]
		}
	}

	fmt.Print(" = ", res)
	fmt.Println("")
	return 0
}

func main() {
	if len(os.Args) > 3 {
		op := 0
		val := make([]int, 0, 100)
		if os.Args[1] == "add" {
			op = 1
		} else if os.Args[1] == "sub" {
			op = 2
		} else if os.Args[1] == "mult" {
			op = 3
		} else {
			fmt.Println("El operador no es valido")
			return
		}

		for i := 2; i < len(os.Args); i++ {
			n, c := strconv.Atoi(os.Args[i])
			if c == nil {
				val = append(val, n)
			} else {
				fmt.Println("Character no valido")
				return
			}
		}
		calc(op, val)
		return
	} else {
		fmt.Println("Operacion invalida")
	}
}
