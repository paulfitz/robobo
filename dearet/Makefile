SRC = "Test_Message_2p1.txt"

default:
	./process.js $(SRC)

freq:
	sed "s/ /\n/g" < $(SRC) | sort | uniq -c | sort -n | head --lines=-1
