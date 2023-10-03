#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

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
    int clientAddressLength = sizeof(clientAddress);

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error in socket creation." << std::endl;
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error in binding." << std::endl;
        return 1;
    }

    std::cout << "UDP Server is listening on port " << PORT << std::endl;

    char buffer[BUFFER_SIZE];

    while (true) {
        int bytesReceived = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Error in receiving data." << std::endl;
            break;
        }

        buffer[bytesReceived] = '\0';

        std::cout << "Received message from client bhai: " << buffer << std::endl;

        std::cout << "Enter a message to send to the client chai (or 'q' to quit): ";
        std::cin.getline(buffer, BUFFER_SIZE);

        if (strcmp(buffer, "q") == 0) {
            break;
        }

        int messageLength = strlen(buffer);

        sendto(serverSocket, buffer, messageLength, 0, (struct sockaddr*)&clientAddress, clientAddressLength);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
