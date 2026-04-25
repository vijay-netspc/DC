#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<string.h>
int main() {
    int server_socket, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int N;

    char buffer[1024] = {0};

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
    client_socket = accept(server_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // Receive N
    read(client_socket, &N, sizeof(N));
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
    close(client_socket);
    close(server_socket);

    return 0;
}
