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

    SOCKET serverSocket;
    sockaddr_in serverAddress, clientAddress;

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error in socket creation." << std::endl;
        WSACleanup();
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error in binding." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int clientAddressSize = sizeof(clientAddress);

    while (true) {
        int bytesReceived = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddress, &clientAddressSize);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Error in receiving data." << std::endl;
            break;
        }

        buffer[bytesReceived] = '\0';

        std::cout << "Received message from client: " << buffer << std::endl;

        // Echo the message back to the client
        sendto(serverSocket, buffer, bytesReceived, 0, (struct sockaddr*)&clientAddress, clientAddressSize);

        // Server can send a message to the client as well
        std::cout << "Enter a message to send to the client: ";
        std::cin.getline(buffer, BUFFER_SIZE);
        int messageLength = strlen(buffer);
        sendto(serverSocket, buffer, messageLength, 0, (struct sockaddr*)&clientAddress, clientAddressSize);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
