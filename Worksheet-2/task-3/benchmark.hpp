#pragma once
#include <chrono>
#include <iostream>

template<typename Func, typename... Args>
double benchmark(Func func, Args... args) {
    auto startTime = std::chrono::high_resolution_clock::now();

    func(args...);

    auto endTime = std::chrono::high_resolution_clock::now();

     return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}