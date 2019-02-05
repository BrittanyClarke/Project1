all: myftpclient

myftpclient.o: myftpclient.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c myftpclient.cpp

myftpclient: myftpclient.o
	g++ -o myftpclient myftpclient.o

clean:
	rm -f myftpclient
	rm -f myftpclient.o

