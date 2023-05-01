#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define SHM_NAME "/my_shared_memory"
#define SHM_SIZE (sizeof(int) * 512)

typedef struct {
    int left_half[512];
    int right_half[512];
} shared_buffer;

void merge_sort(int* arr, int l, int r);
void merge(int* arr, int l, int m, int r);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <left|right>\n", argv[0]);
        exit(1);
    }

    int is_left = strcmp(argv[1], "left") == 0;

    // Create shared memory object
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }
    shared_buffer* buffer = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (buffer == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Sort left or right half of buffer using merge sort
    if (is_left) {
        merge_sort(buffer->left_half, 0, 511);
    } else {
        merge_sort(buffer->right_half, 0, 511);
    }

    // Write sorted digits to parent process via pipeline
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }
    if (write(fd[1], buffer, SHM_SIZE) == -1) {
        perror("write");
        exit(1);
    }

    // Clean up shared memory object
    if (munmap(buffer, SHM_SIZE) == -1) {
        perror("munmap");
        exit(1);
    }
    close(shm_fd);

    return 0;
}

// Merge sort algorithm
void merge_sort(int* arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Merge two sorted subarrays into a single sorted array
void merge(int* arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
        while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

