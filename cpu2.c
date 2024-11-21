// Bankers Algorithm

#include<stdio.h>

void main()
{ 
  int process, resource, i, j, instance, k=0, count=0, temp=0;
  printf("\n Enter Number of Process : ");
  scanf("%d", &process);
  int system[process];
  printf(" Enter Number of Resources : ");
  scanf("%d",&resource);
  int available[resource], max[process][resource], allocated[process][resource], need[process][resource], completed[process];

  for(i=0; i<process; i++)
    completed[i] = 0;

  printf("\n Enter No. of AVAILABLE Instances for each resource\n\n");
  for(i=0; i<resource;i++)
  {  
    printf(" Resources[%d] : ", i);
    scanf("%d", &instance);
    available[i] = instance;
  }

  printf("\n------------------------------------------------------------------------------\n");
  printf("\n Enter MAXIMUM instance for a Process & its corresponding resource :\n");
  for(i=0; i<process; i++)
  {
    printf("\n For Process[%d] \n", i);
    for(j=0; j<resource; j++)
    {
        printf(" Resource[%d] : ", j);
        scanf("%d", &instance);
        max[i][j] = instance;
    }
  }

  printf("\n------------------------------------------------------------------------------\n");
  printf("\n Enter instance ALLOCATED for a Process & its corresponding resource :\n");
  for(i=0; i<process; i++)
  {
    printf("\n For Process[%d] \n", i);
    for(j=0; j<resource; j++)
    {
      printf(" Resource[%d] : ", i);
      scanf("%d", &instance);
      allocated[i][j] = instance;
      need[i][j] = max[i][j] - allocated[i][j];
     
    }
  }
 printf("\n need = max - allocated \n");
printf("\nNeed Matrix");
for(i=0; i<process; i++)
  {
    printf("\n p[%d] ",i);
    for(j=0; j<resource; j++)
    {
     printf("\t %d",need[i][j]);
    }
  }
  printf("\n------------------------------------------------------------------------------\n");
  int countsys=0;
  while(count != process)
  {
    count = temp;
    for(i=0; i<process; i++)
    {
      for(j=0; j<resource; j++)
      {
        if(need[i][j] <= available[j])
        {
          k++;
        }
      }
      if(k == resource && completed[i] == 0 )
      { system[countsys++]=i;
        
        completed[i] = 1;
        for(j=0; j<resource; j++)
        {
          available[j] = available[j] + allocated[i][j];
        }     
          
          printf("Work Vector : ");
          for(j = 0; j < resource; j++) {
             printf("%d ", available[j]);
          }
          printf("\n");

          
         
        count++;
      }
      k=0;
    }

    if(count == temp)
    {
      break;
    }
  }
 printf("\nSafe Sequence: ");
for(i = 0; i < process; i++) {
    printf("P[%d] -> ", system[i]);
}
  for(i=0; i<process; i++)
  {
    if(completed[i] != 1)
    {
      printf("\n\n P[%d] not able to allocate", i);
    }
  }
  printf("\n");
}