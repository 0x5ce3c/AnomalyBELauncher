#ifndef THREADWRAPPER_HPP
#define THREADWRAPPER_HPP

#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include <chrono>

class ThreadWrapper {
public:
    static std::unique_ptr<ThreadWrapper> create();

    template<typename func>
    void beginThread(func f);

    template<typename func, class ... args_types>
    void beginThreadex(func f, args_types ... args);

    void joinAll();
    int GetCountErrors() const;

    ~ThreadWrapper();

private:
    std::vector<std::unique_ptr<std::thread>> threads;
    std::mutex mtx;
    int errors = 0;
};

// Реализация методов

template<typename func>
void ThreadWrapper::beginThread(func f) {
    try {
        auto threadPtr = std::make_unique<std::thread>(f);
        std::lock_guard<std::mutex> lock(mtx);
        threads.push_back(std::move(threadPtr));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    catch (const std::exception& e) {
        std::cerr << "Error creating thread: " << e.what() << std::endl;
        errors++;
    }
}

template<typename func, class ... args_types>
void ThreadWrapper::beginThreadex(func f, args_types ... args) {
    try {
        auto threadPtr = std::make_unique<std::thread>(std::bind(f, args...));
        std::lock_guard<std::mutex> lock(mtx);
        threads.push_back(std::move(threadPtr));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    catch (const std::exception& e) {
        std::cerr << "Error creating thread: " << e.what() << std::endl;
        errors++;
    }
}



#endif // THREADWRAPPER_HPP