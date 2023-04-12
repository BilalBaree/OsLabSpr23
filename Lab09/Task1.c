#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREADS 50

int tickets[THREADS];
int choosing[THREADS];
int counter = 0;
int completed_threads = 0;

sem_t mutex;
sem_t semaphore[THREADS];

void *thread_func(void *arg) {
    int thread_num = *((int *) arg);
    int i;

    for (i = 0; i < 1; i++) {
        choosing[thread_num] = 1;
        int max_ticket = 0;

        sem_wait(&mutex);
        for (int j = 0; j < THREADS; j++) {
            if (tickets[j] > max_ticket) {
                max_ticket = tickets[j];
            }
        }
        tickets[thread_num] = max_ticket + 1;
        choosing[thread_num] = 0;

        sem_post(&mutex);

        for (int j = 0; j < THREADS; j++) {
            if (j != thread_num) {
                while (choosing[j]) { }
                while (tickets[j] != 0 && (tickets[thread_num] > tickets[j] ||
                    (tickets[thread_num] == tickets[j] && thread_num > j))) { }
            }
        }

        // Critical section
        printf("Thread %d entered critical section.\n", thread_num);
        counter++;
        //sleep(1);
        printf("Counter value: %d\n", counter);
        //sleep(1);
        printf("Thread %d leaving critical section.\n", thread_num);

        tickets[thread_num] = 0;

        sem_post(&semaphore[thread_num]);
    }

    completed_threads++;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[THREADS];
    int thread_num[THREADS];

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < THREADS; i++) {
        sem_init(&semaphore[i], 0, 0);
        thread_num[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_num[i]);
    }

    while (completed_threads < THREADS) {
        // Wait for all threads to complete
    }

    sem_destroy(&mutex);
    for (int i = 0; i < THREADS; i++) {
        sem_destroy(&semaphore[i]);
    }

    return 0;
}
