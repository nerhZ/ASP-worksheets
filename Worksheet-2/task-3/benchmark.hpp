#pragma once
#include <chrono>
#include <iostream>

template <typename Func, typename... Args>
double benchmark(Func& func, uint iterations,  Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; i++){
        func(std::forward<Args>(args)...);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count()/iterations;
}