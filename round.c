#include<stdio.h>
#include<string.h>
int q[100],front=-1,rear=-1,t,i,j;
struct process{
    char name[20];
    int at,bt,wt,status,tt,left;
}p[20];
struct done{
    int st,ct;
    char name[20];
}d[20];
void enqueue(int j)
{
    if (rear == -1) 
        front = rear = 0;
    else
        rear++;
    q[rear] = j;
}
int dequeue()
{
    if(front==-1 || front>rear){
        printf("Under flow");
        return -1;
    }
    int item=q[front];
    front++;
    if(front>rear)
        front=rear=-1;
    return item;
}
void main()
{
    int n,num=0,idle=0,ls=0;
    float totalwt=0,totaltt=0;
    printf("Enter the Time Quantum");
    scanf("%d",&t);
    printf("Enter the limit of process");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter the name of process");
        scanf("%s", p[i].name);
        printf("Enter the arrival time and burst time of process");
        scanf("%d %d",&p[i].at,&p[i].bt);
        p[i].left=p[i].bt;
        p[i].status=0;
    }
    for(i=0;ls<n;)
    {
        for(j=0;j<n;j++)
        {
            if(p[j].status==0 && p[j].at<=i)
            {
                enqueue(j);
                p[j].status=1;
            }
        }
        if(idle==0 && front==-1)
        {
            strcpy(d[num].name,"idle");
            d[num].st=i;
            idle=1;
            i++;
        }
        else if(front!=-1)
        {
            if(idle==1)
            {
                d[num].ct=i;
                idle=0;
                num++;
            }
            int k=dequeue();
            if(k==-1)
            {
                i++;
                continue;
            }
            d[num].st=i;
            strcpy(d[num].name,p[k].name);
            if(p[k].left<=t)
            {
                d[num].ct=i+p[k].left;
                i=d[num].ct;
                p[k].tt=i-p[k].at;
                p[k].wt=p[k].tt-p[k].bt;
                totaltt+=p[k].tt;
                totalwt+=p[k].wt;
                p[k].status=2;
                num++;
                ls++;
            }
            else
            {
                d[num].ct=i+t;
                i=i+t;
                p[k].left=p[k].left-t;
                num++;
                for(j=0;j<n;j++)
                {
                    if(p[j].status==0&&p[j].at<=i)
                    {
                        enqueue(j);
                        p[j].status=1;
                    }
                }
                enqueue(k);
            }
        }
        else
            i++;
    }
    int a;
    printf("\nGantt chart\n");
    for (int i = 0; i < num; i++) 
    {
    	a=d[i].ct-d[i].st;
        printf("---");
        for(int z=1;z<=a;z++) 
            	printf("-");
        printf("-");
    }
    printf("\n");
	for (int i = 0; i < num; i++) 
	{
	    a=d[i].ct-d[i].st;
        	printf("|%s", d[i].name);
        	for (int z = 1; z <=a; z++) 
            		printf(" ");
            
    	}
    	printf("|\n");
	for (int i = 0; i < num; i++) 
	{
	        a=d[i].ct-d[i].st;
        	printf("---");
        	for (int z = 1; z <=a; z++) 
			    printf("-");
            printf("-");
    	}
    	printf("\n");
	for (int i = 0; i < num; i++) 
	{
	        a=d[i].ct-d[i].st;
        	printf("%d", d[i].st);
        	for (int z = 0; z <=a; z++) 
            	printf(" ");
            printf(" ");
            printf(" ");
    }
    printf("%d",d[num-1].ct);
    printf("\n");
    printf("Average waiting time: %f\n", totalwt / n);
    printf("Average turnaround time: %f\n", totaltt / n);
}