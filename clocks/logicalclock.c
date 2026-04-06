#include <stdio.h> 
 
int max(int a, int b) { 
    return (a > b) ? a : b; } 
 
int main() { 
    int n, e; 
    int clock[10] = {0}; 
    printf("Enter number of processes: "); 
    scanf("%d", &n); 
    printf("Enter number of events: "); 
    scanf("%d", &e); 
    for (int i = 0; i < e; i++) { 
        int pid, type, recv_clock; 
        printf("\nEvent %d\n", i + 1); 
        printf("Enter process ID (0 to %d): ", n - 1); 
        scanf("%d", &pid); 
        printf("Event type (1-Internal, 2-Send, 3-Receive): "); 
        scanf("%d", &type); 
        if (type == 1 || type == 2) { 
            clock[pid]++; 
        } 
        else if (type == 3) { 
            printf("Enter sender clock value: "); 
            scanf("%d", &recv_clock); 
            clock[pid] = max(clock[pid], recv_clock) + 1; 
        } 
        printf("Logical Clocks: "); 
        for (int j = 0; j < n; j++) 
            printf("P%d=%d ", j, clock[j]); 
        printf("\n"); 
    } 
 
    return 0; 
} 
