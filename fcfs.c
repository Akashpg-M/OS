#include<stdio.h>

struct Process{
    int pid;
    int arrival_t;
    int burst_t;
    int completion_t;
};

void sortByArrivalTime(struct Process p[], int n){
  for(int i=0; i<n-1; i++){
    for(int j=i+1; j<n-i; j++){
      if(p[j-1].arrival_t > p[j].arrival_t){
        struct Process temp = p[j-1];
        p[j-1] = p[j];
        p[j] = temp;
      }
    }
  }
}

int main(){
    int n;
    struct Process p[20];

    printf("Enter no of process to add: ");
    scanf("%d", &n);

    for(int i=0; i<n-1; i++){
        p[i].pid = i+1;

        printf("Enter the arrival time: ");
        scanf("%d", &p[i].arrival_t);

        printf("Enter burst tiem: ");
        scanf("%d", &p[i].burst_t);
    }

    sortByArrivalTime(p, n);

    int currentTime = 0;
    int t_complitionTime = 0, t_turnAroundTime = 0, t_waitingTime = 0, t_responseTime = 0;
    printf("Process | ArrivalTime | burst Time | Complition | TurnAround | waiting Time | response Time\n");
    for(int i=0; i<n; i++){
        int complitionTime = 0, turnAroundTime = 0, waitingTime = 0, responseTime = 0;

        if(currentTime < p[i].arrival_t){
            currentTime = p[i].arrival_t;
        }

        complitionTime = currentTime + p[i].burst_t;
        turnAroundTime = complitionTime - p[i].arrival_t;
        waitingTime = turnAroundTime - p[i].burst_t;
        responseTime = waitingTime;

        printf("   %d    |     %d     |     %d     |     %d     |     %d     |     %d      |    %d     \n", p[i].pid, p[i].arrival_t, p[i].burst_t, complitionTime, turnAroundTime, waitingTime, responseTime);

        t_complitionTime += complitionTime;
        t_turnAroundTime += turnAroundTime;
        t_waitingTime += waitingTime;
        t_responseTime += responseTime;
    }

    printf("Average complition time : %d\n", t_complitionTime/n);
    printf("Average turnAround Time : %d\n", t_turnAroundTime/n);
    printf("Average Waiting Time : %d\n", t_waitingTime/n);
    printf("Average response Time : %d\n", t_responseTime/n);

    return 0;
}