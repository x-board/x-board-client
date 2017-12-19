
all:
	gcc -c lsquaredc/lsquaredc.c
	g++ -c -std=c++11 src/x-board.cpp src/main.cpp
	g++ lsquaredc.o x-board.o main.o -o x-board

clean: 
	rm -f *.o