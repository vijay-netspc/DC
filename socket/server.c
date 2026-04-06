#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <signal.h> 
#define PORT 5000 
#define BUFFER_SIZE 1024 
int main() { 
 
 int server_fd, client_fd; 
 struct sockaddr_in server_addr; 
 char buffer[BUFFER_SIZE]; 
            server_fd = socket(AF_INET, SOCK_STREAM, 0); 
            server_addr.sin_family = AF_INET; 
 server_addr.sin_addr.s_addr = INADDR_ANY; 
 server_addr.sin_port = htons(PORT); 
            bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)); 
 listen(server_fd, 1); 
 printf("Server waiting for connection...\n"); 
 client_fd = accept(server_fd, NULL, NULL); 
 printf("Client connected\n"); 
 if (fork() == 0) { 
          while (1) { 
         memset(buffer, 0, BUFFER_SIZE); 
         if (recv(client_fd, buffer, BUFFER_SIZE, 0) <= 0) 
             break; 
         printf("\nClient: %s\nServer: ", buffer); 
         fflush(stdout); 
     } 
     kill(getppid(), SIGTERM); 
 } else { 
         while (1) { 
         printf("Server: "); 
         fgets(buffer, BUFFER_SIZE, stdin); 
         buffer[strcspn(buffer, "\n")] = 0; 
         send(client_fd, buffer, strlen(buffer), 0); 
     } } 
            close(client_fd); 
 close(server_fd); 
 return 0; 
} 
