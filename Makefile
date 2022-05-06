CC = g++
CFLAGS = -Wextra -Wall
LDLIBS = -lm

build: algo1_test.o algo2_test.o algo3_test.o

run-best:
	./test1

run-p1:
	./test2

run-p2:
	./test3

algo1_test.o: var1.cpp
	g++ var1.cpp -o test1 $(LDLIBS) $(CFLAGS)

algo2_test.o: var2.cpp
	g++ var2.cpp -o test2 $(LDLIBS) $(CFLAGS)

algo3_test.o: var3.cpp
	g++ var3.cpp -o test3 $(LDLIBS) $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o test1 test2 test3 test.in test.out