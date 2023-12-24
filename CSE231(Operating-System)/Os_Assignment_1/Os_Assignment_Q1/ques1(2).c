#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

// vfork studied from 
int main() {
    int rc = vfork();

    if (rc < 0) {
        fprintf(stderr, "vfork failed\n");
        exit(1);
    } 
    else if (rc == 0) {
        fact();
        
    } else {
        wait(NULL);
        fib();
            
    }
    return 0;
}
