project: main.o functions.o
	cc main.o functions.o -o project -lm
main.o: main.c 
	cc -Wall -c main.c
functions.o: functions.c header.h
	cc -c header.h
	cc -Wall -c functions.c

clear:
	rm *.o	
