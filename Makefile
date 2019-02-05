all: myftpserver

myftpserver: myftpserver.o
	g++ -o  myftpserver myftpserver.o

myftpserver.o: myftpserver.cpp
	g++ -Wall -g -c myftpserver.cpp

clean: 
	rm -f myftpserver
	rm -f myftpserver.o
