 #include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CARS 100

sem_t bridgeSem;
sem_t leftSem, rightSem;
pthread_mutex_t mutex;

int leftCount = 0, rightCount = 0;

void passing(int dir, int carNumber) {
    printf("Car %d from %s side is traveling on the bridge.\n", carNumber, (dir == 0) ? "Left" : "Right");
    sleep(1);  
}

void* left(void* args) {
 
    int carNumber = *((int*)args);

    sem_wait(&leftSem);  

    pthread_mutex_lock(&mutex);

    sem_wait(&bridgeSem);  
    passing(0, carNumber);
    sem_post(&bridgeSem);  

    pthread_mutex_unlock(&mutex);

    sem_post(&leftSem);
    pthread_exit(NULL);
}

void* right(void* args) {

    int carNumber = *((int*)args);

    sem_wait(&rightSem);  

    pthread_mutex_lock(&mutex);

    sem_wait(&bridgeSem);  
    passing(1, carNumber);
    sem_post(&bridgeSem);  

    pthread_mutex_unlock(&mutex);

    sem_post(&rightSem);
    pthread_exit(NULL);
}

int main() {
    int numLeft, numRight;

    printf("Enter the number of cars from the left: ");
    scanf("%d", &numLeft);
    printf("Enter the number of cars from the right: ");
    scanf("%d", &numRight);

    if (numLeft + numRight > MAX_CARS) {
        printf("Total number of cars exceeds the limit. Exiting.\n");
        return 1;
    }

    sem_init(&bridgeSem, 0, 5);
    sem_init(&leftSem, 0, 5);
    sem_init(&rightSem, 0, 5);
    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[MAX_CARS];
    int carNumbers[MAX_CARS];

    for (int i = 0; i < numLeft; ++i) {
        carNumbers[i] = i + 1;
        pthread_create(&threads[i], NULL, left, &carNumbers[i]);
    }

    for (int i = 0; i < numRight; ++i) {
        carNumbers[i + numLeft] = i + 1;
        pthread_create(&threads[i + numLeft], NULL, right, &carNumbers[i + numLeft]);
    }

    for (int i = 0; i < numLeft + numRight; ++i) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&bridgeSem);
    sem_destroy(&leftSem);
    sem_destroy(&rightSem);
    pthread_mutex_destroy(&mutex);

    return 0;
}
