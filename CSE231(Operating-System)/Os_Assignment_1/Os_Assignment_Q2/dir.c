
#include "dir.h"

char * dir(int argc, char *argv[])
{
    char * path = (char *) malloc(128*sizeof(char));
    getcwd(path,128);
    const char *option = NULL;
    const char *dir_name = NULL;
    if(argc<3){
        dir_name = argv[1];
    }
    else{
        dir_name = argv[2];
        option = argv[1];
    }

    // credits Chat GPT starts
    struct stat st;
    int dir_exist = (stat(dir_name, &st) == 0);
    // credits end
    if (strcmp(argv[0],"dir") == 0){
        if (option == NULL)
        {
            printf("Understanding and executing message\n");

            if (dir_exist)
            {
                fprintf(stderr, "Directory already exists\n");
                return path;
            }
            else
            {
                printf("Creating directory\n");
                printf("Changing directory to %s\n", dir_name);
                mkdir(dir_name, 0777);
                snprintf(path, 128, "%s/%s", path, dir_name);
                return path;
            }
        }
        
        else if (strcmp(option, "-v") == 0)
        {

            printf("Understanding and executing message\n");

            if (dir_exist)
            {
                fprintf(stderr, "Directory already exists\n");
                snprintf(path, 128, "%s/%s", path, dir_name);
                return path;
                
            }
            else
            {
                printf("Creating directory\n");

                mkdir(dir_name, 0777);


                printf("Changing directory to %s\n", dir_name);

                if (chdir(dir_name) != 0) {
                    perror("Error changing directory");
                    return path;
                }
                snprintf(path, 128, "%s/%s", path, dir_name);
                return path;
            }
        }

        else if (strcmp(option, "-r") == 0)
        {
            if (dir_exist)
            {

               
                if (rmdir(dir_name) != 0)
                {
                    perror("Error removing directory");
                }
                



            }   
            else
            {
                mkdir(dir_name, 0777);
                snprintf(path, 128, "%s/%s", path, dir_name);
                return path;

            }
            
        }

        else{
            printf("Please give correct commands\n");
            printf("\n");
            }
    }
    return path;
}