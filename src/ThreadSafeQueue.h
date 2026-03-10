#include <functional>
#include <mutex>
#include <queue>
#include <utility>

template <typename F>
class ThreadSafeQueue {
public:
    ThreadSafeQueue();
    ThreadSafeQueue(const ThreadSafeQueue& other);
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    void Enqueue(F&& task) {
        std::unique_lock<std::mutex> ul{m_Mux};
        m_TaskQueue.emplace(std::forward<F>(task));
        ul.unlock();
        m_DataCondition.notify_one();
    }

    F& WaitAndPop() {
        std::unique_lock<std::mutex> ul{m_Mux};
        m_DataCondition.wait(ul, [this] { return !m_TaskQueue.empty(); });
        F task = m_TaskQueue.front();
        m_TaskQueue.pop();
        return task;
    }

private:
    std::mutex m_Mux;
    std::queue<std::function<void()>> m_TaskQueue;
    std::condition_variable m_DataCondition;

};