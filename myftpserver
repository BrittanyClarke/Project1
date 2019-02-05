//myftpserver.cpp                                                                                                                                                                                                
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <stdio.h>
using namespace std;

int main(int argc, char* argv[]) {

  //Create the port that the server is going to run on                                                                                                                                                      
  int servPort;
  try{
    servPort = stoi(argv[1]);
  }
  catch(std::exception& e){
    cerr << "Server port creation failed. Please enter a valid socket." << endl;
    return -1;
  }

  if(servPort < 1){
    cerr << "Server port creation failed. Please enter a valid socket." << endl;
    return -1;
  }

  //Create a socket                                                                                                                                                                                         
  int listening = socket(AF_INET, SOCK_STREAM, 0);

  //Create error message if socket cannot be created, & exit.                                                                                                                                               
  if(listening == -1){
    cerr << "Socket cannot be created." << endl;
    return -1;
  }

  //Bind the socket for IP/Port                                                                                                                                                                             
  //Assign IP, Port                                                                                                                                                                                         
  sockaddr_in hint; //sockaddr_in is for IPv4                                                                                                                                                               
  hint.sin_family = AF_INET;
  hint.sin_port = htons(servPort); //Since this is an Intel processor, this address is written in little-endian format, hence the need for "htons"                                                          
  inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr); //pton, Internet command, which is a pointer to a string to a number. Converts number to an array of integers. 127.0.0.1                                   

  //Check if binding was successful                                                                                                                                                                         
  if(bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1){
    cerr << "Cannot bind to IP/Port" << endl;
    return -1;
  }
  //Mark socket for listening                                                                                                                                                                               
  if(listen(listening, SOMAXCONN) == -1) { //SOMAXCONN = maximum number of connections                                                                                                                      
    cerr << "Cannot listen." << endl;
   return -1;
  }
  //Accept call                                                                                                                                                                                             
  sockaddr_in client;
  socklen_t clientSize;
  char host[NI_MAXHOST];
  char svc[NI_MAXSERV];

  int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
  if(clientSocket == -1){
    cerr << "Cannnot connect due to an issue with client connecting." << endl;
    return -1;
  }

  //Close listening socket                                                                                                                                                                                  
  close(listening);
  memset(host, 0, NI_MAXHOST);
  memset(svc, 0, NI_MAXSERV);

  int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

  if(result){
    cout << host << "Connected on: " << svc << endl;
  }
  else{
    inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    cout << host << "Connected on: " << ntohs(client.sin_port) << endl;
  }

  //Loop: while receiving, display message, echo message                                                                                                                                                    
  char buf[4096];
  while(true){
    //Clear the buffer                                                                                                                                                                                      
    memset(buf, 0, 4096);
    //Wait for message                                                                                                                                                                                      
    int bytesRecv = recv(clientSocket, buf, 4096, 0);
    if(bytesRecv == -1){
      cerr << "There was a connection issue." << endl;
      break;
    }
    if(bytesRecv == 0){
      cout << "The client disconnected." << endl;
      break;
    }

    //Display message                                 
	string userInput;
	userInput = string(buf,0,bytesRecv);
	cout<<"Here is the user's input: "<<userInput<<endl;
	
	/**
	 * if the user inputs pwd, it will print out the present
	 * working directory of the server
	 */
	if(userInput == "pwd"){
		long path_max;
		size_t size;
		char *ptr;
		char *buffer;
		// turn off buffering for cout
		std::cout.setf(std::ios::unitbuf);
		path_max = pathconf(".", _PC_PATH_MAX);
		if (path_max == -1)
			size = 1024;
		else if (path_max > 10240)
			size = 10240;
		else
			size = path_max;

		for (buffer = ptr = NULL; ptr == NULL; size *= 2){
			ptr = getcwd(buffer, size);
		}		
		//Resend message                                                                                                                                                                               
		send(clientSocket, ptr, 256, 0);
		free(ptr);
		free(buffer);
	}
	
	
	/**
	 * if the user inputs mkdir, it should include the name of
	 * the directory to create and will output "Created" once
	 * the directory is created... you can view this by typing pwd
	 */
	size_t found = userInput.find("mkdir");
	if(found!=string::npos){
		size_t pos = 1 + userInput.find(' ');
		size_t pos2 = userInput.find(' ', pos);
		string dirName = userInput.substr(pos, pos2-pos);
		mkdir(dirName.c_str(), 0777);
		send(clientSocket, "Created", 7, 0);
	}
	
	
	/**
	 * if the user inputs cd, they should include '..' or
	 * <directory_name>, and it will change the directory
	 * location appropriately.. assuming that there is a
	 * directory of the name they type in.. once it changes
	 * directories, it will out "Changed"... you can view this
	 * by typing pwd
	 */
	size_t cdFound = userInput.find("cd");
	if(cdFound !=string::npos){
		size_t posC = 1 + userInput.find(' ');
		size_t pos2C = userInput.find(' ', posC);
		string loc = userInput.substr(posC, pos2C-posC);
		if(loc ==".."){
			chdir("..");
		}
		else{
			chdir(loc.c_str());
		}
		send(clientSocket, "Changed", 7, 0);
	}
	/**
	 * if the user inputs delete, it should include the name
	 * of the file they want to delte and it will appropriately
	 * remove the file from the directory
	 */
	size_t deleteFound = userInput.find("delete");
	if(deleteFound !=string::npos){
		size_t posD = 1 + userInput.find(' ');
		size_t pos2D = userInput.find(' ', posD);
		string fileName = userInput.substr(posD, pos2D-posD);
		const char * fileChar = fileName.c_str();
		if(remove(fileChar) != 0){
			send(clientSocket, "Error", 5, 0);
		}
		else{
			send(clientSocket, "Deleted", 7, 0);
		}
	}
	
	/**
	 *if the user inputs ls, it will print out files and
	 * directories within the pwd... not including hidden files
	 */
	if(userInput == "ls"){
		bool a = false;
		const char *dirname="./";
		vector<char*> cvec;
		DIR * dirp = opendir(dirname);
		struct dirent * direntp = nullptr;
		string dir(dirname);
		string path;
		
		while((direntp = readdir(dirp)) != nullptr)
		{
			if(a == false)
			{
				if((!strcmp(direntp->d_name, ".")) || (!strcmp(direntp->d_name, "..")))
				{
					continue;
				}
				else if((!strcmp(direntp->d_name, "/")) || (!strcmp(direntp->d_name, "//")))
				{
					continue;
				}
				
				if((!strncmp(direntp->d_name, ".", 1)))
				{
					continue;
				}
			}
			
			cvec.push_back(direntp->d_name);
		}
		
		std::sort(std::begin(cvec),std::end(cvec), [](std::string const &name1, std::string const &name2){
			return name1 < name2;
		});
		string lsOutput = "";
		for(unsigned int i = 0; i < cvec.size(); i++){
			if(i !=0)
				lsOutput.append(" ");
			lsOutput.append(cvec[i]);
		}
		const char *output = lsOutput.c_str();
		send(clientSocket, output, 256, 0);
		closedir(dirp);
	}
  }
  //Close the socket                                                                                                                                                                                        
  close(clientSocket);
  return 0;
}
