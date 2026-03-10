#pragma once
#include <functional>
#include <mutex>
#include <queue>

class ThreadSafeQueue {
public:
    ThreadSafeQueue();
    ThreadSafeQueue(const ThreadSafeQueue& other);
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    using TaskFunc_t = std::function<void()>;

    void Push(TaskFunc_t& task) {
        std::unique_lock<std::mutex> ul{m_Mux};
        m_TaskQueue.emplace(std::forward<TaskFunc_t>(task));
        ul.unlock();
        m_DataCondition.notify_one();
    }

    TaskFunc_t Pop() {
        std::unique_lock<std::mutex> ul{m_Mux};
        m_DataCondition.wait(ul, [this] { return !m_TaskQueue.empty(); });
        TaskFunc_t task = m_TaskQueue.front();
        m_TaskQueue.pop();
        return task;
    }

public:
    std::condition_variable m_DataCondition;

private:
    std::mutex m_Mux;
    std::queue<TaskFunc_t> m_TaskQueue;

};