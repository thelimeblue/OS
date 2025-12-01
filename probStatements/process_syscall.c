#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("Parent process started. PID = %d\n", getpid());

    pid = fork(); // Create child process

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        printf("Child process running...\n");
        printf("Child PID = %d, Parent PID = %d\n", getpid(), getppid());
    }
    else
    {
        // Parent process
        printf("Parent waiting for child...\n");
        wait(NULL); // wait system call
        printf("Child completed.\n");
    }

    return 0;
}
