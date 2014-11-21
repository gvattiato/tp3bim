
all: main

main: main.cpp functions.o
	g++ -Wall -o main main.cpp functions.o
functions.o: functions.cpp functions.h
	g++ -Wall -c -o functions.o functions.cpp
clean:
	rm *.o
mrproper: clean
	rm ppm


