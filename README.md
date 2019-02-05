# Project1
README
Distributed Systems — Project 1: Simple FTP Client and Server
Spring 2019
University of Georgia

Team Members: 
  Brittany Clarke
  Anokhi Patel
  Afua Acheampong

Implementation Overview:
This project was done in its entirety by Brittany Clarke, Anokhi Patel, and Afua Acheampong. We hereby
state that we have not received unauthorized help of any form.
This Simple FTP Client and Server project allows a server and client to interact with each other. We implemented this project using a single-threading at the server's end using TCP socket. This project allows the client to type in commands to view information on the server's side. As well in this project, it is assumed that the client inputs correct commands.
There seemed to be an issue of printing information out to the client after calling ls command. But if you call it at the end, everything prints out perfectly.

As well, in order to use get and put, the file and its correct name must exist within both directories. In the ftpServer directory, the server.txt contains content, so when you input 'get server.txt' it will copy the content into the server.txt in ftpClient directory. As well, in the ftpClient directory, the client.txt contains context, so when you input 'put client.txt', it will copy the content into the client.txt in the ftpServer directory.

For the delete command, there is a delete.txt included in the ftpServer directory to make it easier to use the command 'delete delete.txt'

Compilation Instructions:
Starting the server:
	~$ cd <path-to-directory>
	./main ‘port number for server to execute on’ 
	EXAMPLE: to start FTP server named main on port number 58000, 
	execute the following command:  ./main 58000
	
Starting the client:
	~$cd <path-to-directory>
	./ftpClient ‘127.0.0.1’ ‘same port number the server is executing on’ 
	EXAMPLE: To start the client on the sever’s machine address, 
	enter “127.0.0.1” on the port corresponding to the server 58000. 
	./ftpClient 127.0.0.1 58000

Commands:

*get*: copy file with the name <remote_filename> from remote directory to local directory
EXAMPLE: get <remote_filename>

*put*: copy file with the name <local_filename> from local directory to remote directory

*delete*: delete the file with the name <remote_filename> from the remote directory
EXAMPLE: delete <remote_filename>

*ls*: To view all the files and subdirectories within the current remote directory, type 'ls' and hit 'enter'
EXAMPLE: myftp> ls

*cd* ..: To change to the parent directory of the remote directory, type 'cd ..' and hit 'enter'
EXAMPLE: myftp> cd ..

*cd <directory_name>*: To change to a subdirectory within the current remote directory, type 'cd <directory_name>' and hit 'enter'
EXAMPLE: myftp> cd <directory_name>

*mkdir <directory_name>*: To create a subdirectory within the current remote directory, type 'mkdir <directory_name>' and hit 'enter'
EXAMPLE: myftp> mkdir <directory_name>

*pwd*: To view the current working remote directory, type 'pwd' and hit 'enter'
EXAMPLE: myftp> pwd

*quit*: To quit the client, type ‘quit’ and hit ‘enter’.
EXAMPLE: mytftp> quit
