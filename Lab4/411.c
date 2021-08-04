// C program to show thread functions
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void * func(void * num)
{
    // detach the current thread from the calling thread
    pthread_detach(pthread_self());

    int i,j;
    int n = *((int*) num);

    printf("Inside thread:\n");

    printf("Prime numbers within the range: \n");
    for(i=2; i<=n; i++)
    {

        int cnt=0;
        for(int j = 2; j <= i/2; j++)
        {
            if( i % j == 0)
            {
                cnt = 1;
                break;
            }
        }
        if(cnt == 0 || i == 2)
            printf("%d\n ", i);

    }
    pthread_exit(NULL);

}

void fun()
{
    int n;
    printf("Enter range: ");
    scanf("%d", &n);

    void *ptr = &n;
    pthread_t ptid;

    pthread_create(&ptid, NULL, func, ptr);

    pthread_join(ptid, NULL);

    printf("This line will be printed after thread ends\n");

    pthread_exit(NULL);
}

int main()
{
    fun();
    return 0;
}
