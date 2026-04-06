#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int n;
int RN[MAX], LN[MAX];
int tokenQueue[MAX];
int front = 0, rear = -1;

int hasToken;
int tokenHolder;

void enqueue(int p) {
    if (rear < MAX - 1)
        tokenQueue[++rear] = p;
}

int dequeue() {
    if (front > rear)
        return -1;
    return tokenQueue[front++];
}

void requestCS(int pid) {
    RN[pid]++;
    printf("Process %d requesting CS\n", pid);

    if (hasToken && tokenHolder == pid) {
        printf("Process %d enters CS\n", pid);
        printf("Process %d exits CS\n", pid);

        LN[pid] = RN[pid];

        for (int i = 0; i < n; i++) {
            if (RN[i] == LN[i] + 1)
                enqueue(i);
        }

        int next = dequeue();
        if (next != -1 && next != pid) {
            tokenHolder = next;
            printf("Token passed to %d\n", next);
        }
    } else {
        enqueue(pid);
        printf("Process %d added to queue\n", pid);
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        RN[i] = 0;
        LN[i] = 0;
    }

    printf("Enter initial token holder: ");
    scanf("%d", &tokenHolder);

    hasToken = 1;

    int choice, pid;

    while (1) {
        printf("\n1.Request CS\n2.Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter pid: ");
                scanf("%d", &pid);
                requestCS(pid);
                break;
            case 2:
                exit(0);
        }
    }

    return 0;
}
