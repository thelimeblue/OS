#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

sem_t mutex;  // For mutual exclusion of shared resource (forks)
sem_t forks[N]; // Semaphores representing forks

void* philosopher(void* num) {
    int id = *(int*)num;
    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1); // simulate thinking

        sem_wait(&mutex); // Ensure mutual exclusion for fork usage
        sem_wait(&forks[id]);  // Take left fork
        sem_wait(&forks[(id + 1) % N]); // Take right fork

        printf("Philosopher %d is eating\n", id);
        sleep(2); // simulate eating

        sem_post(&forks[id]);  // Release left fork
        sem_post(&forks[(id + 1) % N]); // Release right fork
        sem_post(&mutex); // Release mutual exclusion for the next philosopher

        sleep(1); // simulate delay before thinking again
    }
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int philosopher_ids[N] = {0, 1, 2, 3, 4};

    // Initialize the mutex and the forks (semaphores)
    sem_init(&mutex, 0, 1); // mutex for mutual exclusion
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1); // each fork is initially available
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Clean up semaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&mutex);

    return 0;
}
