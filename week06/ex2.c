#include <stdio.h>


int main()
{
    int numProcess;
    printf("Enter number of processes: ");
    scanf("%d", &numProcess);

    int bt[10] = {0};

    printf("Burst time: ");
    for ( int i = 0; i < numProcess; i++) {
        scanf("%d", &bt[i]);
    }
    
    
    float totalTime = 0;
    int wt[10] = {0};
    for (int i = 1; i < numProcess; i++) {
        wt[i] = 0;
        for(int j = 0; j < i; j++)
            wt[i] += bt[i];
        totalTime += wt[i];
    }
    
    float avgWT=totalTime/numProcess;      
    totalTime = 0;
  
    printf("ProcessNumber\t BT\t  WT\t TAT\t\n\n");
    int tat[10] = {0};
    
    for(int i = 0; i < numProcess; i++){
        tat[i] = bt[i] + wt[i];   
        totalTime += tat[i];
        printf("Process%d\t %d\t %d\t %d\n", i+1, bt[i],wt[i],tat[i]);
    }
    
    float avgTAT=totalTime/numProcess;
    printf("\nAverage Turnaround time = %f\n%s%f", avgTAT, "Average Waiting time = ", avgWT);
    
    return 0;
}
