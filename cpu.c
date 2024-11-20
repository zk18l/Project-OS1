#include <stdio.h>
#include <limits.h>
void FCFS() {
    // Code for FCFS scheduling
}

void SJF() {
   int nprocess;
    int avgwt = 0, temp;

    // Input the number of processes
    printf("\nEnter the number of processes: ");
    scanf("%d", &nprocess);

    int burstTime[nprocess];
    int waitingTime[nprocess];
    int turnaroundTime[nprocess];

    // Input the burst time for each process
    printf("\nEnter the burst time for each process:\n");
    for (int i = 0; i < nprocess; i++) {
        printf("Burst time for P%d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    // Sort the processes based on burst time (SJF)
    for (int i = 0; i < nprocess - 1; i++) {
        for (int j = i + 1; j < nprocess; j++) {
            if (burstTime[i] > burstTime[j]) {
                // Swap burst times
                temp = burstTime[i];
                burstTime[i] = burstTime[j];
                burstTime[j] = temp;
            }
        }
    }

    // Calculate waiting time for each process
    waitingTime[0] = 0; // First process has zero waiting time
    for (int i = 1; i < nprocess; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    }

   
    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < nprocess; i++) {
        avgwt += waitingTime[i];
    
    }

    avgwt = avgwt / nprocess;
    

    // Print average waiting time and average turnaround time
    printf("\nAverage waiting time: %.2f\n", (float)avgwt);
    
    
}
void RR() {
    // Code for Round Robin scheduling
}

void PriorityScheduling() {
    // Code for Priority Scheduling
}

int main() {
    int choice;

    // Display available CPU scheduling algorithms to the user
    printf("Choose a CPU scheduling algorithm:\n"
           "1- FCFS\n"
           "2- SJF\n"
           "3- Round Robin\n"
           "4- Priority Scheduling\n"
           "Enter your choice (1-4): ");
    scanf("%d", &choice);

    
    switch(choice) {
        case 1:
            FCFS();
            break;
        case 2:
            SJF();
            break;
        case 3:
            RR();
            break;
        case 4:
            PriorityScheduling();
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}