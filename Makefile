FILE=UNO

programa: $(FILE).o
	gcc -o programa $(FILE).o

UNO.o: $(FILE).c
	gcc -c $(FILE).c

clean:
	rm -f programa *.o
	rm -f mazo/*.txt
	rm -f player1/*.txt
	rm -f player2/*.txt
	rm -f player3/*.txt
	rm -f player4/*.txt
	rm -f last_card/*.txt
