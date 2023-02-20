package main

import (
	"fmt"
	"net"

	"github.com/Microsoft/go-winio"
)

type logger struct {
	listener net.Listener
	conn     net.Conn
}

func newLogger() (*logger, error) {
	config := winio.PipeConfig{
		MessageMode:      true,
		InputBufferSize:  1024,
		OutputBufferSize: 1024,
	}

	listener, err := winio.ListenPipe("\\\\.\\pipe\\lazy_logger", &config)
	if err != nil {
		return nil, err
	}

	conn, err := listener.Accept()
	if err != nil {
		return nil, err
	}

	return &logger{
		listener: listener,
		conn:     conn,
	}, nil
}

func (l *logger) start() {
	fmt.Println("Starting to listen")
	for {
		buf := make([]byte, 5000)
		_, err := l.conn.Read(buf)
		if err != nil {
			fmt.Println("Waiting for worker connection...")
			l.conn, err = l.listener.Accept()
			if err != nil {
				break
			}
			continue
		}
		fmt.Println(string(buf))
	}
}
