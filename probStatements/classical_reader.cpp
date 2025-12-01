#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;

int readCount = 0;
bool isWriting = false;

void reader(int id)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);

        // Readers wait if a writer is writing
        cv.wait(lock, []()
                { return !isWriting; });

        readCount++;
        std::cout << "Reader " << id << " started reading. Active readers: "
                  << readCount << "\n";

        lock.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        lock.lock();
        readCount--;
        std::cout << "Reader " << id << " finished reading. Active readers: "
                  << readCount << "\n";

        if (readCount == 0)
            cv.notify_all();

        lock.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void writer(int id)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);

        // Writers wait if readers exist or writer is active
        cv.wait(lock, []()
                { return !isWriting && readCount == 0; });

        isWriting = true;
        std::cout << "Writer " << id << " started writing\n";

        lock.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(2));

        lock.lock();
        isWriting = false;
        std::cout << "Writer " << id << " finished writing\n";

        cv.notify_all();
        lock.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main()
{
    std::vector<std::thread> readers, writers;

    for (int i = 1; i <= 5; i++)
        readers.emplace_back(reader, i);

    for (int i = 1; i <= 2; i++)
        writers.emplace_back(writer, i);

    for (auto &th : readers)
        th.join();
    for (auto &th : writers)
        th.join();

    return 0;
}
