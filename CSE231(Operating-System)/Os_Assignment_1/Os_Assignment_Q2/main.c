#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "dir.h"
#include "date.h"
#include "word.h"

int main() {
    printf("-----------------------------\n");
    printf("-------CSHELL----------------\n");
    printf("-----------------------------\n");
    char input[100];
    char * path = (char *) malloc(128 * sizeof(char));
    getcwd(path,128);
    
    while (1) {
        printf("%s",path);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        char *args[5];
        char *token = strtok(input, " ");
        
        int argc = 0;
        while (token != NULL) {
            args[argc] = token;
            argc++;
            
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;
        
        if (argc > 0) {
            if (strcmp(args[0], "exit") == 0) {
                break;
            }
            else if (strcmp(args[0], "word") == 0) {
                word(argc, args);
            }
            else if (strcmp(args[0], "date") == 0) {
                date(argc, args);
                
            }
            else if (strcmp(args[0], "dir") == 0) {
                char * newpath = dir(argc, args);
                path = newpath;
            }
        }
    }
    return 0;
}


