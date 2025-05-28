#include <stdio.h>

int main(){
    int n, i, j;
    int bt[20], p[20], prt[20];
    int wt[20], tat[20], rt[20];
    int temp;
    
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;
    
    printf("Enter the number of Patients: ");
    scanf("%d", &n);
    
    printf("Enter the Burst Time(Consultation) and Priority: \n");
    
    for(i =0; i<n;i++){
        printf("\nBT: ");
        scanf("%d",&bt[i]);
        printf("\nPRT: ");
        scanf("%d",&prt[i]);
        p[i] = i+1;
    }
    for(i=0;i<n-1;i++){
        for(j=i+1; j<n; j++){
            if(prt[i] > prt[j]){
                temp = prt[i];
                prt[i] = prt[j];
                prt[j] = temp;
                
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
     
    wt[0] = 0;
    rt[0] = 0;
    for(i =1; i<n; i++){
        wt[i] = wt[i-1]+bt[i-1];
        rt[i] = wt[i];
    }
    for(i = 0; i<n; i++){
        tat[i] = wt[i] + bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
        avg_rt += rt[i];
    }
     printf("\nPatient\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], prt[i], wt[i], tat[i], rt[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);
    printf("Average Response Time: %.2f\n", avg_rt / n);
    
     printf("\nGantt Chart:\n|");
    for(i = 0; i < n; i++) {
        printf(" P%d |", p[i]);
    }
    printf("\n0");
    int time = 0;
    for(i = 0; i < n; i++) {
        time += bt[i];
        printf("\t%d", time);
    }
    return 0;
}