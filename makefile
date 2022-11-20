
all: main.o my_memory.o
	g++ -std=c++11 main.o my_memory.o -o output

main.o:
	g++ -std=c++11 -c main.cpp

my_memory.o: my_memory.cpp my_memory.h
	g++ -std=c++11 -c my_memory.cpp

clean:
	rm *.o output