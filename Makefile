SHELL=/bin/bash

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
	IFS=$'\n'
	echo "$(valgrind --leak-check=yes --log-file=memory_leak.txt ./a.out Maple.json Sally.json)"
	result="$(cat ./memory_leak.txt)"
	echo $result
	errors="$(echo $result | sed 's/^.*ERROR SUMMARY: \([0-9]*\) errors.*$/\1/')"
	if [ "$errors" == "0" ]
	then
		echo
		echo "No memory leaks found."
	else
		echo "Memory leaks found."
		exit 1
	fi

cppcheck:
	IFS=$'\n'
	echo "$(cppcheck *.cpp --enable=warning --output-file=cppcheck_errors.txt)"
	if  [ ! -s .cppcheck_errors.txt ]
	then
			echo "No performance or style error."
			 echo "$(cppcheck *.cpp --enable=performance,style --output-file=cppcheck_performance.txt)"
		
		if [ ! -s cppcheck_performance.txt ]
		then
			echo "No performance or style error."
		fi
	else
			echo "Error/warning!"
			exit 1
	fi

documentation:
	doxygen doxconfig
	
clean:
	rm -rf $(OBJS) $(OUT)
