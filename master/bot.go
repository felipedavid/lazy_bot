package main

import (
	"net"

	"github.com/Microsoft/go-winio"
)

type OperationType uint8

const (
	opStart = iota
)

type botInstance struct {
	conn   net.Conn
	logger *logger
}

func newBotInstance() (*botInstance, error) {
	config := winio.PipeConfig{
		MessageMode:      true,
		InputBufferSize:  1024,
		OutputBufferSize: 1024,
	}

	listener, err := winio.ListenPipe("\\\\.\\pipe\\lazy_commands", &config)
	if err != nil {
		return nil, err
	}

	conn, err := listener.Accept()
	if err != nil {
		return nil, err
	}

	log, err := newLogger()
	if err != nil {
		return nil, err
	}
	log.start()

	return &botInstance{
		conn:   conn,
		logger: log,
	}, nil
}

func (b *botInstance) start() {
	b.conn.Write([]byte{opStart})
}

func (b *botInstance) close() {
	b.conn.Close()
}
