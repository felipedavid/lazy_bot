package main

func main() {
	//bot, err := newBotInstance()
	//if err != nil {
	//	panic(err)
	//}
	//defer bot.close()

	log, err := newLogger()
	if err != nil {
		panic(err)
	}

	log.start()
}
