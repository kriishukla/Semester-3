#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<assert.h>


int main(int argc, char *argv[]) {
printf("hello world (pid:%d)\n", (int) getpid());
int rc = fork();
if (rc < 0) {
// fork failed
fprintf(stderr, "fork failed\n");
exit(1);
} else if (rc == 0) {
// child (new process)
printf("hello, I am child (pid:%d)\n", (int) getpid());
} else {
    int wc =wait(NULL);
// parent goes down this path (main)
printf("hello, I am parent of %d (pid:%d)  (wc:%d) \n",
rc, (int) getpid(),wc);
printf("%d",wc);
}
return 0;
}