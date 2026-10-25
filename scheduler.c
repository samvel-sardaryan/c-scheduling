#include <stdio.h>

#define MAX_PROCESSES 100

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

void print_gantt(struct Process p[], int n) {
    int time = 0;

    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++) {
        if (p[i].start_time > time) {
            printf("| IDLE ");
        }
        printf("| P%-3d ", p[i].pid);
        time = p[i].completion_time;
    }
    printf("|\n");

    time = 0;
    printf("             ");
    for (int i = 0; i < n; i++) {
        if (p[i].start_time > time) {
            printf("%-7d", time);
        }
        printf("%-7d", p[i].start_time);
        time = p[i].completion_time;
    }
    printf("%d\n", time);
}

void print_table(struct Process p[], int n) {
    int total_waiting = 0;
    int total_turnaround = 0;
    int total_response = 0;

    printf("PID     AT     BT     WT     TAT    RT\n");
    for (int i = 0; i < n; i++) {
        printf("%-8d%-7d%-7d%-7d%-7d%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time, p[i].response_time);
        total_waiting += p[i].waiting_time;
        total_turnaround += p[i].turnaround_time;
        total_response += p[i].response_time;
    }

    printf("\n");
    printf("Average Waiting Time: %.2f\n", (double)total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", (double)total_turnaround / n);
    printf("Average Response Time: %.2f\n", (double)total_response / n);
}

void fcfs(struct Process input[], int n) {
    struct Process p[MAX_PROCESSES];
    struct Process temp;
    int time = 0;

    for (int i = 0; i < n; i++) {
        p[i] = input[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time) {
            time = p[i].arrival_time;
        }
        p[i].start_time = time;
        p[i].completion_time = time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;
        time = p[i].completion_time;
    }

    printf("=== First Come First Served (FCFS) ===\n");
    print_gantt(p, n);
    printf("\n");
    print_table(p, n);
}

void sjf(struct Process input[], int n) {
    struct Process p[MAX_PROCESSES];
    struct Process order[MAX_PROCESSES];
    int done[MAX_PROCESSES];
    int completed = 0;
    int time = 0;

    for (int i = 0; i < n; i++) {
        p[i] = input[i];
        done[i] = 0;
    }

    while (completed < n) {
        int best = -1;

        for (int i = 0; i < n; i++) {
            if (done[i] == 0 && p[i].arrival_time <= time) {
                if (best == -1) {
                    best = i;
                } else if (p[i].burst_time < p[best].burst_time) {
                    best = i;
                } else if (p[i].burst_time == p[best].burst_time &&
                           p[i].arrival_time < p[best].arrival_time) {
                    best = i;
                }
            }
        }

        if (best == -1) {
            time++;
            continue;
        }

        p[best].start_time = time;
        p[best].completion_time = time + p[best].burst_time;
        p[best].turnaround_time = p[best].completion_time - p[best].arrival_time;
        p[best].waiting_time = p[best].turnaround_time - p[best].burst_time;
        p[best].response_time = p[best].start_time - p[best].arrival_time;
        time = p[best].completion_time;

        done[best] = 1;
        order[completed] = p[best];
        completed++;
    }

    printf("=== Shortest Job First (SJF) ===\n");
    print_gantt(order, n);
    printf("\n");
    print_table(order, n);
}

int main(void) {
    struct Process processes[MAX_PROCESSES];
    int n;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_PROCESSES) {
        printf("The number of processes must be between 1 and %d\n", MAX_PROCESSES);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        if (scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time) != 2) {
            printf("Please enter two whole numbers\n");
            return 1;
        }
        if (processes[i].arrival_time < 0 || processes[i].burst_time < 1) {
            printf("Arrival time must be 0 or more and burst time must be 1 or more\n");
            return 1;
        }
        processes[i].pid = i + 1;
        processes[i].start_time = 0;
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].response_time = 0;
    }

    printf("\n");
    fcfs(processes, n);
    printf("\n");
    sjf(processes, n);

    return 0;
}