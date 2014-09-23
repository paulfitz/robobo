SRC = "Test_Message_2p1.txt"

default:
	./process.js $(SRC) | tee outcome.scm
	grep triplet outcome.scm | tee progress.scm
	which prettify && prettify outcome.scm || echo skipping indentation
	which prettify && prettify progress.scm || echo skipping indentation
	sed -i "s/^.triplet.*//" progress.scm
	sed -i "s/^.moony_triplet.)//" progress.scm
	sed -i "s/^).*//" progress.scm

notes:
	./notes.js | tee notes.txt

freq:
	sed "s/ /\n/g" < $(SRC) | sort | uniq -c | sort -n | head --lines=-1
