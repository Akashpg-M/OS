#include<stdio.h>

struct Process{
  int pid;
  int arrival_t;
  int burst_t;
  int completion_t;
  int turnAround_t;
  int waiting_t;
  int response_t;
  int visited;
};

int main(){
  int n;
  struct Process p[20];
  printf("Enter no of process : ");
  scanf("%d", &n);

  for(int i=0; i<n; i++){
    p[i].pid = i+1;
    printf("Enter p%d arrival time : ", i+1);
    scanf("%d", &p[i].arrival_t);
    printf("Enter p%d burst time : ",  i+1);
    scanf("%d", &p[i].burst_t);
    p[i].visited = 0;
  }

  printf(" Process | Arrival | Burst | Completion | TurnAround | Waiting | Response\n");

  int completed = 0;
  int totalTAT = 0, totalWT = 0, totalRT = 0, current_t = 0;
  
  while(completed < n){
    int idx = -1;
    int minBurst = 1e9;

    for(int i=0; i<n; i++){
      if(p[i].arrival_t <= current_t && p[i].visited == 0 && p[i].burst_t < minBurst){
        minBurst = p[i].burst_t;
        idx = i;
      }
    }

    if(idx != -1){
      p[idx].visited = 1;
      if(current_t < p[idx].arrival_t) current_t = p[idx].arrival_t;

      p[idx].completion_t = current_t + p[idx].burst_t;
      p[idx].turnAround_t = p[idx].completion_t - p[idx].arrival_t;
      p[idx].waiting_t = p[idx].turnAround_t - p[idx].burst_t;
      p[idx].response_t = p[idx].waiting_t;

      totalTAT += p[idx].turnAround_t;
      totalWT += p[idx].waiting_t;
      totalRT += p[idx].response_t;

      current_t = p[idx].completion_t;
      completed++;

      printf("    %d     |    %d    |    %d    |    %d    |     %d     |    %d    |    %d   \n", p[idx].pid, p[idx].arrival_t, p[idx].burst_t, p[idx].completion_t,
      p[idx].turnAround_t, p[idx].waiting_t, p[idx].response_t);
    }else{
      current_t++;
    }
  }

  printf("\nAverage Turnaround Time: %.2f", (float)totalTAT/n);
  printf("\nAverage Waiting Time   : %.2f", (float)totalWT/n);
  printf("\nAverage Response Time  : %.2f\n", (float)totalRT/n);

  return 0;
}