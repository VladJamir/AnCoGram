CC=g++
CFLAGS=-c -std=c++11 -pthread

nonogramsolver: clean obj main.o board.o
	$(CC) -pthread obj/main.o obj/board.o -o nonogramsolver

obj:
	mkdir -p obj

main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o obj/main.o
board.o: src/board.cpp
	$(CC) $(CFLAGS) src/board.cpp -o obj/board.o

clean:
	rm -rf obj nonogramsolver
