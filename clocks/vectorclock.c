#include <stdio.h> 
int max(int a, int b) { 
    return (a > b) ? a : b; 
} 
int main() { 
    int n, e; 
    int VC[10][10] = {0}; 
    int msg[10]; 
 
    printf("Enter number of processes: "); 
    scanf("%d", &n); 
 
    printf("Enter number of events: "); 
    scanf("%d", &e); 
 
    for (int i = 0; i < e; i++) { 
        int pid, type; 
 
        printf("\nEvent %d\n", i + 1); 
        printf("Enter process ID (0 to %d): ", n - 1); 
        scanf("%d", &pid); 
 
        printf("Event type (1-Internal, 2-Send, 3-Receive): "); 
        scanf("%d", &type); 
 
        if (type == 1 || type == 2) { 
            VC[pid][pid]++; 
        } 
else if (type == 3) { 
printf("Enter received vector clock:\n"); 
for (int j = 0; j < n; j++) 
scanf("%d", &msg[j]); 
for (int j = 0; j < n; j++) 
VC[pid][j] = max(VC[pid][j], msg[j]); 
VC[pid][pid]++; 
} 
printf("Vector Clocks:\n"); 
for (int p = 0; p < n; p++) { 
printf("P%d [ ", p); 
for (int j = 0; j < n; j++) 
printf("%d ", VC[p][j]); 
printf("]\n"); 
} 
} 
return 0; 
}
