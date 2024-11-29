#include <stdio.h>
#include <unistd.h>

void main()
{
    int process, resource, i, instance, j, process_counter = 0, count = 0, temp = 0;
    
    // Get number of processes from the user
    printf("\n\t\tEnter Number of Process : ");
    scanf("%d", &process);
    
    // Declare arrays for system states
    int system[process];
    
    // Get number of resources from the user
    printf("\t\tEnter Number of Resources : ");
    scanf("%d", &resource);
    
    // Declare matrices and arrays for resource allocation data
    int available[resource], max_instance[resource], max[process][resource], allocated[process][resource], need[process][resource], completed[process], total[resource];

    // Initialize the completed array to 0 (indicating no process is completed)
    for (i = 0; i < process; i++)
        completed[i] = 0;

    // Initialize total resource usage to 0
    for (j = 0; j < resource; j++)
        total[j] = 0;

    // Get maximum instance values for each resource
    printf("\n\t\tEnter Number of Max Instances for each resource\n\n");
    for (i = 0; i < resource; i++)
    {
        printf("\t\tResources[%d] : ", i);
        scanf("%d", &max_instance[i]);
    }

    printf("\n\t-------------------------------------------------------------------------------------\n");
    
    // Get maximum resources each process can request
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
    
    // Get the allocated resources for each process
    printf("\n\t\tEnter instance ALLOCATED for a Process & its corresponding resource :\n");
    for (i = 0; i < process; i++)
    {
        printf("\n\t\tFor Process[%d] \n", i);
        for (j = 0; j < resource; j++)
        {
            printf("\t\t\tResource[%d] : ", j);
            scanf("%d", &instance);
            allocated[i][j] = instance;
            need[i][j] = max[i][j] - allocated[i][j]; // Calculate need (max - allocated)
        }
    }

    printf("\n\t-------------------------------------------------------------------------------------\n");
    printf("\n\t\tChecking if maximum values are valid...\n");

    // Check if the allocated values are valid (should not exceed max)
    int valid_input = 1;
    for (i = 0; i < process; i++)
    {
        for (j = 0; j < resource; j++)
        {
            if (max[i][j] < allocated[i][j]) // Invalid allocation (allocated > max)
            {
                printf("\t\tError: Maximum value for P[%d] R[%d] is less than allocated value.\n", i, j);
                valid_input = 0;
            }
        }
    }

    // If the input is invalid, terminate the program
    if (!valid_input)
    {
        printf("\n\t\tInvalid input. Please restart the program and enter correct values.\n");
        return;
    }

    // Calculate the total allocated resources
    for (j = 0; j < resource; j++)
    {
        for (i = 0; i < process; i++)
        {
            total[j] += allocated[i][j];
        }
    }

    // Calculate the available 
    for (i = 0; i < resource; i++)
    {
        available[i] = max_instance[i] - total[i];
    }

    // Simulate a delay with an animation for processing
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
    
    // Display the Need matrix 
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
        usleep(700000);
    }
    printf("\n\n\t-------------------------------------------------------------------------------------\n");
    printf("\n");

    // Banker's algorithm to find safe sequence
    int countsys = 0;
    while (count != process)
    {
        temp = count;
        
        // Check each process to see if it can be executed
        for (i = 0; i < process; i++)
        {
            if (completed[i] == 0)
            {
                process_counter = 0;
                
                // Check if all needs can be met with available resources
                for (j = 0; j < resource; j++)
                {
                    if (need[i][j] <= available[j]) // If the need of resource[i] can be fulfilled
                    {
                        process_counter++;
                    }
                }

                // If all resources are available, execute the process
                if (process_counter == resource)
                {
                    printf("\t\tP[%d] will be executed because need[P%d]<=work\n", i, i);
                    printf("\t\tP[%d] will release the allocated resource", i);
                    printf("(");

                    // Display Work = Available + Allocated
                    printf("Work= Work(");
                    for (int k = 0; k < resource; k++)
                    {
                        printf("%d", available[k]);
                        if (k < resource - 1)
                            printf(",");
                    }

                    printf(")+Allocated(P%d)(", i);

                    for (int k = 0; k < resource; k++)
                    {
                        printf("%d", allocated[i][k]);
                        if (k < resource - 1)
                            printf(",");
                    }
                    printf(")\n");

                    system[countsys++] = i;

                    completed[i] = 1; // Mark process as completed
                    for (j = 0; j < resource; j++)
                    {
                        available[j] = available[j] + allocated[i][j]; // Update available resources
                    }

                    printf("\t\tWork Vector : ");
                    for (j = 0; j < resource; j++)
                    {
                        printf("%d ", available[j]);
                    }
                    printf("\n");

                    count++;
                }
                else
                {
                    printf("\t\tP[%d] will not be executed because need[P%d]>work\n", i, i);
                }
            }
            usleep(700000);
        }

        // If no progress is made in this cycle, break the loop (deadlock)
        if (count == temp)
        {
            break;
        }
    }

    // Output the safe sequence
    printf("\n\t\tSafe Sequence: ");
    for (i = 0; i < countsys; i++)
    {
        printf(" P[%d] ", system[i]);
        if (i < countsys - 1)
            printf("->");
    }
    
    // If some processes are not completed, display which ones
    for (i = 0; i < process; i++)
    {
        if (completed[i] != 1)
        {
            printf("\n\n\t\t P[%d] not able to allocate", i);
        }
    }
    printf("\n");
}