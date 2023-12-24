#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include<assert.h>

// snippet and idea to write code taken from The book three pieces and lecture slides
int main(int argc, char *argv[]) {


    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } 
    else if (rc == 0) {
        int wc = wait(NULL);  
        printf("Child is having ID %d\n", (int) getpid());
        printf("My Parent ID is %d\n", getppid());  
    } else {
        printf("Parent is having ID %d\n", (int) getpid());
        int wc = wait(NULL);  
        printf("ID of Child is %d\n", rc);
        
    }
    return 0;
}
