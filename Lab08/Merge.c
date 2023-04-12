#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 1024

int arr[MAX_SIZE];
int temp[MAX_SIZE];

//Thread Struct
typedef struct {
    int start;
    int end;
} thread_args;

//Regular Merge Sort
void merge(int start, int mid, int end) {
    int i = start, j = mid + 1, k = start;

    while (i <= mid && j <= end) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= end) {
        temp[k++] = arr[j++];
    }

    for (i = start; i <= end; i++) {
        arr[i] = temp[i];
    }
}

//Merge Sort For Thread
void *merge_sort(void *args) {
	//Creating Thread
    thread_args *ta = (thread_args*) args;

    int start = ta->start;
    int end = ta->end;

    if (start >= end) {
        return NULL;
    }

    
    int mid = (start + end) / 2;

    //Creat Two Thread For Left AND Right Sub_Array Respectively
    pthread_t tid[2];
    
    //Start To Mid
    thread_args left_args = {start, mid};
    pthread_create(&tid[0], NULL, merge_sort, &left_args);


    //Mid to End
    thread_args right_args = {mid + 1, end};
    pthread_create(&tid[1], NULL, merge_sort, &right_args);

    // Wait For Other Thread To Finish
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    // Merge Left and Right Arrays
    merge(start, mid, end);

    return NULL;
}

int main() {
    int num, i;
    int new;
    num = 256;
    // printf("How Many Elements? : ");
    // scanf("%d", &num);

    printf("Enter %d Numbers:\n", num);
    for (i = 0; i < num; i++) {
		new = rand() % 100;
		printf(" %d" , new);
		printf("\n");
        arr[i] = new;
    }

    thread_args args = {0, num - 1};
    pthread_t tid;
    pthread_create(&tid, NULL, merge_sort, &args);
    pthread_join(tid, NULL);

    printf("Sorted Array :  ");
    for (i = 0; i < num; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
