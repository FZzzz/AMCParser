CC = g++
CFLAGS = -std=c++11 -O0 -Wall

all:
	$(CC) $(CFLAGS) -c Character.cpp ASFParser.cpp AMCParser.cpp main.cpp
	$(CC) $(CFLAGS) Character.o ASFParser.o AMCParser.o main.o -o asf_amc_parser
debug:
	$(CC) $(CFLAGS) -g -c Character.cpp ASFParser.cpp AMCParser.cpp main.cpp
	$(CC) $(CFLAGS) Character.o ASFParser.o AMCParser.o main.o -o asf_amc_parser

test:
	rm -f ./output
	./asf_amc_parser >> output

clean:
	rm *.o