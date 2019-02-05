all: mytftpclient

mytftpclient: mytftpclient.o
	g++ -o  mytftpclient  mytftpclient.o

mytftpclient.o: mytftpclient.cpp
	g++ -Wall -g -c mytftpclient.cpp

clean: 
	rm -f mytftpclient
	rm -f mytftpclient.o

