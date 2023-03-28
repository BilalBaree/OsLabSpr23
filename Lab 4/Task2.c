#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) { // child process
        execl("./program", "program", NULL);
        perror("execl");
        exit(1);
    }

    int num_children = 0;

    while (1) {
        pid_t child_pid = fork();
        if (child_pid == -1) {
            perror("fork");
            break;
        } else if (child_pid == 0) { // child process
            sleep(1);
            printf("Child process with PID %d and parent PID %d\n", getpid(), getppid());
            sleep(1);
            exit(0);
        } else { // parent process
            num_children++;
            printf("Created child process number %d\n", num_children);
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

