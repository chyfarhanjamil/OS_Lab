#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    // ftok to generate unique key
    //key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(IPC_PRIVATE,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    int *str = (int*) shmat(shmid,NULL,0);

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
        printf("\nEnter key: \n");
        scanf("%d", &key);
    }

    printf("\n");

    pid_t p = fork();

    if (p < 0)
    {
        printf("fork Failed" );
        return 1;
    }

    // Parent process
    else if (p > 0)
    {
        wait(NULL);
        int i;
        printf("Inside parent:\n");

        // Binary Search
        int first = 0;
        int last = size - 1;
        int middle = (first + last)/2;

        while (first <= last)
        {
            if (str[middle] < key)
                first = middle + 1;
            else if (str[middle] == key)
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

        printf("Parent ends.\n");


        //detach from shared memory
        shmdt(str);
    }

    // child
    else
    {

        int i;

        printf("Data read from memory: \n");

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
        printf("Sorted Array Inside Child: \n");
        for (int j = 0; j < size; j++)
        {
            printf("%d ", array[j]);
            str[j]=array[j];
        }
        printf("\n");

        //detach from shared memory
        shmdt(str);

        // destroy the shared memory
        shmctl(shmid,IPC_RMID,NULL);

        exit(0);
    }
}
