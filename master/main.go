package main

func main() {
	//bot, err := newBotInstance()
	//if err != nil {
	//	panic(err)
	//}
	//defer bot.close()

	log, _ := newLogger()
	log.start()
}
