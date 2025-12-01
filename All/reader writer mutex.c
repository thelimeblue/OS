#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int readcount = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;      // controls readcount
pthread_mutex_t write_lock = PTHREAD_MUTEX_INITIALIZER; // ensures writer exclusivity

void* reader(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        readcount++;
        if (readcount == 1)
            pthread_mutex_lock(&write_lock); // first reader blocks writers
        pthread_mutex_unlock(&mutex);

        printf("Reader %d is reading\n", id);
        sleep(1);

        pthread_mutex_lock(&mutex);
        readcount--;
        if (readcount == 0)
            pthread_mutex_unlock(&write_lock); // last reader unlocks writer
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&write_lock);
        printf("Writer %d is writing\n", id);
        sleep(2);
        pthread_mutex_unlock(&write_lock);

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int r_id[3] = {1, 2, 3};
    int w_id[2] = {1, 2};

    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &r_id[i]);
    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &w_id[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    return 0;
}
