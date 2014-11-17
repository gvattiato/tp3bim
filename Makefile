
all: ppm

ppm: ppm.c functions.o
	gcc -Wall -o ppm ppm.cpp functions.o
functions.o: functions.h functions.cpp
	g++ -Wall -c -o functions.o functions.cpp
clean:
	rm *.o
mrproper: clean
	rm ppm


