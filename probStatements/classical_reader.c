#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

int readCount = 0; // Number of active readers
int isWriting = 0; // Flag to check if writer is writing

void *reader(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        pthread_mutex_lock(&mutex);

        // Readers wait if a writer is writing
        while (isWriting)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        readCount++;
        printf("Reader %d started reading. Readers active: %d\n", id, readCount);

        pthread_mutex_unlock(&mutex);

        // Simulate reading
        sleep(1);

        pthread_mutex_lock(&mutex);
        readCount--;
        printf("Reader %d finished reading. Readers active: %d\n", id, readCount);

        // Wake writers if last reader finishes
        if (readCount == 0)
            pthread_cond_broadcast(&cond);

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        pthread_mutex_lock(&mutex);

        // Writers wait if ANY reader is reading or a writer is writing
        while (readCount > 0 || isWriting)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        isWriting = 1;
        printf("Writer %d started writing.\n", id);

        pthread_mutex_unlock(&mutex);

        // Simulate writing
        sleep(2);

        pthread_mutex_lock(&mutex);

        isWriting = 0;
        printf("Writer %d finished writing.\n", id);

        // Wake up all waiting readers and writers
        pthread_cond_broadcast(&cond);

        pthread_mutex_unlock(&mutex);

        sleep(2);
    }
}

int main()
{
    pthread_t r[5], w[2];
    int r_id[5], w_id[2];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // Create 5 readers
    for (int i = 0; i < 5; i++)
    {
        r_id[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &r_id[i]);
    }

    // Create 2 writers
    for (int i = 0; i < 2; i++)
    {
        w_id[i] = i + 1;
        pthread_create(&w[i], NULL, writer, &w_id[i]);
    }

    // Join (never reached)
    for (int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
