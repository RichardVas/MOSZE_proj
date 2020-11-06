
OBJS = main.o Monster.o Hero.o JSON.o
CFLAGS = -std=c++17 -Wall -Werror -g
CC = g++-10
OUT = a.out
VLGRNDFLAGS:= --leak-check=full --error-exitcode=1 --log-file=memory_leaks.txt
JSONFILES:=  units/scenario1.json

build: $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

main.o: main.cpp Hero.h Monster.h JSON.h
	$(CC) $(CFLAGS) -c main.cpp

Monster.o: Monster.cpp Monster.h JSON.h
	$(CC) $(CFLAGS) -c Monster.cpp

Hero.o: Hero.cpp Hero.h JSON.h Monster.h
	$(CC) $(CFLAGS) -c Hero.cpp

JSON.o: JSON.cpp JSON.h
	$(CC) $(CFLAGS) -c JSON.cpp


diff_test:
	diff output1.txt real_output1.txt
	diff output2.txt real_output2.txt

check_leaks:
	valgrind $(VLGRNDFLAGS) ./$(OUT) $(JSONFILES)

gtest:
	cd unit_tests && cmake CMakeLists.txt
	cd unit_tests && make
	cd unit_tests && ./runTests

documentation:
	doxygen doxconf

clean:
	rm -rf $(OBJS) a.out ./DOCS
