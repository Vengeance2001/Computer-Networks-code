#include <iostream>
#include <fstream>
#include <string>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define SIZE 1024

void receive_file(const char* filename, SOCKET sockfd){
    std::ofstream file(filename, std::ios::binary);
    if(!file){
        std::cerr<<"Error in recieving file bro."<<std::endl;
        exit(1);
    }

    char data[SIZE] = {0};
    int byteReceived;

    while(true){
        byteReceived = recv(sockfd, data, SIZE, 0);
        if(byteReceived==SOCKET_ERROR || byteReceived == 0){
            break;
        }
        file.write(data, byteReceived);
        memset(data, 0, SIZE);
    }
    file.close();
}

int main(){
    int port = 12345;
    int e;
      WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }
    
    SOCKET listenSock, clientSock;
    sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);

    listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET) {
        std::cerr << "Error in socket creation." << std::endl;
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
 if (bind(listenSock, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error in binding." << std::endl;
        return 1;
    }

    if (listen(listenSock, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error in listening." << std::endl;
        return 1;
    }
    std::cout << "Server listening on port " << port << std::endl;

    clientSock = accept(listenSock, reinterpret_cast<struct sockaddr*>(&clientAddr), &addrLen);
    if (clientSock == INVALID_SOCKET) {
        std::cerr << "Error in accepting client connection." << std::endl;
        return 1;
    }
    std::cout << "Client connected." << std::endl;

    receive_file("BhaikeFile.txt", clientSock);
    std::cout << "File received and saved as 'BhaikeFile.txt'." << std::endl;

    closesocket(clientSock);
    closesocket(listenSock);
    WSACleanup();

    return 0;
}