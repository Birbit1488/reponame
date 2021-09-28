#include <stdio.h>


int main()
{
    int numProcess;
    printf("Enter number of processes:");
    scanf("%d", &numProcess);
    int at[10] = {0};
    int bt[10] = {0};

    printf("Enter both arrival and burst time for each process:\n");
 
    for ( int i = 0; i < numProcess; i++) {
        printf("Arrival time: %d", i+1);
        scanf("%d", &at[i]);
        printf("Burst time: %d", i+1);
        scanf("%d", &bt[i]);
    }
    
    int sum = 0;
    int ct[10] = {0};
    for (int i = 0; i < numProcess; i++) {
        if (i == 0) //start case
            sum += at[i];
        sum += bt[i];
        ct[i] += sum;
    }
    
    int tat[10] = {0};
    float totalTat = 0;
    for (int i = 0; i < numProcess; i++) {
        tat[i] = ct[i] - at[i];
        totalTat += tat[i];
    }
    
    float totalWt = 0;
    int wt[10] = {0};
    for (int i = 0; i < numProcess; i++) {
        wt[i] = tat[i] - bt[i];
        totalWt += wt[i];
    }
    
    printf("ProcessNumber\t AT\t BT\t CT\t TAT\t WT\t\n\n");
    
    for (int i = 0; i < numProcess; i++) {
        printf("Process%d\t %d\t %d\t %d\t %d\t %d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    
    printf("\nAverage Turnaround time = %f\n%s%f\n", totalTat/numProcess, "Average Waiting time = ", totalWt/numProcess);
    
    return 0;
}
