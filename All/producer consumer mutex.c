#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int count = 0;
int in = 0, out = 0;

pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = i + 1;

        pthread_mutex_lock(&mutex);
        if (count < SIZE) {
            buffer[in] = item;
            printf("Producer produced: %d\n", item);
            in = (in + 1) % SIZE;
            count++;
        } else {
            printf("Buffer full. Producer waiting...\n");
        }
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        if (count > 0) {
            item = buffer[out];
            printf("Consumer consumed: %d\n", item);
            out = (out + 1) % SIZE;
            count--;
        } else {
            printf("Buffer empty. Consumer waiting...\n");
        }
        pthread_mutex_unlock(&mutex);

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
