#include <sys/types.h> // Type definitions used by many programs 
#include <stdio.h> // Standard I/O functions 
#include <stdlib.h> // Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants 
#include <unistd.h> // Prototypes for many system calls
#include <errno.h> // Declares errno and defines error constants
#include <string.h> // Commonly used string-handling functions
#include <sys/wait.h>
#include <pthread.h>

void* Find_Prime_Numbers (void *Number_Limit)
{
    // detach the current thread from the calling thread
    // pthread_detach(pthread_self()); 
    
    int Number = *((int*)Number_Limit);

    printf("\nInside the thread.\n");
    printf("Prime Numbers upto %d : ", Number);

    for(int i = 0; i <= Number; i++){
      int flag_var = 0;

      for(int j = 2; j <= i/2; j++){
        if( i % j == 0){
            flag_var = 1;
            break;
        }
      }

      if(flag_var == 0)
        printf("%d ", i);
    }

    // exit the current thread
    pthread_exit(NULL);
}

void create_Thread()
{
    printf("Before entering the seperate thread.\n");

    int Number;

    StartOver:
        printf("\nEnter the number limit: ");
        scanf("%d", &Number);

    if ( Number <= 0 ){
        printf("Please Enter a non-negative integer!\n");
        goto StartOver;
    }

    // Creating a new thread
    pthread_t ptid;
    pthread_create( &ptid, NULL, Find_Prime_Numbers, &Number );

    // Waiting for the created thread to terminate
    pthread_join( ptid, NULL );

    printf("\nThe thread has ended.\n\n");

    pthread_exit(NULL);
}

// Driver code
int main()
{
    create_Thread();
    return 0;
}