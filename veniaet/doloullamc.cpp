#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

class IoTask {
public:
    void execute() {
        // Define the task to be executed
        std::cout << "Executing I/O task" << std::endl;
    }
};

class IoTaskPool {
private:
    std::queue<IoTask> tasks;  // Queue to hold I/O tasks
    std::mutex mtx;            // Mutex for thread safety
    std::condition_variable cv;// Condition variable for task availability

    IoTaskPool() = default;    // Private constructor for singleton pattern

public:
    // Singleton instance accessor
    static IoTaskPool& getInstance() {
        static IoTaskPool instance;
        return instance;
    }

    // Add a task to the pool
    void addTask(const IoTask& task) {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.push(task);
        cv.notify_one(); // Notify one waiting thread
    }

    // Get a task from the pool
    IoTask get() {
        std::unique_lock<std::mutex> lock(mtx);
        // Wait until a task is available
        cv.wait(lock, [this]() { return !tasks.empty(); });
        IoTask task = tasks.front();
        tasks.pop();
        return task;
    }
};

int main() {
    IoTaskPool& pool = IoTaskPool::getInstance();

    // Add a task to the pool
    IoTask task;
    pool.addTask(task);

    // Retrieve and execute a task from the pool
    IoTask retrievedTask = pool.get();
    retrievedTask.execute();

    return 0;
}
