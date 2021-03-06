#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

// A threadsafe-queue.
template <class T>
class ThreadQueue
{
public:
    ThreadQueue(void)
        : q()
        , m()
        , c()
    {}

    ~ThreadQueue(void)
    {}

    // Add an element to the queue.
    void Enqueue(T t)
    {
        std::lock_guard<std::mutex> lock(m);
        q.push(t);
        c.notify_one();
    }

    //Return the size, avoids stalls on dequeue
    size_t Size() {
        std::unique_lock<std::mutex> lock(m);
        return q.size();
    }

    // Get the "front"-element.
    // If the queue is empty, wait till a element is avaiable.
    T Dequeue(void)
    {
        std::unique_lock<std::mutex> lock(m);
        while (q.empty())
        {
            // release lock as long as the wait and reaquire it afterwards.
            c.wait(lock);
        }
        T val = q.front();
        q.pop();
        return val;
    }
    T Peek(void)
    {
        std::unique_lock<std::mutex> lock(m);
        while (q.empty())
        {
            // release lock as long as the wait and reaquire it afterwards.
            c.wait(lock);
        }
        T val = q.front();
        //We won't pop here..... Just peeking
        return val;
    }
private:
    std::queue<T> q;
    mutable std::mutex m;
    std::condition_variable c;
};
