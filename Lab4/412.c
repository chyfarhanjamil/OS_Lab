#include <sys/types.h> // Type definitions used by many programs
#include <stdio.h> // Standard I/O functions
#include <stdlib.h> // Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants
#include <unistd.h> // Prototypes for many system calls
#include <errno.h> // Declares errno and defines error constants
#include <string.h> // Commonly used string-handling functions
#include <sys/wait.h>
#include <pthread.h>

int range;
void* getFibo ()
{
    // detach the current thread from the calling thread
    // pthread_detach(pthread_self());

    int arr[1000];
    int a = 0, b = 1, fibo = a+b;

    printf("\nInside the thread\n");

    int pos = 2;
    arr[0] = a;
    arr[1] = b;

    for (int i = 0; i < range - 1; i++)
    {
        fibo = a + b;
        arr[pos] = fibo;
        a = b;
        b = fibo;
        pos++ ;
    }
    pthread_exit(arr);
}

void fun()
{
    void *result_array;
    printf("Enter a positive range: ");
    scanf("%d", &range);
    pthread_t ptid;
    pthread_create( &ptid, NULL, getFibo, NULL );
    pthread_join( ptid, &result_array );

    printf("\nInside parent:\n");

    printf("Fibonacci Series: ");
    for (int j = 0; j < range; j++)
        printf("%d ", ((int*)result_array)[j]);

    pthread_exit(NULL);

}

int main()
{
    fun();
    return 0;
}
