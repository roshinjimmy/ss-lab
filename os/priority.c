#include <stdio.h>

struct Process {
    int processNo;
    int arrivalTime;
    int burstTime;
    int priority;
};

void sortProcesses(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[j].arrivalTime < proc[i].arrivalTime ||
                (proc[j].arrivalTime == proc[i].arrivalTime && proc[j].priority < proc[i].priority)) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void calculateWaitingTime(struct Process proc[], int wt[], int n) {
    wt[0] = 0;
    int pstart[n];
    pstart[0]=0;
    for (int i = 1; i < n; i++) {
        pstart[i]=pstart[i-1]+proc[i - 1].burstTime;
        wt[i] = pstart[i]-proc[i].arrivalTime;
    }
}

void calculateTurnaroundTime(struct Process proc[], int wt[], int tat[], int n) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].burstTime + wt[i];
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    int wt[n], tat[n];

    printf("Enter process details (arrival time, burst time, priority):\n");
    for (int i = 0; i < n; i++) {
        proc[i].processNo = i + 1;
        printf("P%d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
    }

    sortProcesses(proc, n);

    calculateWaitingTime(proc, wt, n);
    calculateTurnaroundTime(proc, wt, tat, n);

    float awt=0,atat=0;
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].processNo, proc[i].arrivalTime,
               proc[i].burstTime, proc[i].priority, wt[i], tat[i]);
    awt=awt+wt[i];
    atat=atat+tat[i];
        
    }
    printf("Average Waiting Time = %f\nAverage Turnaround Time = %f\n",awt/n,atat/n);
    return 0;
}