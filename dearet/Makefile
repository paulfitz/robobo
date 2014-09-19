SRC = "Test_Message_2p1.txt"
#SRC = "Snip.txt"

default:
	./process.js $(SRC) | tee outcome.txt

freq:
	sed "s/ /\n/g" < $(SRC) | sort | uniq -c | sort -n | head --lines=-1
