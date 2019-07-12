CFLAGS = -std=c++11 -Wall -O0

all:
	g++ $(CFLAGS) -c Character.cpp main.cpp ASFParser.cpp
	g++ $(CFLAGS) ASFParser.o Character.o main.o -o asf_parser
clean:
	rm *.o