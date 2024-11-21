// Bankers Algorithm

#include <stdio.h>
#include <unistd.h>

void main()
{
    int process, resource, i, instance, j, counter = 0, count = 0, temp = 0;
    printf("\n\t\tEnter Number of Process : ");
    scanf("%d", &process);
    int system[process];
    printf("\t\tEnter Number of Resources : ");
    scanf("%d", &resource);
    int available[resource], max_instance[resource], max[process][resource], allocated[process][resource], need[process][resource], completed[process], total[resource];

    for (i = 0; i < process; i++)
        completed[i] = 0;
    for (j = 0; j < resource; j++)
        total[j] = 0;

    printf("\n\t\tEnter No. of Max Instances for each resource\n\n");
    for (i = 0; i < resource; i++)
    {
        printf("\t\tResources[%d] : ", i);
        scanf("%d", &max_instance[i]);
    }

    printf("\n\t-------------------------------------------------------------------------------------\n");
    printf("\n\t\tEnter MAXIMUM instance for a Process & its corresponding resource :\n");
    for (i = 0; i < process; i++)
    {
        printf("\n\t\tFor Process[%d] \n", i);
        for (j = 0; j < resource; j++)
        {
            printf("\t\t\tResource[%d] : ", j);
            scanf("%d", &instance);
            max[i][j] = instance;
        }
    }

    printf("\n\t-------------------------------------------------------------------------------------\n");
    printf("\n\t\tEnter instance ALLOCATED for a Process & its corresponding resource :\n");
    for (i = 0; i < process; i++)
    {
        printf("\n\t\tFor Process[%d] \n", i);
        for (j = 0; j < resource; j++)
        {
            printf("\t\t\tResource[%d] : ", j);
            scanf("%d", &instance);
            allocated[i][j] = instance;
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    for (j = 0; j < resource; j++)
    {
        for (i = 0; i < process; i++)
        {
            total[j] += allocated[i][j];
        }
    }

    for (i = 0; i < resource; i++)
    {
        available[i] = max_instance[i] - total[i];
    }

    int duration = 10;
    int elapsed = 0;
    printf("\n");
    while (elapsed < duration)
    {

        printf("\r\t\tprocessing /");
        fflush(stdout);
        usleep(200000);

        printf("\r\t\tprocessing \\");
        fflush(stdout);
        usleep(200000);

        elapsed++;
    }
    printf("\n");
    printf("\n\t\tneed = max - allocated \n");
    printf("\n\t\t\tNeed Matrix");
    printf("\n\n\t\tProcess");
    for (i = 0; i < resource; i++)
    {
        printf("\t R#%d", i);
    }
    for (i = 0; i < process; i++)
    {
        printf("\n\t\t p[%d] ", i);
        for (j = 0; j < resource; j++)
        {
            printf("\t %d", need[i][j]);
        }
    }
    printf("\n\n\t-------------------------------------------------------------------------------------\n");
    printf("\n");
    int countsys = 0;
    while (count != process)
    {
        count = temp;
        for (i = 0; i < process; i++)
        {
            for (j = 0; j < resource; j++)
            {
                if (need[i][j] <= available[j])
                {
                    counter++;
                }
            }
            if (counter == resource && completed[i] == 0)
            {
                system[countsys++] = i;

                completed[i] = 1;
                for (j = 0; j < resource; j++)
                {
                    available[j] = available[j] + allocated[i][j];
                }

                printf("\t\tWork Vector : ");
                for (j = 0; j < resource; j++)
                {
                    printf("%d ", available[j]);
                }
                printf("\n");

                count++;
            }
            counter = 0;
        }

        if (count == temp)
        {
            break;
        }
    }
    printf("\n\t\tSafe Sequence: ");
    for (i = 0; i < process; i++)
    {
        printf(" P[%d] ", system[i]);
        if (i < process - 1)
            printf("->");
    }
    for (i = 0; i < process; i++)
    {
        if (completed[i] != 1)
        {
            printf("\n\n\t\t P[%d] not able to allocate", i);
        }
    }
    printf("\n");
}