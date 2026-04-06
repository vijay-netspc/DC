#include <stdio.h> 
#include <unistd.h> 
#include <string.h> 
int main() { 
int fd[2]; 
char write_msg[] = "Hello from Parent"; 
char read_msg[100]; 
pipe(fd);    
if (fork() == 0) { 
close(fd[1]); 
read(fd[0], read_msg, sizeof(read_msg)); 
printf("Child received: %s\n", read_msg); 
close(fd[0]); 
} else { 
close(fd[0]); 
write(fd[1], write_msg, strlen(write_msg) + 1); 
close(fd[1]); 
} 
return 0; 
} 
