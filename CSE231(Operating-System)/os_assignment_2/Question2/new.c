#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>
#include <sys/wait.h>

#define BILLION 1000000000L

void writeToFile(FILE *file, char *str, double time) {
    char buffer[100];
    sprintf(buffer, "%f", time);

    fprintf(file, str);
    fprintf(file, "\t");
    fprintf(file, buffer);
    fprintf(file, "\t");
}

int main() {
    FILE *file = fopen("benchmark.csv", "w");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    struct timespec startA, endA, startB, endB, startC, endC;
    double timeA, timeB, timeC;

    struct sched_param param;

    clock_gettime(CLOCK_REALTIME, &startA);
    int pid1 = fork();
    if (pid1 < 0) {
        perror("fork1");
        return 1;
    } else if (pid1 == 0) {
        // Child process 1
        nice(-1);
        FILE *output = fopen("outputA.txt", "w");
        if (output == NULL) {
            perror("fopen outputA.txt");
            return 1;
        }
        dup2(fileno(output), STDOUT_FILENO); // Redirect stdout to the output file

        char *args[] = {"./FIFO_program", NULL};
        execvp(args[0], args);

        perror("execvp");
        return 1;
    } else {
        clock_gettime(CLOCK_REALTIME, &startB);
        int pid2 = fork();
        if (pid2 < 0) {
            perror("fork2");
            return 1;
        } else if (pid2 == 0) {
            // Child process 2
            param.sched_priority = 10;
            sched_setscheduler(getpid(), SCHED_RR, &param);
            FILE *output = fopen("outputB.txt", "w");
            if (output == NULL) {
                perror("fopen outputB.txt");
                return 1;
            }
            dup2(fileno(output), STDOUT_FILENO); // Redirect stdout to the output file

            char *args[] = {"./RR_program", NULL};
            execvp(args[0], args);

            perror("execvp");
            return 1;
        } else {
            clock_gettime(CLOCK_REALTIME, &startC);
            int pid3 = fork();
            if (pid3 < 0) {
                perror("fork3");
                return 1;
            } else if (pid3 == 0) {
                // Child process 3
                param.sched_priority = 99;
                sched_setscheduler(getpid(), SCHED_FIFO, &param);
                FILE *output = fopen("outputC.txt", "w");
                if (output == NULL) {
                    perror("fopen outputC.txt");
                    return 1;
                }
                dup2(fileno(output), STDOUT_FILENO); // Redirect stdout to the output file

                char *args[] = {"./other_program", NULL};
                execvp(args[0], args);

                perror("execvp");
                return 1;
            } else {
                waitpid(pid3, NULL, 0);
                clock_gettime(CLOCK_REALTIME, &endC);

                timeC = (endC.tv_sec - startC.tv_sec) + (endC.tv_nsec - startC.tv_nsec) / 1000000000.0;
                writeToFile(file, "C", timeC);
                printf("Time taken by 3rd Process (SCHED_FIFO): %lf seconds \n", timeC);
            }
            waitpid(pid2, NULL, 0);
            clock_gettime(CLOCK_REALTIME, &endB);

            timeB = (endB.tv_sec - startB.tv_sec) + (endB.tv_nsec - startB.tv_nsec) / 1000000000.0;
            writeToFile(file, "B", timeB);
            printf("Time taken by 2nd Process (SCHED_RR): %lf seconds \n", timeB);
        }
        waitpid(pid1, NULL, 0);
        clock_gettime(CLOCK_REALTIME, &endA);

        timeA = (endA.tv_sec - startA.tv_sec) + (endA.tv_nsec - startA.tv_nsec) / 1000000000.0;
        writeToFile(file, "A", timeA);
        printf("Time taken by 1st Process (SCHED_OTHER): %lf seconds \n", timeA);
    }

    fprintf(file, "\n");
    fclose(file);

    return 0;
}
