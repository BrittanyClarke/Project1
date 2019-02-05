//myftpclient.cpp
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[]) {
  if(argc != 3){
    cerr << "Invalid arguments. Please pass machine name and port number. << endl";
    return -1;
  }
  //Create a socket                                                                                                                                                                                         
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  //If socket cannot be created, exit                                                                                                                                                                       
  if(sock == -1){
    return -1;
  }
  //Create a hint structure for the server we're connecting with                                                                                                                                            
  //First argument to command line == Machine name where server resides (ip address?)                                                                                                                       
  string ipaddress = argv[1];
  //Second argument to command line == port number                                                                                                                                                          
  int port = stoi(argv[2]);

  if(ipaddress != "127.0.0.1"){
    cout << "Incorrect machine location. Please enter IP address 127.0.0.1";
  }

  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(port);
  inet_pton(AF_INET, ipaddress.c_str(), &hint.sin_addr);

  //Connect to the server on the socket                                                                                                                                                                     
  int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));

  if(connectRes == -1){
    return 1;
  }

  char buf[4096];
  string userInput;

  //Loop: enter text, send to server, wait for response, display response                                                                                                                                   
  do {
    cout << "mytftp> ";
    getline(cin, userInput);

  //If user quits, then stop                                                                                                                                                                              
    if(userInput == "quit"){
      return -1;
    }

    int sendRes = send(sock, userInput.c_str(), userInput.size()+1, 0);
    //if server is not responding, continue gracefully                                                                                                                                                      
    if(sendRes == -1){
      cout << "Unable to send to server.";
      continue;
    }

    memset(buf, 0, 4096);

    int bytesReceived = recv(sock, buf, 4096, 0);

    if(bytesReceived == -1){
      cout << "There was an error getting a response from the server." << endl;
    }
  } while(true);

  //Close the socket                                                                                                                                                                                        
  close(sock);
  return 0;
}
