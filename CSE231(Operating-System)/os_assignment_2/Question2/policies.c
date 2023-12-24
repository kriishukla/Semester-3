#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>
#include <sys/wait.h>

int main()
{
    FILE *Output = fopen("Output.txt", "w");
    if (Output == NULL)
    {
        perror("fopen Output.txt");
        return 1;
    }

    struct timespec startA, endA, startB, endB, startC, endC;
    double timeA, timeB, timeC;

    dup2(fileno(Output), STDOUT_FILENO);

    clock_gettime(CLOCK_REALTIME, &startA);
    int pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork1");
        return 1;
    }
    else if (pid1 == 0)
    {
        nice(0);
        char *args[] = {"./FIFO_program", NULL};
        execvp(args[0], args);
        perror("execvp");
        return 1;
    }
    else
    {
        clock_gettime(CLOCK_REALTIME, &startB);
        int pid2 = fork();
        if (pid2 < 0)
        {
            perror("fork2");
            return 1;
        }
        else if (pid2 == 0)
        {
            char *args[] = {"./RR_program", NULL};
            execvp(args[0], args);
            perror("execvp");
            return 1;
        }
        else
        {
            clock_gettime(CLOCK_REALTIME, &startC);
            int pid3 = fork();
            if (pid3 < 0)
            {
                perror("fork3");
                return 1;
            }
            else if (pid3 == 0)
            {
                char *args[] = {"./OTHER_program", NULL};
                execvp(args[0], args);
                perror("execvp");
                return 1;
            }
            else
            {
                waitpid(pid3, NULL, 0);
                clock_gettime(CLOCK_REALTIME, &endC);

                timeC = (endC.tv_sec - startC.tv_sec) + (endC.tv_nsec - startC.tv_nsec) / 1000000000.0;
                printf("FIFO : %f seconds \n", timeC);
            }
            waitpid(pid2, NULL, 0);
            clock_gettime(CLOCK_REALTIME, &endB);

            timeB = (endB.tv_sec - startB.tv_sec) + (endB.tv_nsec - startB.tv_nsec) / 1000000000.0;
            printf("RR: %f seconds \n", timeB);
        }
        waitpid(pid1, NULL, 0);
        clock_gettime(CLOCK_REALTIME, &endA);

        timeA = (endA.tv_sec - startA.tv_sec) + (endA.tv_nsec - startA.tv_nsec) / 1000000000.0;
        printf("Other: %lf seconds \n", timeA);
    }
    fclose(Output);

    return 0;
}
