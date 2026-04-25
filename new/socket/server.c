#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    int N;

    char buffer[1024] = {0};

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
    write(sock, &N, sizeof(N));

    // Receive result
    read(sock, buffer, sizeof(buffer));

    printf("From Server:\n%s\n", buffer);

    close(sock);

    return 0;
}
