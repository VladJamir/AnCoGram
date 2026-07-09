CC=g++
CFLAGS=-c -std=c++11 -pthread

nonogramsolver: obj main.o
	$(CC) -pthread obj/main.o -o nonogramsolver

obj:
	mkdir -p obj

main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o obj/main.o

clean:
	rm -rf obj nonogramsolver
