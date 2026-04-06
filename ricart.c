#include <stdio.h> 
#include <stdlib.h> 
#define MAX 20 
int n; 
int timestamp = 0; 
int requesting[MAX]; 
int requestTime[MAX]; 
void requestCS(int pid) { 
 timestamp++; 
 requesting[pid] = 1; 
 requestTime[pid] = timestamp; 
 printf("\nProcess %d sends REQUEST at time %d\n", pid, timestamp); 
 int replies = 0; 
 for (int i = 0; i < n; i++) { 
     if (i != pid) { 
         if (!requesting[i] || 
            (requestTime[pid] < requestTime[i]) || 
            (requestTime[pid] == requestTime[i] && pid < i)) { 
             printf("Process %d sends REPLY to Process %d\n", i, pid); 
             replies++; 
         } else { 
             printf("Process %d defers REPLY to Process %d\n", i, pid); } } } 
         if (replies == n - 1) { 
     printf("Process %d enters Critical Section\n", pid); 
     printf("Process %d exits Critical Section\n", pid); 
     requesting[pid] = 0; 
 
     for (int i = 0; i < n; i++) { 
         if (i != pid && requesting[i]) { 
             printf("Process %d now sends deferred REPLY to Process %d\n", pid, i); }  } } 
        
} 
 
int main() { 
 printf("Enter number of processes: "); 
 scanf("%d", &n); 
 
 for (int i = 0; i < n; i++) 
     requesting[i] = 0; 
 
 int choice, pid; 
 
 while (1) { 
     printf("\n1. Request Critical Section\n2. Exit\nEnter choice: "); 
     scanf("%d", &choice); 
 
     switch (choice) { 
         case 1: 
             printf("Enter process ID (0 to %d): ", n - 1); 
             scanf("%d", &pid); 
             requestCS(pid); 
             break; 
         case 2: 
             exit(0); 
     } 
 } 
 
 return 0; 
}
