#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MIN 100000
#define MAX 3000000

void *print_message_function(void *ptr);

pthread_rwlock_t  rwlock = PTHREAD_RWLOCK_INITIALIZER;

int main()
{
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";

    pthread_rwlockattr_t attr;
    pthread_rwlockattr_init(&attr);

#ifdef NO_WRITER_STARVATION
    pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
#endif

    pthread_rwlock_init(&rwlock, &attr);

    // Setting seed for the rand() function
    srand(time(0));

    /* Create independent threads each of which will execute function */
    pthread_create(&thread1, NULL, print_message_function, (void*) message1);
    pthread_create(&thread2, NULL, print_message_function, (void*) message2);

    for(;;) {
        pthread_rwlock_wrlock(&rwlock);
        printf("Main\n");
        pthread_rwlock_unlock(&rwlock);
    }

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

void *print_message_function(void *ptr)
{
    char *message;
    message = (char *)ptr;
    for(;;) {
       pthread_rwlock_rdlock(&rwlock);

       printf("%s \n", message);
       int n = rand() % (MAX - MIN) + MIN;
       usleep(n);
       
       pthread_rwlock_unlock(&rwlock);
    }

    return ptr;
}