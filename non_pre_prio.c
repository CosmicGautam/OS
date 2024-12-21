  #include <stdio.h>
#include <limits.h>  
#define MAX 10
int main() {
     
      
     
    int n, i, time = 0, remain, smallest;
    float sum = 0, avg_wt;
    int pid[MAX], arv[MAX], bt[MAX], remaining_bt[MAX], priority[MAX];
    int finish[MAX];  
    int gantt_pid[MAX * MAX];   
    int gantt_time[MAX * MAX];  
    int gantt_index = 0;
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
    }
    printf("Enter the burst times of processes:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        remaining_bt[i] = bt[i];
    }
   printf("Enter the priorities of processes (lower number means higher priority):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &priority[i]);
    }
priority[MAX - 1] = INT_MAX; 
while (remain > 0) {
        smallest = MAX - 1;  
        for (i = 0; i < n; i++) {
            if (arv[i] <= time && remaining_bt[i] > 0 && priority[i] < priority[smallest]) {
                smallest = i;
            }
        }
 if (smallest == MAX - 1) {   
            time++;
            continue;
        }
 if (gantt_index == 0 || gantt_pid[gantt_index - 1] != pid[smallest]) {
            gantt_pid[gantt_index] = pid[smallest];
            gantt_time[gantt_index] = time;
            gantt_index++;
        }
  time += remaining_bt[smallest];  
        remaining_bt[smallest] = 0;  
        finish[smallest] = time;  
        remain--; 
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
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], arv[i], bt[i], finish[i], tat, waiting_time);
        sum += waiting_time;
    }
avg_wt = sum / n;
    printf("\nThe average waiting time is %.2f\n", avg_wt);
return 0;
}
