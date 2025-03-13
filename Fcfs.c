#include<stdio.h>
#include<string.h>
struct process {
    char pname[20];
    int at, bt, wt, tt, ct, status; 
} p[20], t;
struct done{
    char name[20];
    int ct, st;
} d[20];
void main() 
{
	int n, i, j, id, k, num;
	float sumwt = 0.0, sumtt = 0.0, st, w;
	printf("\nEnter the number of processes: ");
	scanf("%d", &n);
    for (i=0;i<n;i++) 
    {
        printf("\nEnter the process name: ");
        scanf("%s", p[i].pname);
        printf("\nEnter the arrival time: ");
        scanf("%d", &p[i].at);
        printf("\nEnter the burst time: ");
        scanf("%d", &p[i].bt);
        p[i].status = 0;
    }
    for(i=0;i<n;i++)
    {
    	for(j=0;j<n-i-1;j++) 
    	{
            if(p[j].at>p[j+1].at) 
            {
                t=p[j];
                p[j]=p[j+1];
                p[j+1]=t;
            }
        }	
    }
	int idle=0;
    k=0; 
    num=0;
    for(i=0;k<n;) 
    {
        if(p[k].at<=i && p[k].status == 0) 
        {
            if(idle==1)
            {
                d[num].ct=i;
                num++;
            }
            strcpy(d[num].name,p[k].pname);
            d[num].st=i;
            d[num].ct=i+p[k].bt; 
            p[k].wt=d[num].st-p[k].at; 
            p[k].tt=p[k].wt+p[k].bt; 
            p[k].ct=d[num].ct; 
            i=d[num].ct; 
            p[k].status=1; 
            k++; 
            num++; 
        	idle=0;
        }
        else if(idle==0)
        {
            strcpy(d[num].name, "idle");
            d[num].st=i;
            i++;
        	idle = 1;
    	}
    	else             		
            i++; 
    }
	printf("\nGantt chart\n");
    for (i = 0; i < num; i++) 
    {
        printf("---");
        for (int z = 1; z <= p[i].bt; z++) 
    		printf("-");
	}
    printf("\n");
	for (i = 0; i < num; i++) 
	{
    	printf("|%s", d[i].name);
    	for (int z = 1; z <= p[i].bt; z++) 
    		printf(" ");
    }
    printf("|\n");
	for (i = 0; i < num; i++) 
	{
        printf("---");
    	for (int z = 1; z <= p[i].bt; z++) 
			printf("-");
    }
    printf("\n");
	for (i = 0; i < num; i++) 
	{
        printf("%d", d[i].st);
        for (int z = 0; z <= p[i].bt; z++) 
    		printf(" ");
	}
	printf("%d", d[num - 1].ct);
	printf("\n");
	for (i = 0; i < n; i++) 
	{
        sumwt = sumwt + p[i].wt;
    	sumtt = sumtt + p[i].tt;
	}	
    w = sumwt / n;
    st = sumtt / n;
    printf("\nAWT=%f\n", w);
    printf("ATT=%f\n", st);    
}