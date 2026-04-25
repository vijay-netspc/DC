#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd[2];
    pipe(fd);

    // Set read end as non-blocking
    fcntl(fd[0], F_SETFL, O_NONBLOCK);

    if (fork() == 0) {
        // Child process (reader)
        char msg[100];

        int n = read(fd[0], msg, sizeof(msg));

        if (n > 0)
            printf("Child received: %s\n", msg);
        else
            printf("No data available (non-blocking)\n");

    } else {
        // Parent process (writer)
        sleep(2);  // delay to show non-blocking effect

        char msg[] = "Hello from parent";
        write(fd[1], msg, sizeof(msg));
        printf("Parent sent message\n");
    }

    return 0;
}
