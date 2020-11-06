SHELL:=/bin/bash

OBJS = Jsonparser.o Fighter.o Source.o
OUT = a.out
CFLAGS = -Wall -std=c++17
CC = g++

default: build

build: $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

run: ./$(OUT)
	./$(OUT) $(UNIT1) $(UNIT2)

Fighter.o: Fighter.cpp Fighter.h Jsonparser.h
	$(CC) $(CFLAGS) -c Fighter.cpp

Jsonparser.o: Jsonparser.cpp Jsonparser.h
	$(CC) $(CFLAGS) -c Jsonparser.cpp

Source.o: Source.cpp Fighter.h Jsonparser.h
	$(CC) $(CFLAGS) -c Source.cpp

valgrind:
	bash -c "chmod +x valgrind.sh"
	bash -c "./valgrind.sh"

cppcheck:
	bash -c "chmod +x cppcheck.sh"
	bash -c "./cppcheck.sh"

documentation:
	doxygen doxconfig

clean:
	rm -rf $(OBJS) $(OUT)
