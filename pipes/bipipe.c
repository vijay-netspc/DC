#include <stdio.h> 
#include <unistd.h> 
#include <string.h> 
int main() { 
int fd1[2]; 
int fd2[2]; 
char parent_msg[] = "Hello from Parent"; 
char child_msg[]  = "Hello from Child"; 
 char buffer[100]; 
 
 pipe(fd1); 
 pipe(fd2); 
 
 if (fork() == 0) { 
     
 
     close(fd1[1]); 
     read(fd1[0], buffer, sizeof(buffer)); 
     printf("Child received: %s\n", buffer); 
     close(fd1[0]); 
 
     close(fd2[0]); 
     write(fd2[1], child_msg, strlen(child_msg) + 1); 
     close(fd2[1]); 
 
 } else { 
     
 
     close(fd1[0]); 
     write(fd1[1], parent_msg, strlen(parent_msg) + 1); 
     close(fd1[1]); 
 
     close(fd2[1]); 
     read(fd2[0], buffer, sizeof(buffer)); 
     printf("Parent received: %s\n", buffer); 
     close(fd2[0]); 
 } 
 
 return 0; 
}
