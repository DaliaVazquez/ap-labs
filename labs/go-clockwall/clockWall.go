package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
)

func cp(des io.Writer, src io.Reader) {
	_, err := io.Copy(des, src)

	if err != nil {
		log.Fatal(err)
	}
}
func main() {

	if len(os.Args) >= 2 {
		x := 1

		for _, arg := range os.Args[1:] {
			log.Println("Port:", arg[strings.LastIndex(arg, "=")+1:])
			conn, err := net.Dial("tcp", arg[strings.LastIndex(arg, "=")+1:])

			if err == nil {
				defer conn.Close()
				go cp(os.Stdout, conn)
			} else {
				log.Fatal(err)
			}
		}

		estado := make(chan int)
		x = <-estado
		log.Println("Close with: ", x)
		close(estado)

	} else {

		fmt.Println("Incorrect number of arguments")
		os.Exit(1)
	}
}
