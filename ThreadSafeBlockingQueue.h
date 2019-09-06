//
// Created by paulos on 9/5/19.
//

#ifndef ASYNCPROCCODECHALLENGE_THREADSAFEBLOCKINGQUEUE_H
#define ASYNCPROCCODECHALLENGE_THREADSAFEBLOCKINGQUEUE_H

#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

template <class T>
class ThreadSafeBlockingQueue {
private:
    std::queue<T> q_;
    std::mutex mutex_;
    std::condition_variable cvar_;
public:
    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (q_.empty()) cvar_.wait(lock);
        auto result = std::move(q_.front());
        q_.pop();
        return result;
    }
    void push( T&& item) {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            q_.push(std::move(item));
        }
        cvar_.notify_one();
    }
    //locking s not required, because empty check is used only before poping
    bool empty(){
        return q_.empty();
    }




};
#endif //ASYNCPROCCODECHALLENGE_THREADSAFEBLOCKINGQUEUE_H
