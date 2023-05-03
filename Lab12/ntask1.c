#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <omp.h>

#define SHM_SIZE 1024

// Generate seeded random numbers in shared memory
void generate_random_numbers(int *shm_ptr) {
    int seed = 1234;
    srand(seed);
    for (int i = 0; i < SHM_SIZE; i++) {
        shm_ptr[i] = rand() % 1000;
    }
}

// Merge two sorted arrays into one sorted array
void merge(int *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge sort function
void merge_sort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            merge_sort(arr, l, m);
            #pragma omp section
            merge_sort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

int main() {
    int shmid;
    int *shm_ptr;

    // Create shared memory
    shmid = shmget(IPC_PRIVATE, SHM_SIZE * sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    // Generate random numbers in shared memory
    generate_random_numbers(shm_ptr);

    // Sort numbers using merge sort in parallel
    #pragma omp parallel num_threads(100) shared(shm_ptr)
    {
        merge_sort(shm_ptr, 0, SHM_SIZE - 1);
    }

    // Print sorted numbers
    printf("Sorted numbers:\n");
    for (int i = 0; i < SHM_SIZE; i++) {
        printf("%d ", shm_ptr[i]);
        }

// Detach shared memory
if (shmdt(shm_ptr) == -1) {
    perror("shmdt");
    exit(1);
}

// Delete shared memory
if (shmctl(shmid, IPC_RMID, NULL) == -1) {
    perror("shmctl");
    exit(1);
}

return 0;
}
