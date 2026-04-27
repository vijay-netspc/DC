#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    int N;

    char buffer[1024] = {0};

    // Initialize Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Change IP if using different system
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // Connect
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Input
    printf("Enter N: ");
    scanf("%d", &N);

    // Send N
    send(sock, (char*)&N, sizeof(N), 0);

    // Receive result
    recv(sock, buffer, sizeof(buffer), 0);

    printf("From Server:\n%s\n", buffer);

    closesocket(sock);
    WSACleanup();

    return 0;
}
