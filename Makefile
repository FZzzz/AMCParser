CFLAGS = -std=c++11 -O0 -Wall

all:
	g++ $(CFLAGS) -c Character.cpp main.cpp ASFParser.cpp
	g++ $(CFLAGS) ASFParser.o Character.o main.o -o asf_parser
clean:
	rm *.o