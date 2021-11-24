// Clock Server is a concurrent TCP server that periodically writes the time.
package main

import (
	"io"
	"log"
	"net"
	"time"
	"os"
	"flag"
	"fmt"
)

func handleConn(c net.Conn, local *time.Location) {
	defer c.Close()
	for {
		_, err := io.WriteString(c, fmt.Sprintf("%-16s : %s", local.String(), time.Now().In(local).Format("15:04:05\n")))
		if err != nil {
			return // e.g., client disconnected
		}
		time.Sleep(1 * time.Second)
	}
}

func main() {
	port := flag.String("port", "8080", "Server port")
	flag.Parse()
	local, err := time.LoadLocation(os.Getenv("TZ"))
	if err != nil {
		log.Fatal(err)
	}
	listener, err := net.Listen("tcp", "localhost:"+*port)
	if err != nil {
		log.Fatal(err)
	}
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err) // e.g., connection aborted
			continue
		}
		go handleConn(conn, local) // handle connections concurrently
	}
}
