#include <stdio.h>
  #define MAX 10

int main() {
     
      
     
    int n, i, j;
    float sum = 0, wt;
    int pid[MAX], arv[MAX], bt[MAX];
    int start[MAX], finish[MAX], remaining_bt[MAX];
    int currentTime = 0, completed = 0;
    int is_completed[MAX] = {0};
    int shortest = -1;
    int gantt_pid[MAX * MAX];
    int gantt_time[MAX * MAX];
    int gantt_index = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

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

    while (completed < n) {
        shortest = -1;

       
        for (i = 0; i < n; i++) {
            if (arv[i] <= currentTime && !is_completed[i] && (shortest == -1 || remaining_bt[i] < remaining_bt[shortest])) {
                shortest = i;
            }
        }

        if (shortest != -1) {
            if (remaining_bt[shortest] == bt[shortest]) {
                start[shortest] = currentTime;
            }

           
            if (gantt_index == 0 || gantt_pid[gantt_index - 1] != pid[shortest]) {
                gantt_pid[gantt_index] = pid[shortest];
                gantt_time[gantt_index] = currentTime;
                gantt_index++;
            }

            remaining_bt[shortest]--;
            currentTime++;

            if (remaining_bt[shortest] == 0) {
                finish[shortest] = currentTime;
                is_completed[shortest] = 1;
                completed++;
            }
        } else {
            currentTime++;
        }
    }

   
    gantt_time[gantt_index] = currentTime;

  
    printf("\nGantt Chart:\n");
    for (i = 0; i < gantt_index; i++) {
        printf("%d---P%d---", gantt_time[i], gantt_pid[i]);
    }
    printf("%d\n", currentTime);

    printf("\nProcess Table\n");
    printf("ID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], arv[i], bt[i], finish[i], finish[i] - arv[i], finish[i] - arv[i] - bt[i]);
        sum += (finish[i] - arv[i] - bt[i]);
    }
    wt = sum / n;
    printf("\nThe average waiting time is %f\n", wt);

    return 0;
}
