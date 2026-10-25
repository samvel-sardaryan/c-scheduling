# Process Scheduling Simulator (FCFS and SJF)

A C program that simulates two non-preemptive CPU scheduling algorithms: First Come First Served (FCFS) and Shortest Job First (SJF). For each algorithm it prints a Gantt chart, the waiting, turnaround and response time of every process, and the averages.

## How to compile and run

    gcc -Wall -Wextra -o scheduler scheduler.c
    ./scheduler

Enter the number of processes (1 to 100), then the arrival time and burst time of each process, separated by a space.

## Example

    Enter the number of processes: 4
    Enter the arrival time and burst time for process 1: 0 8
    Enter the arrival time and burst time for process 2: 1 4
    Enter the arrival time and burst time for process 3: 2 9
    Enter the arrival time and burst time for process 4: 3 5

    === First Come First Served (FCFS) ===
    Gantt Chart: | P1   | P2   | P3   | P4   |
                 0      8      12     21     26

    PID     AT     BT     WT     TAT    RT
    1       0      8      0      8      0
    2       1      4      7      11     7
    3       2      9      10     19     10
    4       3      5      18     23     18

    Average Waiting Time: 8.75
    Average Turnaround Time: 15.25
    Average Response Time: 8.75

    === Shortest Job First (SJF) ===
    Gantt Chart: | P1   | P2   | P4   | P3   |
                 0      8      12     17     26

    PID     AT     BT     WT     TAT    RT
    1       0      8      0      8      0
    2       1      4      7      11     7
    4       3      5      9      14     9
    3       2      9      15     24     15

    Average Waiting Time: 7.75
    Average Turnaround Time: 14.25
    Average Response Time: 7.75

The numbers under the Gantt chart are the times when each process starts and finishes. IDLE appears when the CPU has no process to run.

## How the algorithms work

**FCFS** runs the processes in the order they arrive. Processes with the same arrival time run in the order they were entered.

**SJF** is non-preemptive. Every time the CPU becomes free, it picks the process with the shortest burst time among the ones that have already arrived. If two burst times are equal, the earlier arrival goes first, and if the arrival times are equal too, the one entered first. Once a process starts, it runs to the end.

In both algorithms, if no process has arrived yet, the CPU stays idle until one does.

## How the times are calculated

- Completion time = start time + burst time
- Turnaround time = completion time - arrival time
- Waiting time = turnaround time - burst time
- Response time = start time - arrival time

Both algorithms are non-preemptive, so the response time is always equal to the waiting time.

## Edge cases

- Processes with the same arrival time
- Processes with the same burst time
- Gaps where the CPU is idle
- Processes entered in any order, not only by arrival time
- Invalid input: a number of processes outside 1 to 100, input that is not a number, a negative arrival time or a burst time below 1 prints an error message