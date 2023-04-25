#include "pthread.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include "semaphore.h" // Importing semaphore library
#include "stdlib.h"

#define MAX_THREADS 100

volatile int num[MAX_THREADS];
volatile int res;
sem_t mutex; // Semaphore for mutual exclusion

void lock_thread(int thread)
{
    // Wait on semaphore
    sem_wait(&mutex);

    int max_num = 0;
    for (int i = 0; i < MAX_THREADS; ++i)
    {
        int ticket = num[i];
        max_num = ticket > max_num ? ticket : max_num;
    }
    num[thread] = max_num + 1;

    // Signal semaphore
    sem_post(&mutex);
}

void unlock_thread(int thread)
{
    num[thread] = 0;
}

void use_res(int thread)
{
    if (res != 0)
    {
        printf("The Resource was acquired by %d, but is still in-use by %d!\n", thread, res);
    }
    res = thread;
    printf("%d is using resource...\n", thread);
    sleep(2);
    res = 0;
}

void *thread_body(void *arg)
{
    long thread = (long)arg;
    lock_thread(thread);
    use_res(thread);
    unlock_thread(thread);
    return NULL;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }

    int thread_count = atoi(argv[1]);

    if (thread_count <= 0 || thread_count > MAX_THREADS)
    {
        printf("Invalid number of threads. Exiting...\n");
        return 1;
    }

    memset((void *)num, 0, sizeof(num));
    res = 0;

    // Initialize semaphore
    sem_init(&mutex, 0, 1);

    // Declare thread variables
    pthread_t threads[MAX_THREADS];

    for (int i = 0; i < thread_count; ++i)
    {
        pthread_create(&threads[i], NULL, &thread_body, (void *)((long)i));
    }

    for (int i = 0; i < thread_count; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    // Destroy semaphore
    sem_destroy(&mutex);

    return 0;
}
