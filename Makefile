SHELL:= /bin/bash

OBJS := main.o character.o JSON.o Hero.o Monster.o
CFLAGS := -Wall -std=c++17
CC := clang++

build: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

main.o: main.cpp character.h JSON.h Hero.h Monster.h
	$(CC) $(CFLAGS) -c main.cpp

character.o: character.cpp character.h JSON.h
	$(CC) $(CFLAGS) -c character.cpp

JSON.o: JSON.cpp JSON.h
	$(CC) $(CFLAGS) -c JSON.cpp

Hero.o: Hero.cpp Hero.h character.h JSON.h Monster.h
	$(CC) $(CFLAGS) -c Hero.cpp

Monster.o: Monster.cpp Monster.h character.h JSON.h Hero.h
	$(CC) $(CFLAGS) -c Monster.cpp

documentation:
	doxygen doxconfig

test:
	bash -c "chmod +x test.sh"
	bash -c "./test.sh main output.txt"

io-diff-tests:
	bash -c "diff output.txt good_output.txt"

static-code-analysis:
	bash -c "chmod +x run_cppcheck.sh"
	bash -c "./run_cppcheck.sh"

memory-leak-check:
	bash -c "chmod +x run_valgrind_check.sh"
	bash -c "./run_valgrind_check.sh"

parser-tests:
	cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make
	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest.a && sudo ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a
	cd unit_test && cmake CMakeLists.txt
	cd unit_test && make
	cd unit_test && ./test_parser

clean:
	rm -rf *.o main ./html ./latex test_parser CMakeCache.txt cmake_install.cmake libtestCode.a
