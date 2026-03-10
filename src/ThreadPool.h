#pragma once

#include "ThreadSafeQueue.h"
#include <thread>

class ThreadPool {
public:
    ThreadPool(int numberOfThreads) : m_Running{true} {

    }

    void Enqueue(std::function<void()>) {}

    void Shutdown() {}

private:
    bool m_Running;
    std::vector<std::jthread> m_Workers;


};