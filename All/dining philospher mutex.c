#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // Number of philosophers

pthread_mutex_t forks[N]; // Mutexes representing forks

void* philosopher(void* num) {
    int id = *(int*)num;
    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1); // simulate thinking

        pthread_mutex_lock(&forks[id]); // Take left fork
        pthread_mutex_lock(&forks[(id + 1) % N]); // Take right fork

        printf("Philosopher %d is eating\n", id);
        sleep(2); // simulate eating

        pthread_mutex_unlock(&forks[id]); // Release left fork
        pthread_mutex_unlock(&forks[(id + 1) % N]); // Release right fork

        sleep(1); // simulate delay before thinking again
    }
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int philosopher_ids[N] = {0, 1, 2, 3, 4};

    // Initialize the mutexes for each fork
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Clean up mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
