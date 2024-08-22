#include <stdio.h>

int getSeekTime(int a,int b){
   if(a>b)
      return a-b;
   return b-a;
}

void copy(int arr[],int temp[],int n)
{
 for(int i=0;i<n;i++)
    temp[i] = arr[i];
}

void sort(int arr[],int n)
{
   int temp;
   for(int i=0;i<n-1;i++)
   {
      for(int j=0;j<n-i-1;j++)
      {
       if(arr[j]>arr[j+1])
       {
         temp = arr[j];
         arr[j] = arr[j+1];
         arr[j+1] = temp;
       }
      }
   }
}

int reqIndex(int arr[],int n,int p)
{
   for(int i=0;i<n;i++)
   {
      if(arr[i]>=p)
         return i;
    }
    return n;
}

void fcfs(int arr[],int n,int p,int max)
{
  printf("\nFCFS Disk Scheduling\n");
  int seekTime=0;
  printf("%d => ",p);
  for(int i=0;i<n;i++)
  {
     seekTime += getSeekTime(p,arr[i]);
     if(i!=n-1)
        printf("%d => ",arr[i]);
     else
       printf("%d",arr[i]);
       p = arr[i];
   }
 printf("\nTotal Head Movements in FCFS = %d\n\n",seekTime);
}

void scan(int arr[],int n,int p,int max, int direction)
{
   printf("\nSCAN Disk Scheduling\n");
   int seekTime=0,temp[n],i;
   copy(arr,temp,n);
   sort(temp,n);
   int index = reqIndex(temp,n,p);

   printf("%d => ",p);

   if (direction == 1) { // Increasing order
      seekTime += getSeekTime(p,max);
      for( i=index;i<n;i++)
      {
         printf("%d => ",temp[i]);
         p=temp[i];
      }
      printf("%d\n%d => ",max,max);
      p=max;
      for( i=index-1;i>=0;i--)
      {
        if(i!=0)
            printf("%d => ",temp[i]);
        else
           printf("%d",temp[i]);
         p=temp[i];
      }
      seekTime += getSeekTime(max,temp[0]);
   } else { // Decreasing order
      seekTime += getSeekTime(p, 0);
      for( i=index-1;i>=0;i--)
      {
        printf("%d => ",temp[i]);
        p=temp[i];
      }
      printf("0\n0 => ");
      p=0;
      for( i=index;i<n;i++)
      {
        if(i!=n-1)
           printf("%d => ",temp[i]);
        else
           printf("%d",temp[i]);
         p=temp[i];
      }
      seekTime += getSeekTime(0,temp[n-1]);
   }
   printf("\nTotal Head Movements in SCAN = %d\n\n",seekTime);
}

void cscan(int arr[],int n,int p,int max, int direction){
   printf("\nCSCAN Disk Scheduling\n");
   int seekTime=0,temp[n],i;
   copy(arr,temp,n);
   sort(temp,n);
   int index = reqIndex(temp,n,p);

   printf("%d => ",p);

   if (direction == 1) { // Increasing order
      seekTime+=getSeekTime(p,max);
      for( i=index;i<n;i++)
      {
         printf("%d => ",temp[i]);
         p=temp[i];
      }
      printf("%d \n0 => ",max);
      p=0;
      for( i=0;i<index;i++)
      {
       if(i!=index-1)
         printf("%d => ",temp[i]);
       else
         printf("%d",temp[i]);
       p=temp[i];
      }
      seekTime+=getSeekTime(max,0);
      if(index>0)
          seekTime+=getSeekTime(0,temp[index-1]);
   } else { // Decreasing order
      seekTime+=getSeekTime(p,0);
      for( i=index-1;i>=0;i--)
      {
         printf("%d => ",temp[i]);
         p=temp[i];
      }
      printf("0\n%d => ",0);
      p=max;
      for( i=n-1;i>=index;i--)
      {
       if(i!=index)
         printf("%d => ",temp[i]);
       else
         printf("%d",temp[i]);
       p=temp[i];
      }
      seekTime+=getSeekTime(0,max);
      if(index<n)
          seekTime+=getSeekTime(max,temp[index]);
   }
   printf("\nTotal Head Movements in CSCAN = %d\n\n",seekTime);
}

void main()
{
   printf("DISK SCHEDULING\n");
 
   int n,i,max,p;
 
   printf("Enter the disk track limit(max): ");
   scanf("%d",&max);
   printf("Enter the number of requests: ");
   scanf("%d",&n);
   printf("Enter the requests \n");
   int arr[n];
   for(i=0;i<n;i++)
   {
      scanf("%d",&arr[i]);
   }
   printf("Enter the current position of disk arm: ");
   scanf("%d",&p);
   int choice;
   do{
    printf("1. FCFS\n");
    printf("2. SCAN\n");
    printf("3. CSCAN\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice){
      case 1: 
        fcfs(arr,n,p,max);
        break;
      case 2: {
       int direction;
       printf("Enter 1 for increasing order, 0 for decreasing order: ");
       scanf("%d", &direction);
       scan(arr,n,p,max,direction);
       break;
      }
      case 3: {
        int direction;
        printf("Enter 1 for increasing order, 0 for decreasing order: ");
        scanf("%d", &direction);
        cscan(arr,n,p,max,direction);
        break;
      }
      case 4: 
        break;
      default:
        printf("invalid input\n");
        break;
  }
 }while(choice<4);
}