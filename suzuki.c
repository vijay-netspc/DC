#include <stdio.h> 
#include <stdlib.h> 
 
#define MAX 20 
 
int n; int RN[MAX];  
int LN[MAX];  
int tokenQueue[MAX]; 
int front = -1, rear = -1; 
int hasToken; 
int tokenHolder; 
void enqueue(int p) { 
 if (rear == MAX - 1) 
     return; 
 if (front == -1) 
     front = 0; 
 tokenQueue[++rear] = p; 
} 
int dequeue() { 
 if (front == -1 || front > rear) 
     return -1; 
 return tokenQueue[front++]; 
} 
void requestCS(int pid) { 
 RN[pid]++; 
 printf("Process %d is requesting CS\n", pid); 
 if (hasToken && tokenHolder == pid) { 
     printf("Process %d enters Critical Section\n", pid); 
     printf("Process %d exits Critical Section\n", pid); 
     LN[pid] = RN[pid]; 
     for (int i = 0; i < n; i++) { 
         if (RN[i] == LN[i] + 1) 
             enqueue(i); } 
     int next = dequeue(); 
     if (next != -1 && next != pid) { 
         hasToken = 1; 
         tokenHolder = next; 
         printf("Token passed to Process %d\n", next); } 
 } else { 
     printf("Process %d does not have a token. Added to queue.\n", pid); 
     enqueue(pid); 
 } 
} 
int main() { 
 printf("Enter number of processes: "); 
 scanf("%d", &n); 
 for (int i = 0; i < n; i++) { 
     RN[i] = 0; 
     LN[i] = 0; 
 } 
 printf("Enter initial token holder (0 to %d): ", n - 1); 
 scanf("%d", &tokenHolder); 
 hasToken = 1; 
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
             exit(0); }  
 return 0; 
}
