main: main.o 
	cc main.o -o main
main.o: main.c 
	cc -Wall -c main.c
clear:
	rm *.o	
