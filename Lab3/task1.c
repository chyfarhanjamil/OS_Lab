
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
    int fd1[2];

    pid_t p;

    int search = -1, array[100], arrSize, temp;

    printf("Enter Size of Array:\n");
    scanf("%d", &arrSize);

    printf("Enter Non-Negative Integers:\n");
    for(int i=0; i<arrSize; i++)
    {
        scanf("%d", &array[i]);
    }

    printf("Scaning for Non-Negative Integers...\n");
    for(int i=0; i<arrSize; i++)
    {
        printf("%d ", array[i]);
        if(array[i]<0)
        {
            printf("\n");
            printf("Input not ok, program terminates...\n");
            return 0;
        }
    }

    while(search < 0)
    {
        printf("\nEnter the value to search: \n");
        scanf("%d", &search);
    }

    printf("\n");

    if(pipe(fd1)==-1)
    {
        printf("Pipe Failed");
        return 1;
    }

    p = fork();

    if(p<0)
    {
        printf("fork failed");
        return 1;
    }

    //Parent Process
    else if(p > 0)
    {
        wait(NULL);
        printf("\nParent Process id %d\n",getpid());

        close(fd1[1]);

        int i,output_int[arrSize];

        read(fd1[0], output_int, sizeof(output_int));

        printf("Data read from pipe: \n");
        for(i=0;i<sizeof(output_int);i++)
        {
            if(i<arrSize){
            printf("%d ",output_int[i]);
            printf("\n");
            }
        }

        // Binary Search
        int first = 0;
        int last = arrSize - 1;
        int middle = (first + last)/2;

        while (first <= last)
        {
            if (output_int[middle] < search)
                first = middle + 1;
            else if (output_int[middle] == search)
            {
                printf("\n%d is found!\n", search);
                break;
            }
            else
                last = middle - 1;

            middle = (first + last)/2;
        }

        if (first > last)
            printf("\nNot found! %d is not present in the array.\n", search);

        printf("Parent Process ends.\n");
        return 1;
    }

    //child process
    else
    {
        printf("Child Process id %d\n",getpid());

        for (int j = 0; j < arrSize-1; j++)
        {
            for (int k = 0; k < arrSize-j-1; k++)
            {
                if (array[k] > array[k+1])
                {
                    temp = array[k];
                    array[k] = array[k+1];
                    array[k+1] = temp;
                }
            }
        }
        printf("Sorted Array by Child:\n");
        for (int j = 0; j < arrSize; j++)
        {
            printf("%d ", array[j]);
        }

        close(fd1[0]); // Close reading end of first pipe

        // Write and close writing end of first pipe.
        write(fd1[1], array, sizeof(array));
        printf("\nData written in pipe\n");
        close(fd1[1]);

        printf("Child Process ends.\n");
        return 1;
    }

    return 0;
}
