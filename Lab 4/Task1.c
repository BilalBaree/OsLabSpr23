#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int num_children = 0;
    pid_t pid;

    while ((pid = fork()) != -1) {
        if (pid == 0) { // child process
            sleep(1);
            printf("Child process with PID %d and parent PID %d\n", getpid(), getppid());
            sleep(1);
            exit(0);
        } else { // parent process
            num_children++;
            printf("Created child process number %d\n", num_children);
            if (num_children == 10) {
                break;
            }
            sleep(2);
        }
    }

    int status;
    pid_t child_pid;
    while ((child_pid = wait(&status)) != -1) {
        printf("Child process with PID %d terminated\n", child_pid);
    }

    return 0;
}

