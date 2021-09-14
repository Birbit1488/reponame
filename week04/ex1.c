#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
    int n;
    
    n = fork();
    if (n>0) {
        printf("Hello from parent [PID-%d]\n", getpid());
    }
    else if (n==0) {
        printf("Hello from child [PID-%d]\n", getpid());
    }
    else {
        printf("Error");
    }
    return 0;
}