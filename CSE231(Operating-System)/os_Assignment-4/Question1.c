#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define numberofphilosphers 5
#define numberofbowls 2

pthread_mutex_t mutex;
pthread_cond_t fork_and_bowl_available;

pthread_mutex_t forks[numberofphilosphers];
pthread_mutex_t bowls[numberofbowls];

typedef struct {
    int philosopher_id;
    int left_fork;
    int right_fork;
} Philosopher;

void eating(int philosopher_id) {
    printf("Philosopher %d is eating\n", philosopher_id);
    usleep(rand() % 1000000);  // time for which the philosopher is eating
}

void thinking(int philosopher_id) {
    printf("Philosopher %d is thinking\n", philosopher_id);
    usleep(rand() % 1000000);  // time for which the philosopher is thinking
}

void* philosopher(void* args) {
    Philosopher* data = (Philosopher*)args;

    while (1) {
        thinking(data->philosopher_id);

        pthread_mutex_lock(&mutex);

        // Attempt to pick up both forks and a bowl
        while (1) {
            if (pthread_mutex_trylock(&forks[data->left_fork]) == 0) {
                if (pthread_mutex_trylock(&forks[data->right_fork]) == 0) {
                    int bowl_index = -1;
                    if (pthread_mutex_trylock(&bowls[0]) == 0) {
                        bowl_index = 0;
                    } else if (pthread_mutex_trylock(&bowls[1]) == 0) {
                        bowl_index = 1;
                    }

                    if (bowl_index != -1) {
                        // Successfully acquired forks and a bowl
                        pthread_mutex_unlock(&mutex);  
                        break;
                    }

                    pthread_mutex_unlock(&forks[data->right_fork]);  
                }

                pthread_mutex_unlock(&forks[data->left_fork]);  
            }

            pthread_cond_wait(&fork_and_bowl_available, &mutex);
        }

        pthread_mutex_unlock(&mutex);

        eating(data->philosopher_id);

        // Release forks and bowl
        pthread_mutex_unlock(&forks[data->left_fork]);
        pthread_mutex_unlock(&forks[data->right_fork]);
        pthread_mutex_unlock(&bowls[0]);
        pthread_mutex_unlock(&bowls[1]);

        // Signal that the philosopher has finished eating
        pthread_cond_signal(&fork_and_bowl_available);
    }
}

int main() {
   pthread_t philosophers[numberofphilosphers];
    Philosopher philosopher_data[numberofphilosphers];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&fork_and_bowl_available, NULL);

    for (int i = 0; i < numberofphilosphers; ++i) {
        pthread_mutex_init(&forks[i], NULL);
        philosopher_data[i].philosopher_id = i;
        philosopher_data[i].left_fork = i;
        philosopher_data[i].right_fork = (i + 1) % numberofphilosphers;
    }

    for (int i = 0; i < numberofbowls; ++i) {
        pthread_mutex_init(&bowls[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < numberofphilosphers; ++i) {
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_data[i]);
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < numberofphilosphers; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    // Cleanup
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&fork_and_bowl_available);

    for (int i = 0; i < numberofphilosphers; ++i) {
        pthread_mutex_destroy(&forks[i]);
    }

    for (int i = 0; i < numberofbowls; ++i) {
        pthread_mutex_destroy(&bowls[i]);
    }
    return 0;
}