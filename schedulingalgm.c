#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 20
#define Q 3

typedef struct {
    int pid, at, bt, pr;
    int ct, tat, wt, rt;
} Process;

// Standard print for FCFS, SJF, and Round Robin
void printResult(Process p[], int n, char name[]) {
    float totalWT = 0, totalTAT = 0;

    printf("\n========== %s ==========\n", name);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("---------------------------------------\n");
    printf("Average Turnaround Time : %.2f\n", totalTAT / n);
    printf("Average Waiting Time    : %.2f\n", totalWT / n);
}

// Specialized print for Priority Scheduling to show the Priority Number
void printPriorityResult(Process p[], int n, char name[]) {
    float totalWT = 0, totalTAT = 0;

    printf("\n========== %s ==========\n", name);
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("-----------------------------------------------\n");
    printf("Average Turnaround Time : %.2f\n", totalTAT / n);
    printf("Average Waiting Time    : %.2f\n", totalWT / n);
}

void FCFS(Process p[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    printResult(p, n, "FCFS Scheduling");
}

void SJF(Process p[], int n) {
    int completed = 0, time = 0;
    int done[MAX] = {0};

    while (completed < n) {
        int idx = -1, minBT = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = 1;
        completed++;
    }
    printResult(p, n, "SJF Scheduling");
}

void Priority(Process p[], int n) {
    int completed = 0, time = 0;
    int done[MAX] = {0};

    while (completed < n) {
        int idx = -1;
        int minPr = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].pr < minPr) {
                minPr = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = 1;
        completed++;
    }
    printPriorityResult(p, n, "Priority Scheduling");
}

void RoundRobin(Process p[], int n) {
    int time = 0, completed = 0;
    int queue[500], front = 0, rear = 0;
    int inQueue[MAX] = {0};

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && p[i].at <= time && p[i].rt > 0) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (front == rear) { 
            time++;
            continue;
        }

        int i = queue[front++];
        int exec = (p[i].rt > Q) ? Q : p[i].rt;
        
        p[i].rt -= exec;
        time += exec;

        for (int j = 0; j < n; j++) {
            if (!inQueue[j] && p[j].at <= time && p[j].rt > 0) {
                queue[rear++] = j;
                inQueue[j] = 1;
            }
        }

        if (p[i].rt > 0) {
            queue[rear++] = i;
        } else {
            completed++;
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
        }
    }
    printResult(p, n, "Round Robin (Q = 3)");
}

int main() {
    int n;
    Process p[MAX], temp[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("PID: "); scanf("%d", &p[i].pid);
        printf("Arrival Time: "); scanf("%d", &p[i].at);
        printf("Burst Time: "); scanf("%d", &p[i].bt);
        printf("Priority: "); scanf("%d", &p[i].pr);
    }

    memcpy(temp, p, sizeof(Process) * n);
    FCFS(temp, n);

    memcpy(temp, p, sizeof(Process) * n);
    SJF(temp, n);

    memcpy(temp, p, sizeof(Process) * n);
    Priority(temp, n);

    memcpy(temp, p, sizeof(Process) * n);
    RoundRobin(temp, n);

    return 0;
}
