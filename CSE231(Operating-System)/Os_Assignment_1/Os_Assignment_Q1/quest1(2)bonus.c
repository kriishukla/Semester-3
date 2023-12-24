#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void fib() {
    int fib[17];
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= 16; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    for (int i = 0; i < 16; i++) {
        printf("%d\n", fib[i]);
    }
}

void fact() {
    int fact = 1;

    for (int i = 1; i <= 4; i++) {
        fact *= i;
    }

    printf("Factorial of %d is: %d\n", 4, fact);
}

// Signal handler for child process
void child_signal_handler(int signum) {
    // Do nothing, just exit the pause
}

int main() {
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        signal(SIGUSR1, child_signal_handler);  // Set up signal handler
        pause(); 
        fact();  
    } else {
        fib();  // Calculate Fibonacci series
        sleep(1);  // Sleep for 1 second to ensure child is ready to receive signal
        kill(rc, SIGUSR1);  // Send custom signal SIGUSR1 to child to resume
        wait(NULL);  // Wait for child to complete
    }

    return 0;
}
