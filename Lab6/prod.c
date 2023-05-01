#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

typedef struct {
    int left_half[512];
    int right_half[512];
} buffer_t;

int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int shmid;
    buffer_t *buffer;
    int *shared_memory;
    int i, pid1, pid2, status;

    // create shared memory
    shmid = shmget(IPC_PRIVATE, BUFFER_SIZE * sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("Error creating shared memory");
        exit(EXIT_FAILURE);
    }

    // attach shared memory
    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (int*) -1) {
        perror("Error attaching shared memory");
        exit(EXIT_FAILURE);
    }

    // seed random number generator
    srand(42);

    // generate random numbers and store in shared memory
    for (i = 0; i < BUFFER_SIZE; i++) {
        shared_memory[i] = rand();
    }

    // create buffer from shared memory
    buffer = (buffer_t*) shared_memory;

    // fork first child process
    pid1 = fork();
    if (pid1 == -1) {
        perror("Error forking first child process");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // first child process: sort left half of buffer
        qsort(buffer->left_half, 512, sizeof(int), cmpfunc);
        exit(EXIT_SUCCESS);
    }

    // fork second child process
    pid2 = fork();
    if (pid2 == -1) {
        perror("Error forking second child process");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        // second child process: sort right half of buffer
        qsort(buffer->right_half, 512, sizeof(int), cmpfunc);
        exit(EXIT_SUCCESS);
    }

    // wait for both child processes to finish
    if (waitpid(pid1, &status, 0) == -1) {
        perror("Error waiting for first child process");
        exit(EXIT_FAILURE);
    }
    if (waitpid(pid2, &status, 0) == -1) {
        perror("Error waiting for second child process");
        exit(EXIT_FAILURE);
    }

    // sort entire shared memory buffer
    qsort(shared_memory, BUFFER_SIZE, sizeof(int), cmpfunc);

    // print sorted buffer
    printf("Sorted buffer:\n");
    for (i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", shared_memory[i]);
    }
    printf("\n");

    // detach shared memory
    if (shmdt(shared_memory) == -1) {
        perror("Error detaching shared memory");
        exit(EXIT_FAILURE);
    }

    // delete shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Error deleting shared memory");
        exit(EXIT_FAILURE);
    }

    return 0;
}
