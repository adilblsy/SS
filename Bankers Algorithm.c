#include <stdio.h>

void main()
{
        int i,j,k,ind=0,p,r,alloc[10][10],max[10][10],avail[10],need[10][10],flag,safe[10],finish[10];

        printf("Enter number of processes: ");
        scanf("%d",&p);
        printf("Enter number of resources: ");
        scanf("%d",&r);
        printf("Enter allocation matrix:\n");
        for(i=0;i<p;i++)
        {
                for(j=0;j<r;j++)
                {
                        scanf("%d",&alloc[i][j]);
                }
        }
        printf("Enter max matrix:\n");
        for(i=0;i<p;i++)
        {
                for(j=0;j<r;j++)
                {
                        scanf("%d",&max[i][j]);
                }
        }
        printf("Enter avail matrix:\n");
        for(i=0;i<r;i++)
        {
                        scanf("%d",&avail[i]);
        }

        printf("\nNEED MATRIX\n");
        for(i=0;i<p;i++)
        {
                for(j=0;j<r;j++)
                {
                        need[i][j]=max[i][j]-alloc[i][j];
                        printf("%d\t",need[i][j]);
                }
                printf("\n");
        }
        printf("\n");

        for(i=0;i<p;i++)
        {
                finish[i]=0;
        }

        for(k=0;k<p;k++)
        {
                for(i=0;i<p;i++)
                {
                        if(finish[i]==0)
                        {
                                flag=0;
                                for(j=0;j<r;j++)
                                {
                                        if(need[i][j]>avail[j])
                                        {
                                                flag=1;
                                                break;
                                        }
                                        else
                                        {
                                                avail[j]+=alloc[i][j];
                                        }
                                }
                                if(flag==0)
                                {
                                        safe[ind++]=i;
                                        finish[i]=1;
                                }
                        }
                }
        }

        flag=1;
        for(i=0;i<p;i++)
        {
                if(finish[i]==0)
                {
                        printf("Not safe\n");
                        flag=0;
                        break;
                }
        }
        if(flag==1)
        {
                for(i=0;i<p-1;i++)
                {
                        printf("P%d->",safe[i]);
                }
                printf("P%d",safe[p-1]);
        }
        printf("\n");
}