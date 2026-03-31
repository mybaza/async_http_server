#ifndef DATAPROCESSOR_HPP
#define DATAPROCESSOR_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ConcurrentQueue {
public:
    void enqueue(T item);
    T dequeue();
    bool is_empty();

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
};

class DataProcessor {
public:
    void processData();
    void addData(int data);

private:
    ConcurrentQueue<int> dataQueue;
};

#endif // DATAPROCESSOR_HPP