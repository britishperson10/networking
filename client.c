//Compiles on windows

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h.>
#pragma comment(lib, "Ws2_32.lib")

int main(){
    SOCKET client_socket;  //Create a SOCKET structure
    WSADATA wsastructure;  //Create WSADATA structure for winsock init
    int result;
    struct sockaddr_in client_addr;  //Create structure user by connect()
    char data[500]="Hello from client";
    char recvData[500];

    result=WSAStartup(MAKEWORD(2, 2), &wsastructure);  //Initialize winsock
    if(result !=0){
        printf("[!] WinSock Init Failed\n");  //Print errors
        return 1;
    }
    client_socket=socket(AF_INET, SOCK_STREAM, 0);
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(9001);
    client_addr.sin_addr.s_addr= inet_addr("192.168.1.18");

    connect(client_socket, (SOCKADDR*) &client_addr, sizeof(client_addr));  //Connect to server
    recv(client_socket, recvData, sizeof(recvData), 0);  //Recv data from server
    printf("Data from the server:  %s\n", recvData);
    send(client_socket, data, sizeof(data), 0);  //Send data to server
    closesocket(client_socket);  //Close the socket connection and exit
    WSACleanup();
    return 0;
}