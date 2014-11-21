
all: main

main: main.cpp img_class.o
	g++ -Wall -o main main.cpp img_class.o

img_class.o: img_class.cpp img_class.h
	g++ -Wall -c -o img_class.o img_class.cpp

clean:
	rm *.o

mrproper: clean
	rm ppm


