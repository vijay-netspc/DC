#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe(fd);  // create pipe

    if (fork() == 0) {
        // Child process (reader)
        char msg[100];
        read(fd[0], msg, sizeof(msg));  // blocks until data comes
        printf("Child received: %s\n", msg);
    } else {
        // Parent process (writer)
        char msg[] = "Hello from parent";
        write(fd[1], msg, sizeof(msg));
        printf("Parent sent message\n");
    }

    return 0;
}
