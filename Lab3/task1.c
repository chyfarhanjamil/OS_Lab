
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
    int fd[2];

    pid_t p;

    int key = -1, array[100], size, temp;

    printf("Size of array:\n");
    scanf("%d", &size);

    printf("Enter non-negative no. :\n");
    for(int i=0; i<size; i++)
    {
        scanf("%d", &array[i]);
        if(array[i]<0)
        {
            printf("\n");
            printf("Negative no. detected... Program terminated\n");
            return 0;
        }
    }

    while(key < 0)
    {
        printf("Enter key: \n");
        scanf("%d", &key);
    }

    printf("\n");

    if(pipe(fd)==-1)
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

    //parent
    else if(p > 0)
    {
        wait(NULL);

        close(fd[1]);

        int i,output_int[size];

        read(fd[0], output_int, sizeof(output_int));

        printf("\nData read from pipe: \n");
        for(i=0;i<size;i++)
        {
            if(i<size){
            printf("%d ",output_int[i]);
            printf("\n");
            }
        }

        // binary Search
        int first = 0;
        int last = size - 1;
        int middle = (first + last)/2;

        while (first <= last)
        {
            if (output_int[middle] < key)
                first = middle + 1;
            else if (output_int[middle] == key)
            {
                printf("%d is in the array at position %d!\n", key, (middle+1));
                break;
            }
            else
                last = middle - 1;

            middle = (first + last)/2;
        }

        if (first > last)
            printf("\n%d cannot be found in the array!\n", key);

        printf("\nParent ends.\n");
        return 1;
    }

    //child
    else
    {
        //bubble
        for (int j = 0; j < size-1; j++)
        {
            for (int k = 0; k < size-j-1; k++)
            {
                if (array[k] > array[k+1])
                {
                    temp = array[k];
                    array[k] = array[k+1];
                    array[k+1] = temp;
                }
            }
        }
        printf("Sorted Array Inside Child: ");
        for (int j = 0; j < size; j++)
        {
            printf("%d ", array[j]);
        }

        close(fd[0]);

        write(fd[1], array, sizeof(array));
        close(fd[1]);

        printf("\nChild ends.\n");
        return 1;
    }

    return 0;
}
