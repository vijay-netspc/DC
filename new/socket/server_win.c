#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int N;

    char buffer[1024] = {0};

    // Initialize Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind and listen
    bind(server_socket, (struct sockaddr *)&address, sizeof(address));
    listen(server_socket, 3);

    printf("Server waiting...\n");

    // Accept client
    client_socket = accept(server_socket, (struct sockaddr *)&address, &addrlen);

    // Receive N
    recv(client_socket, (char*)&N, sizeof(N), 0);
    printf("Received N = %d\n", N);

    // Prepare odd numbers as string
    char result[1024] = "Odd numbers: ";
    char temp[20];

    for(int i = 0; i <= N; i++) {
        if(i % 2 != 0) {
            sprintf(temp, "%d ", i);
            strcat(result, temp);
        }
    }

    // Send result to client
    send(client_socket, result, sizeof(result), 0);

    // Close
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
