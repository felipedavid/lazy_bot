package main

import (
	"bufio"
	"fmt"
	"os"

	"github.com/Microsoft/go-winio"
)

func main() {
	config := winio.PipeConfig{
		MessageMode:      true,
		InputBufferSize:  1024,
		OutputBufferSize: 1024,
	}
	listener, err := winio.ListenPipe("\\\\.\\pipe\\lazy_bot", &config)
	if err != nil {
		panic(err)
	}

	conn, err := listener.Accept()
	if err != nil {
		panic(err)
	}

	reader := bufio.NewReader(os.Stdin)
	for {
		fmt.Printf(">>> ")
		buf, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		_, err = conn.Write([]byte(buf[:len(buf)-1]))
		if err != nil {
			break
		}
	}

	conn.Close()
}
