#include "word.h"

int word(int argc, char *argv[])
{
    if (argc<2){

    printf("Number of argument is much less");

}

    const char *option = NULL;
    const char *file_name = NULL;
    // printf("Imhere");

    if (strcmp(argv[0], "word") == 0)
    {
         option = argv[1]; // Set option based on command-line argument

        if (argc >= 3) {
            file_name = argv[2]; // Set file_name if available
        }
        
        if (strcmp(option, "-n") == 0){
            // printf("im here1");
            FILE *file;
            char chb;
            int count = 0;
            file = fopen(file_name , "r");
            if (file == NULL)
            {
                printf("Error opening file\n");
                return 1;
            }

            while ((chb = fgetc(file)) != EOF)
            {
                if (chb == ' ' || chb == '\n')
                {
                    count++;
                }
            }

            printf("Word count ignoring newlines: %d\n", count);
            fclose(file);
            
        }
      
        else if (strcmp(option, "-d") == 0)
        {
            // printf("im here111");
            FILE *file1;
            char cha;
            int count1 = 0;
            file1 = fopen(file_name, "r");
            if (file1 == NULL)
            {
                printf("Error opening file\n");
                return 1;
            }   

            while ((cha = fgetc(file1)) != EOF)
            {
                if (cha == ' ' || cha == '\n')
                {
                    count1++;
                }
            }

            printf("Word count: %d\n", count1);
            fclose(file1);



            FILE *file2;
            char ch;
            int count2 = 0;

            file2 = fopen(argv[3], "r");
            if (file2 == NULL)
            {
                printf("Error opening file\n");
                return 1;
            }

            while ((ch = fgetc(file2)) != EOF)
            {
                if (ch == ' ' || ch == '\n')
                {
                    count2++;
                }
            }

            printf("Word count : %d\n", count2);
            fclose(file2);

            printf("Difference in word size between files: %d\n", count2 - count1);
        }
    else
        {
            // printf("im here11111");
            FILE *file;
            char chb;
            int count = 0;
            file = fopen(option , "r");
            if (file == NULL)
            {
                printf("Error opening file\n");
                return 1;
            }

            while ((chb = fgetc(file)) != EOF)
            {
                if (chb == ' ' || chb == '\n')
                {
                    count++;
                }
            }

            printf("Word count ignoring newlines: %d\n", count);
            fclose(file);
        }

        return 0;
    }

    return 0;
}
