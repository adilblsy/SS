#include <stdio.h>
#include <stdlib.h>

struct procees
{
        int pid;
	int at;
        int bt;
        int ct;
        int tat;
        int wt;
	int prio;
}p[10],temp;

int n;

void userinput()
{
	int i;

	printf("Enter number of processes: ");
	scanf("%d",&n);

	printf("Enter process id, arrival time and burst time of all processes\n");
	for(i=0;i<n;i++)
	{
		scanf("%d%d%d",&p[i].pid,&p[i].at,&p[i].bt);
	}
}

void fcfs()
{
	int i,j,t=0;
	float avg_wt=0,avg_tat=0;

	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(p[j].at>p[j+1].at)
			{
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}

	for(i=0;i<n;i++)
	{
		if(p[i].at>t)
		{
			t=p[i].at;
		}

		p[i].ct=t+p[i].bt;
		t=p[i].ct;
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].tat-p[i].bt;
		avg_tat+=p[i].tat;
		avg_wt+=p[i].wt;
	}

	printf("\nFCFS SCHEDULING\nPID	|	AT	| 	BT	|	CT	|	TAT	|	WT\n");
	for(i=0;i<n;i++)
	{
		printf("\n%d	|	%d	|	%d	|	%d	|	%d	|	%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
	}
	printf("\nTotal turnaroundtime: %.2f\nAverage turnaround time: %.2f\n\nTotal waiting time: %.2f\nAverage waiting time: %.2f\n\n",avg_tat,avg_tat/n,avg_wt,avg_wt/n);
}

void sjf()
{
	int i,j,t=0;
        float avg_wt=0,avg_tat=0;

        for(i=0;i<n-1;i++)
        {
                for(j=0;j<n-i-1;j++)
                {
                        if(p[j].at>p[j+1].at || (p[j].at==p[j+1].at && p[j].bt>p[j+1].bt))
                        {
                                temp=p[j];
                                p[j]=p[j+1];
                                p[j+1]=temp;
                        }
                }
        }

        for(i=0;i<n;i++)
        {
                if(p[i].at>t)
                {
                        t=p[i].at;
                }

		for(j=i+1;j<n;j++)
		{
			if(p[j].at<=t && p[j].bt<p[i].bt)
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
		}

                p[i].ct=t+p[i].bt;
                t=p[i].ct;
                p[i].tat=p[i].ct-p[i].at;
                p[i].wt=p[i].tat-p[i].bt;
                avg_tat+=p[i].tat;
                avg_wt+=p[i].wt;
        }

        printf("\nSJF SCHEDULING\nPID     |       AT      |       BT      |       CT      |       TAT     |       WT\n");
        for(i=0;i<n;i++)
        {
                printf("\n%d	|       %d	|       %d	|       %d	|       %d	|	%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
        }
        printf("\nTotal turnaroundtime: %.2f\nAverage turnaround time: %.2f\n\nTotal waiting time: %.2f\nAverage waiting time: %.2f\n\n",avg_tat,avg_tat/n,avg_wt,avg_wt/n);
}

void prioinput()
{
	int i;

	printf("Enter priority of all processes\n");
        for(i=0;i<n;i++)
        {
                scanf("%d",&p[i].prio);
        }
	return;
}

void prio()
{
	int i,j,t=0;
        float avg_wt=0,avg_tat=0;

        for(i=0;i<n-1;i++)
        {
                for(j=0;j<n-i-1;j++)
                {
                        if(p[j].at>p[j+1].at || (p[j].at==p[j+1].at && p[j].prio>p[j+1].prio))
                        {
                                temp=p[j];
                                p[j]=p[j+1];
                                p[j+1]=temp;
                        }
                }
        }

        for(i=0;i<n;i++)
        {
                if(p[i].at>t)
                {
                        t=p[i].at;
                }

                for(j=i+1;j<n;j++)
                {
                        if(p[j].at<=t && p[j].prio<p[i].prio)
                        {
                                temp=p[i];
                                p[i]=p[j];
                                p[j]=temp;
                        }
                }

                p[i].ct=t+p[i].bt;
                t=p[i].ct;
                p[i].tat=p[i].ct-p[i].at;
                p[i].wt=p[i].tat-p[i].bt;
                avg_tat+=p[i].tat;
                avg_wt+=p[i].wt;
        }

        printf("\nPRIORITY SCHEDULING\nPID     |       AT      |       BT      |       CT      |       TAT     |       WT\n");
        for(i=0;i<n;i++)
        {
                printf("\n%d	|       %d	|       %d	|       %d	|       %d	|       %d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
        }
        printf("\nTotal turnaroundtime: %.2f\nAverage turnaround time: %.2f\n\nTotal waiting time: %.2f\nAverage waiting time: %.2f\n\n",avg_tat,avg_tat/n,avg_wt,avg_wt/n);
}

void rdrb()
{
	int tq;

	printf("Enter time quantum: ");
	scanf("%d",&tq);

	int i,j,t=0,rem=n,rem_bt[10];
        float avg_wt=0,avg_tat=0;

	for(i=0;i<n;i++)
	{
		rem_bt[i]=p[i].bt;
	}

	int q[10],f=0,r=0;
	int visited[10]={0};

	for(i=0;i<n;i++)
	{
		if(p[i].at<=t)
                {
                        q[r++]=i;
			visited[i]=1;
                }
	}

	while(rem>0)
	{
		i=q[f];
		f=(f+1)%10;

                if(rem_bt[i]>0)
                {
			if(rem_bt[i]>tq)
                        {
				t+=tq;
				rem_bt[i]-=tq;
			}
			else
			{
				t+=rem_bt[i];
                		p[i].ct=t;
                		rem_bt[i]=0;
				rem--;
			}

			for(j=0;j<n;j++)
			{
				if(p[j].at<=t && !visited[j])
				{
					q[r]=j;
					r=(r+1)%10;
					visited[j]=1;
				}
			}

			if(rem_bt[i]>0)
			{
				q[r]=i;
				r=(r+1)%10;
			}
		}
	}

	for(i=0;i<n;i++)
        {
                p[i].tat=p[i].ct-p[i].at;
                p[i].wt=p[i].tat-p[i].bt;
                avg_tat+=p[i].tat;
                avg_wt+=p[i].wt;
        }

        printf("\nROUND ROBIN SCHEDULING\nPID     |       AT      |       BT      |       CT      |       TAT     |       WT\n");
        for(i=0;i<n;i++)
        {
                printf("\n%d	|	%d	|       %d	|       %d	|       %d	|       %d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
        }
        printf("\nTotal turnaroundtime: %.2f\nAverage turnaround time: %.2f\n\nTotal waiting time: %.2f\nAverage waiting time: %.2f\n\n",avg_tat,avg_tat/n,avg_wt,avg_wt/n);
}

void main()
{
        int c;

        while(1)
        {
                printf("CHOOSE\n1-FCFS\n2-SJF\n3-PRIORITY\n4-ROUND ROBIN\n5-EXIT\n");
                scanf("%d",&c);

                switch(c)
                {
                        case 1: userinput();
                                fcfs();
				break;
                        case 2: userinput();
                                sjf();
				break;
                        case 3: userinput();
				prioinput();
                                prio();
				break;
                        case 4: userinput();
                                rdrb();
				break;
                        case 5: return;
                        default: printf("Invalid choice\n\n");
                }
        }
}
