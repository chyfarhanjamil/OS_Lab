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

    int n;

    printf("NO. of terms: ");
    scanf("%d", &n);

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

    //Parent
    else if(p > 0)
    {
        wait(NULL);

        close(fd1[1]);

        int i,output_int[n];

        read(fd1[0], output_int, sizeof(output_int));

        printf("Data read from pipe: \n");
        for(i=0; i<sizeof(output_int); i++)
        {
            if(i<n)
            {
                printf("%d ",output_int[i]);
                printf("\n");
            }
        }
        printf("Parent ends.\n");
        return 1;
    }

    //child
    else
    {
        int i, array[n];
        int t1 = 0, t2 = 1;
        int fibo = t1 + t2;

        for (i = 0; i <= n; ++i)
        {
            if(i==0)
            {
                array[i]=t1;
            }
            else if(i==1)
            {
                array[i]=t2;
            }
            else
            {
                array[i] = fibo;
                t1 = t2;
                t2 = fibo;
                fibo = t1 + t2;
            }
        }

        close(fd1[0]);

        write(fd1[1], array, sizeof(array));

        close(fd1[1]);

        printf("Child Process ends.\n");
        return 1;
    }
    return 0;
}
