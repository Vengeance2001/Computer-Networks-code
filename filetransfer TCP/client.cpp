#include <iostream>
#include <fstream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define SIZE 1024

void send_file(const char* filename, SOCKET sockfd){
    std::ifstream file(filename, std::ios::binary);
    if(!file){
        std::cerr<<"Bro error in sending file"<<std::endl;
        exit(1);
    }

    char data[SIZE]={0};
    while (file.read(data, SIZE))
    {
        int bytesSent = send(sockfd, data, SIZE, 0);
        if(bytesSent == SOCKET_ERROR){
            std::cerr<<"Error in sending file bhai"<<std::endl;
            exit(1);
        }
        memset(data, 0, SIZE);
    }

    int remainingBytes = file.gcount();
    if(remainingBytes>0){
        int bytesSent = send(sockfd, data, remainingBytes,0);
        if(bytesSent==SOCKET_ERROR){
            std::cerr<<"Error in sending the patra"<<std::endl;
            exit(1);
        }
    }
    file.close();
    
}

int main(){
    const char* ip = "127.0.0.1";
    int port = 12345;
    int e;

    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2), &wsaData)!=0){
        std::cerr <<"Winsock initialization failed"<<std::endl;
        return 1;
    }

    SOCKET sockfd;
    sockaddr_in serverADDr;
    const char* filename = "myBroFile.txt";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == INVALID_SOCKET){
        std::cerr<<"Socket creation failed"<<std::endl;
        return 1;
    }
    std::cout<<"Socket created bro!"<<std::endl;

    serverADDr.sin_addr.s_addr = inet_addr(ip);
    serverADDr.sin_family = AF_INET;
    serverADDr.sin_port = htons(port);
     
     e = connect(sockfd, reinterpret_cast<struct sockaddr*>(&serverADDr), sizeof(serverADDr));
     if(e==SOCKET_ERROR){
        std::cerr<<"Socket connect failed"<<std::endl;
        return 1;
     }

     std::cout<<"Bro Server se connected!"<<std::endl;
     send_file(filename, sockfd);
     std::cout<<"Bro file transfer sucessful!"<<std::endl;
     std::cout<<"bro closing the connection"<<std::endl;
     closesocket(sockfd);
     WSACleanup();


return 0;
}