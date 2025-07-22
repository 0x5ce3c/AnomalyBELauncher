#include "main.h"
#include "ThreadWrapper.hpp"

void ThreadWrapper::joinAll() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& threadPtr : threads) {
        if (threadPtr->joinable()) {
            threadPtr->join();
        }
    }
    threads.clear();
}

int ThreadWrapper::GetCountErrors() const {
    return errors;
}

std::unique_ptr<ThreadWrapper> ThreadWrapper::create() {
    return std::unique_ptr<ThreadWrapper>(new ThreadWrapper());
}

ThreadWrapper::~ThreadWrapper() {
    joinAll();
}