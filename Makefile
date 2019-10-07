

programa: UNO.o manejo_archivos.o
	gcc -o programa UNO.o manejo_archivos.o

UNO.o: UNO.c
	gcc -c UNO.c

manejo_archivos.o: manejo_archivos.c manejo_archivos.h
	gcc -c manejo_archivos.c

clean:
	rm -f programa *.o
	rm -f mazo/*.txt
	rm -f player1/*.txt
	rm -f player2/*.txt
	rm -f player3/*.txt
	rm -f player4/*.txt
	rm -f last_card/*.txt
