CLANG=clang++
CPPFLAGS=-O3 -std=c++20

.PHONY: clean

all: main

foo.o: foo.cpp
	$(CLANG) -c $(CPPFLAGS) foo.cpp

bug.o: bug.cpp foo.h
	$(CLANG) -c $(CPPFLAGS) bug.cpp

main.o: main.cpp bug.h
	$(CLANG) -c $(CPPFLAGS) main.cpp

main: foo.o bug.o main.o
	$(CLANG) foo.o bug.o main.o $(CPPFLAGS) -o main

clean:
	rm foo.o bug.o main.o main
