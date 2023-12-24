#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main(int argc, char *argv[]) {
    int *p = malloc(sizeof(int));
    assert(p != NULL);
    printf("(%d) address pointed to by p: %p\n", getpid(), p);
    *p = 0;

    while (1) {
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p);
        
        // Add a sleep to prevent excessive resource consumption
        usleep(1000000); // Sleep for 1 second
    }

    return 0;
}
