#include "bump_down_allocator.hpp"
#include "benchmark.hpp"
#include "../task-1/bump_allocator.hpp"

int main(){
    double down_timeTaken = benchmark([](){
        bump_down_allocator bump(1024);
        for (int i = 0; i < 100; i++){
            bump.alloc<char>(1);
            bump.alloc<int>(1);
        }
        for (int i = 0; i < 100; i++){
            bump.dealloc();
            bump.dealloc();
        }
    });

    double up_timeTaken = benchmark([](){
        bump_allocator bump(1024);
        for (int i = 0; i < 100; i++){
            bump.alloc<char>(1);
            bump.alloc<int>(1);
        }
        for (int i = 0; i < 100; i++){
            bump.dealloc();
            bump.dealloc();
        }
    });

    std::cout << "Time taken to benchmark DOWN allocator is " << down_timeTaken << "ms" << std::endl;
    std::cout << "Time taken to benchmark UP allocator is " << up_timeTaken << "ms" << std::endl;

    return 0;
};
