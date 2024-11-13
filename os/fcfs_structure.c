#include <stdio.h>

typedef struct{
    int name;
    int arrival;
    int burst;
    int completion;
    int waiting;
    int turnaround;
}Process;

int main(){
    Process processes[] = {
        {1,0,8},
        {2,1,1},
        {3,2,3},
        {4,3,2},
        {5,4,6}
    };

    int n = sizeof(processes)/sizeof(Process);
    int current_time = 0;

    for(int i =0;i<n;i++){
        int execution_time = processes[i].burst;
        current_time += execution_time;

        processes[i].completion = current_time;
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
    }

    float avgwt = 0;
    float avgtat = 0;

    printf("Process\tArrivalTime\tBurstTime\tTurnaroundTime\tWaitingTime\n");
    for(int i=0;i<n;i++){
       printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n",processes[i].name,processes[i].arrival,processes[i].burst,processes[i].turnaround,processes[i].waiting);
       avgwt += processes[i].waiting;
       avgtat += processes[i].turnaround;
    }

    printf("Average wait time: %.2f \n",avgwt/n);
    printf("Average tunraround time: %.2f\n",avgtat/n);

    return 0;
}