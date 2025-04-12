#include<stdio.h>

struct Process{
  int pid;
  int arrival_t;
  int burst_t;
  int completion_t;
  int turnAround_t;
  int waiting_t;
  int response_t;
  int remaining_t;
  int priority;
};

int main(){
  int n;
  printf("Enter no of process: ");
  scanf("%d", &n);

  struct Process p[n];

  for(int i=0; i<n; i++){
    p[i].pid = i+1;

    printf("Enter p%d Arrival Time: ", i+1);
    scanf("%d",&p[i].arrival_t);
    printf("Enter p%d Burt Time: ", i+1);
    scanf("%d",&p[i].burst_t);
    printf("Enter p%d Priority: ", i+1);
    scanf("%d",&p[i].priority);

    p[i].remaining_t = p[i].burst_t;
  }

  int completed = 0;
  int current_t = 0;
  int t_tat = 0, t_wt = 0, t_rt = 0;

  printf(" process | priority | Arrival | Burst | Completion | turnAround | Waiting | Response \n");

  while(completed < n){
    int idx = -1, min_p = 1e9;
    for(int i = 0; i< n; i++){
      if(p[i].arrival_t <= current_t && p[i].remaining_t != 0 && p[i].priority < min_p){
        idx = i;
        min_p = p[i].priority;
      }
    }

    if(idx != -1){
      
      p[idx].completion_t = current_t + p[idx].burst_t;
      p[idx].turnAround_t = p[idx].completion_t - p[idx].arrival_t;
      p[idx].response_t = current_t - p[idx].arrival_t;
      p[idx].waiting_t = p[idx].turnAround_t - p[idx].burst_t;
      p[idx].remaining_t = 0;
      completed++;
      current_t += p[idx].burst_t;

      t_tat += p[idx].turnAround_t;
      t_rt += p[idx].response_t;
      t_wt += p[idx].waiting_t;

      printf("    %d    |   %d    |   %d    |   %d    |   %d    |   %d    |   %d    |   %d    \n", p[idx].pid, p[idx].priority, p[idx].arrival_t, p[idx].burst_t, p[idx].completion_t, p[idx].turnAround_t, p[idx].waiting_t, p[idx].response_t);
      
    }else{
      current_t++;
    }
  }

  printf("Average turn around time : %d", (float)t_tat/n);
  printf("Average waiting time : %d", (float)t_wt/n);
  printf("Average response time : %d", (float)t_rt/n);

  return 0;
}