#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


int main(){
    int serverSocket; 
    int clientSocket;
    struct sockaddr_in serverAddr;  //structure required by bind
    char buffer[500]="hello from server";
    char recvBuffer[500];

    serverSocket=socket(AF_INET, SOCK_STREAM, 0);  //creates tcp socket

    serverAddr.sin_family=AF_INET;  //type
    serverAddr.sin_port=htons(9001);  //port number
    serverAddr.sin_addr.s_addr=inet_addr("192.168.1.18");  //host

    bind(serverSocket, (struct serverAddr*) &serverAddr, sizeof(serverAddr));  //bind the server

    listen(serverSocket, 5);
    
    clientSocket=accept(serverSocket, NULL, NULL);  //Accept incoming connections
    printf("CLIENT CONNECTED\n");
    send(clientSocket, buffer, sizeof(buffer), 0);  //Sending data to the client
    recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);  //Recv data from the client
    printf("Client has sent:  %s\n", recvBuffer);  //Print the data sent by the client
    close(serverSocket);  //Close the connection
    return 0;


}