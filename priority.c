#include <stdio.h>
#include <string.h>
#include<stdlib.h>
struct process
{
    char name[10];
    int at,bt,wt,tt,ct,status,pt;
}p[20];
struct done
{
    char name[10];
    int st,ct;
}d[20];
int main()
{
    int n,min,f,num=0,idle,ls;
    float totalwt=0,totaltt=0;
    printf("Enter the limit of process");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        printf("Enter the name of process");
        scanf("%s", p[i].name);
        printf("Enter the arrival time and burst time of process");
        scanf("%d %d",&p[i].at,&p[i].bt);
        printf("Enter the priority of process");
        scanf("%d",&p[i].pt);
        p[i].status=0;
    }
    for(int i=0,ls=0,idle=0;ls<n;)
    {
        f=0;
        for(int j=0;j<n;j++)
        {
            if(p[j].at<=i && p[j].status==0)
            {
                if(!f || p[j].pt<p[min].pt)
                {
                    min=j;
                    f=1;
                }
                else if(p[j].pt==p[min].pt)
                {
                    if(p[j].bt<p[min].bt)
                    {
                        min=j;
                        f=1;
                    }
                }
            }
        }
        if(f) 
        {
            if(idle) 
            { 
                d[num].ct=i;
                idle=0;
                num++;
            }
            strcpy(d[num].name,p[min].name);
            p[min].status=1;
            d[num].st=i;
            d[num].ct=i+p[min].bt;
            i=d[num].ct;
            p[min].ct=d[num].ct;
            p[min].tt=p[min].ct-p[min].at;
            p[min].wt=p[min].tt-p[min].bt;
            totalwt+=p[min].wt;
            totaltt+=p[min].tt;
            num++;
            ls++;
        }
        else 
        {
            if(!idle) 
            {
                strcpy(d[num].name,"Idle");
                d[num].st = i;
                idle = 1;
            }
            i++; 
        }
    }
    int a;
    
    printf("\nGantt chart\n");
    for (int i = 0; i < num; i++) 
    {
    	a=d[i].ct-d[i].st;
        printf("----");
        for(int z=1;z<=a;z++) 
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
        	printf("----");
        	for (int z = 1; z <=a; z++) 
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