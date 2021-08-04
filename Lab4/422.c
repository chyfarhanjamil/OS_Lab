#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int arr[100];

void* func(void* t_no)
{
    int num;
    int a = 1, b = 1;

    printf("Inside the thread\n");

    num = *(int*)t_no;

    if(num == 0)
    {
        arr[num] = a;
    }
    else if(num == 1)
    {
        arr[num] = b;
    }
    else
    {
        arr[num] = arr[num-1] + arr[num-2];
    }
    pthread_exit(NULL);
}



int main()
{
    int i,number;
    printf("Enter the number: \n");
    scanf("%d", &number);

    pthread_t ptid [number];

    printf("Fibonacci series:\n");
    for(i=0; i<number; i++)
    {
        pthread_create(&ptid[i], NULL, func, &i);
        pthread_join(ptid[i], NULL);
        printf("%d\n", arr[i]);
    }
    printf("\n");

    pthread_exit(NULL);
    return 0;
}

