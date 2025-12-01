#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readcount = 0;  // number of active readers
sem_t mutex;        // controls access to readcount
sem_t wrt;          // ensures writers' exclusive access

void* reader(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1)
            sem_wait(&wrt); // first reader locks the writer
        sem_post(&mutex);

        printf("Reader %d is reading\n", id);
        sleep(1); // simulate reading

        sem_wait(&mutex);
        readcount--;
        if (readcount == 0)
            sem_post(&wrt); // last reader unlocks the writer
        sem_post(&mutex);

        sleep(1); // simulate delay before next read
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&wrt);
        printf("Writer %d is writing\n", id);
        sleep(2); // simulate writing
        sem_post(&wrt);
        sleep(2); // simulate delay before next write
    }
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int r_id[3] = {1, 2, 3};
    int w_id[2] = {1, 2};

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &r_id[i]);
    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &w_id[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}
