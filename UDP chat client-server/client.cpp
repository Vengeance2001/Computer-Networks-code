#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1" 
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    SOCKET clientSocket;
    sockaddr_in serverAddress;

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error in socket creation." << std::endl;
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);

    char buffer[BUFFER_SIZE];

    while (true) {
        std::cout << "Enter a message to send to the server Behen (or 'q' to quit): ";
        std::cin.getline(buffer, BUFFER_SIZE);

        if (strcmp(buffer, "q") == 0) {
            break;
        }

        int messageLength = strlen(buffer);

        sendto(clientSocket, buffer, messageLength, 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

        int bytesReceived = recvfrom(clientSocket, buffer, BUFFER_SIZE, 0, NULL, NULL);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Error in receiving data." << std::endl;
            break;
        }

        buffer[bytesReceived] = '\0';

        std::cout << "Received response from server behen: " << buffer << std::endl;
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
