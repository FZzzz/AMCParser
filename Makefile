all:
	g++ -std=c++11 -c Character.cpp main.cpp ASF_parser.cpp
	g++ -std=c++11 ASF_parser.o Character.o main.o -o asf_parser
clean:
	rm *.o