#include <stdio.h>


int main()
{
    int numProcess;
    printf("Enter number of processes:");
    scanf("%d", &numProcess);
    int at[10] = {0};
    int bt[10] = {0};
    int tmp[10] = {0};

    printf("Enter arrival time and burst time for each process:\n");
 
    for ( int i = 0; i < numProcess; i++) {
        printf("Arrival time: %d", i+1);
        scanf("%d", &at[i]);
        printf("Burst time: %d", i+1);
        scanf("%d", &bt[i]);
        tmp[i] = bt[i];
    }
    int q = 0;
    printf("Enter quantum \n");
    scanf("%d", &q);
    
    int sum = at[0], cur = 0;
    int ct[10] = {0};
    int finished[10] = {0};
    int activeProcNum = numProcess;
     while (activeProcNum) {
        if(!finished[cur])
        {
            if (tmp[cur] > q)
            {
                tmp[cur] = tmp[cur] - q;
                sum += q;
            }
            else
            {
                sum += tmp[cur];
                ct[cur] = sum;
                activeProcNum--;
                finished[cur] = 1;
            }
        }
	cur++;
	if (cur >= numProcess)
		cur = 0;
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

