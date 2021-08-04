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

    int n;

    printf("No. of terms: ");
    scanf("%d", &n);

    pid_t p = fork();

    if (p < 0)
    {
        printf("fork Failed" );
        return 1;
    }

    // Parent
    else if (p > 0)
    {
        wait(NULL);

        int i;

        printf("Data read from pipe: ");
        for(i=0; i<n; i++)
        {
            printf("%d ",str[i]);
        }
        printf("\n");

        //detach from shared memory
        shmdt(str);
    }

    // child
    else
    {
        int i, array[n];
        int t1 = 0, t2 = 1;
        int fibo = t1 + t2;


        for (i = 0; i <= n; ++i) {
            if(i==0){
                array[i]=t1;
            }
            else if(i==1){
                array[i]=t2;
            }
            else{
                array[i] = fibo;
                t1 = t2;
                t2 = fibo;
                fibo = t1 + t2;
            }
        }

        for(i=0;i<=n;i++)
        {
            str[i] = array[i];
        }

        //detach from shared memory
        shmdt(str);

        // destroy the shared memory
        shmctl(shmid,IPC_RMID,NULL);

        exit(0);
    }
}
