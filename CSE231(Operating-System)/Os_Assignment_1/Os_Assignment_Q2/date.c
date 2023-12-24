#include "date.h"

struct opera {
    time_t op_ctime;
};

int opera(const char *pathname, struct opera *op) {
    return 0;
}

int date(int argc, char *argv[]) {
    const char *option = NULL;
    const char *file_name = NULL;

    if (argc<3){
        file_name = argv[1];
    }
    else{
        file_name = argv[2];
        option = argv[1];
    }

    struct stat st;
    int file_exists = (stat(file_name, &st) == 0);

    struct opera op;
    int file_re = (opera(file_name, &op) == 0);
    if (strcmp(argv[0], "date") == 0) {
        if (option == NULL) {
            time_t mod_time = st.st_mtime;

            struct tm *tm_info = localtime(&mod_time);

            char time_buffer[128];

            strftime(time_buffer, sizeof(time_buffer), "%a, %d %b %Y %H:%M:%S", tm_info);
            printf("Creation date and time: %s\n", time_buffer);
           
        }
        else if (strcmp(option, "-R") == 0) {
            if (!file_exists) {
                perror("File does not exist");
                return 1;
            }

            time_t mod_time = st.st_mtime;

            struct tm *tm_info = localtime(&mod_time);

            char time_buffer[128];

            strftime(time_buffer, sizeof(time_buffer), "%a, %d %b %Y %H:%M:%S", tm_info);

            printf("RFC 5322 formatted date and time: %s\n", time_buffer);
            
        } 
        else if (strcmp(option, "-d") == 0) {
            if (!file_exists) {
                perror("File does not exist");
                return 1;
            }

            time_t mod_time = st.st_mtime;

            struct tm *tm_info = localtime(&mod_time);

            char time_buffer[128];

            strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", tm_info);
            printf("Creation time %s\n", time_buffer);
   
        }  
        else {
            printf("Please give the command in correct format\n");
        }
    }
    return 0;
}