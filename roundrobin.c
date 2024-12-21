  #include <stdio.h>
#define MAX 10
int main() {
     
      
     
    int n, i, time = 0, remain;
    float sum = 0, wt;
    int pid[MAX], arv[MAX], bt[MAX], remaining_bt[MAX];
    int finish[MAX];  
    int gantt_pid[MAX * MAX];   
    int gantt_time[MAX * MAX]; 
    int gantt_index = 0;
    int tq;  

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    remain = n;

    printf("Enter the process IDs:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pid[i]);
    }

    printf("Enter the arrival times of processes:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arv[i]);
    
 printf("Enter the burst times of processes:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        remaining_bt[i] = bt[i];
    }
printf("Enter the Time Quantum: ");
    scanf("%d", &tq);
while (remain > 0) {
        int executed = 0;  
for (i = 0; i < n; i++) {
            if (remaining_bt[i] > 0 && arv[i] <= time) {
                 if (gantt_index == 0 || gantt_pid[gantt_index - 1] != pid[i]) {
                    gantt_pid[gantt_index] = pid[i];
                    gantt_time[gantt_index] = time;
                    gantt_index++;
                }
                    if (remaining_bt[i] > tq) {
                    time += tq;
                    remaining_bt[i] -= tq;
                } else {
                    time += remaining_bt[i];
                    remaining_bt[i] = 0;
                    finish[i] = time;
                    remain--;
                }
                executed = 1;
            }
        }
          if (!executed) {
               int next_arrival_time = -1;
              for (i = 0; i < n; i++) {
                if (remaining_bt[i] > 0) {
                    if (next_arrival_time == -1 || arv[i] < next_arrival_time) {
                        next_arrival_time = arv[i];
                   }
   }
            time = next_arrival_time > time ? next_arrival_time : time + 1;
        }
    }
 gantt_time[gantt_index] = time;
 printf("\nGantt Chart:\n");
    for (i = 0; i < gantt_index; i++) {
        printf("%d---P%d---", gantt_time[i], gantt_pid[i]);
    }
    printf("%d\n", time);
 printf("\nProcess Table\n");
    printf("ID\tAT\tBT\tCT\tTAT\tWT\n");
    sum = 0;
    for (i = 0; i < n; i++) {
        int tat = finish[i] - arv[i];   
        int waiting_time = tat - bt[i];  
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], arv[i], bt[i], finish[i], tat, waiting_time);
        sum += waiting_time;
    }
    wt = sum / n;
    printf("\nThe average waiting time is %.2f\n", wt);

    return 0;
}
}}
