#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PASSENGERS 100

int total_passengers;
int capacity;
int passengers_on_board = 0;
sem_t mutex, boardQueue, rideInProgress, unboardQueue;

void load();
void unload();
void board(int passenger_id);
void offboard(int passenger_id);
void car_ride();
void passenger_ride(int passenger_id);

void* passenger(void* args) {
    int passenger_id = *((int*)args);

    for (;;) {
        passenger_ride(passenger_id);
    }

    return NULL;
}

void load() {
    sem_wait(&mutex);
    printf("Car: Loading passengers...\n");
    sleep(1); 
    sem_post(&mutex);
}

void offboard(int passenger_id) {
    sem_wait(&mutex);
    printf("Passenger %d: Getting off the car...\n", passenger_id);
    sleep(1); 
    sem_post(&mutex);
}

void passenger_ride(int passenger_id) {
    sem_wait(&boardQueue);

    board(passenger_id);
    sem_post(&rideInProgress);

    sem_wait(&unboardQueue);

    offboard(passenger_id);

    sem_post(&rideInProgress);
}

void board(int passenger_id) {
    sem_wait(&mutex);
    printf("Passenger %d: Boarding the car...\n", passenger_id);
    sleep(1); 
    sem_post(&mutex);
}

void* car(void* args) {
    for (;;) {
        car_ride();
    }

    return NULL;
}

void unload() {
    sem_wait(&mutex);
    printf("Car: Unloading passengers...\n");
    sleep(1); 
    sem_post(&mutex);
}

void car_ride() {
    load();

    int i = 0;
    while (i < capacity) {
        sem_post(&boardQueue);
        i++;
    }

    i = 0;
    while (i < capacity) {
        sem_wait(&rideInProgress);
        i++;
    }

    printf("Car: Ride in progress...\n");
    sleep(2);

    unload();

    i = 0;
    while (i < capacity) {
        sem_post(&unboardQueue);
        i++;
    }

    i = 0;
    while (i < capacity) {
        sem_wait(&rideInProgress);
        i++;
    }
}

int main() {
    printf("Enter total number of passengers: ");
    scanf("%d", &total_passengers);

    printf("Enter car capacity: ");
    scanf("%d", &capacity);

    sem_init(&mutex, 0, 1);
    sem_init(&boardQueue, 0, 0);
    sem_init(&rideInProgress, 0, 0);
    sem_init(&unboardQueue, 0, 0);

    pthread_t car_thread;
    pthread_create(&car_thread, NULL, car, NULL);
    pthread_t passenger_threads[MAX_PASSENGERS];
    int passenger_ids[MAX_PASSENGERS];
    int i = 0;

    while (i < total_passengers) {
        passenger_ids[i] = i + 1; 
        pthread_create(&passenger_threads[i], NULL, passenger, &passenger_ids[i]);
        i++;
    }

    pthread_join(car_thread, NULL);

    i = 0;
    while (i < total_passengers) {
        pthread_join(passenger_threads[i], NULL);
        i++;
    }

    sem_destroy(&mutex);
    sem_destroy(&boardQueue);
    sem_destroy(&rideInProgress);
    sem_destroy(&unboardQueue);
    return 0;
}