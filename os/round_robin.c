#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int arrival_time;
};

void roundRobin(struct Process processes[], int n, int time_quantum) {
    int remaining_time[n];
    int wt[n], tat[n];
    int completed = 0;
    int current_time = 0;
    int flag = 0;

    for (int i = 0; i < n; ++i) {
        remaining_time[i] = processes[i].burst_time;
        wt[i] = 0;
    }

    struct {
        int process_id;
        int start_time;
        int end_time;
    } gantt_chart[100];
    int gc_count = 0;

    while (completed < n) {
        flag = 0;

        for (int i = 0; i < n; ++i) {
            if (remaining_time[i] > 0 && processes[i].arrival_time <= current_time) {
                flag = 1;

                gantt_chart[gc_count].process_id = processes[i].id;
                gantt_chart[gc_count].start_time = current_time;

                if (remaining_time[i] <= time_quantum) {
                    current_time += remaining_time[i];
                    remaining_time[i] = 0;
                    completed++;

                    tat[i] = current_time - processes[i].arrival_time;
                    wt[i] = tat[i] - processes[i].burst_time;

                    printf("Process P%d completed at time %d\n", processes[i].id, current_time);
                    printf("Process P%d WT = %d, TAT = %d\n", processes[i].id, wt[i], tat[i]);
                } 

                else {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }

                gantt_chart[gc_count].end_time = current_time;
                gc_count++;
            }
        }
        if (!flag) {
            current_time++;
        }
    }

    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; ++i) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;

    printf("Average Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);

    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gc_count; ++i) {
        printf(" P%d |", gantt_chart[i].process_id);
    }
    printf("\n");

    printf("0");
    for (int i = 0; i < gc_count; ++i) {
        printf("  %d", gantt_chart[i].end_time);
    }
    printf("\n");
}

int main() {
    int n, time_quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        processes[i].id = i + 1;
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    printf("\nRound Robin Scheduling:\n");
    roundRobin(processes, n, time_quantum);

    return 0;
}
