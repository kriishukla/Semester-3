#include <stdio.h>

int main(argc, argv) {
for(int i = 0; i < 4; i++) {
int ret = fork();
printf("%d",i);
if(ret == 0)
printf("child %d\n", i);
}
}