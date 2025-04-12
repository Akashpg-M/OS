#include<stdio.h>

struct Process{
  int pid;
  int arrival_t;
  int burst_t;
  int remaining_t;
  int completion_t;
  int turnAround_t;
  int waiting_t;
  int response_t;
};

int main(){
  int n, completed = 0;
  printf("Enter no of process to add: ");
  scanf("%d", &n);

  struct Process p[n];

  for(int i=0; i<n; i++){
    p[i].pid = i+1;

    printf("Enter arrival time : ");
    scanf("%d", &p[i].arrival_t);

    printf("Enter burst time : ");
    scanf("%d", &p[i].burst_t);

    p[i].remaining_t = p[i].burst_t;
    p[i].response_t = -1;
  }

  int current_t = 0;
  int totalTAT=0, totalRT=0, totalWT=0;

  printf("process | arrival | burst | completion | turnAround | waiting | response \n");
  while(completed < n){
    int idx = -1;
    int minBurst = 1e9;
    for(int i=0; i<n; i++){
      if(p[i].arrival_t <= current_t && p[i].remaining_t > 0 && p[i].remaining_t < minBurst){
        minBurst = p[i].remaining_t;
        idx = i;
      }
    }

    if(idx != -1){
      if(p[idx].response_t == -1){
        p[idx].response_t = current_t - p[idx].arrival_t;
      }

      p[idx].remaining_t--;
      current_t++;

      if(p[idx].remaining_t == 0){
        p[idx].completion_t = current_t+1;
        p[idx].turnAround_t = p[idx].completion_t - p[idx].arrival_t;
        p[idx].waiting_t = p[idx].turnAround_t - p[idx].burst_t;
        completed++;

        totalTAT += p[idx].turnAround_t;
        totalWT += p[idx].waiting_t;
        totalRT += p[idx].response_t;

        printf("    %d    |    %d    |    %d    |    %d    |    %d    |    %d    |    %d    \n", p[idx].pid, p[idx].arrival_t, p[idx].burst_t, p[idx].completion_t, p[idx].turnAround_t, p[idx].waiting_t, p[idx].response_t);  
      }
    }else{
      current_t++;
    }
  }

  printf("\nAverage Turnaround Time: %.2f\n", (float)totalTAT / n);
  printf("Average Waiting Time   : %.2f\n", (float)totalWT / n);
  printf("Average Response Time  : %.2f\n", (float)totalRT / n);
  return 0;
}