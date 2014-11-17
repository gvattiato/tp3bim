
all: main

main: main.c functions.o
	gcc -Wall -o main main.c functions.o
functions.o: functions.c
	gcc -Wall -c -o functions.o functions.c
clean:
	rm *.o
mrproper: clean
	rm ppm


