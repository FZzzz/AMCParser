CC = g++
CFLAGS = -std=c++11 -O0 -Wall

all:
	$(CC) $(CFLAGS) -c Character.cpp ASFParser.cpp main.cpp
	$(CC) $(CFLAGS) ASFParser.o Character.o main.o -o asf_parser
debug:
	$(CC) $(CFLAGS) -g -c Character.cpp ASFParser.cpp main.cpp
	$(CC) $(CFLAGS) ASFParser.o Character.o main.o -o asf_parser
clean:
	rm *.o