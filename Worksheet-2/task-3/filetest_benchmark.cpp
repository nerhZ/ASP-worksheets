#include "bump_down_allocator.hpp"
#include "benchmark.hpp"
#include "../task-1/bump_allocator.hpp"

// Function to allocate memory for char and int types, with the number of iterations and size of the memory block
void allocate_test_down(bump_down_allocator* bump_alloc, int iterations, int size){
    for (int i = 0; i < iterations; i++){
        bump_alloc->alloc<char>(size);
        bump_alloc->alloc<int>(size);
    }
};

// Function to allocate memory for char and int types, with the number of iterations and size of the memory block
void allocate_test_up(bump_allocator* bump_alloc, int iterations, int size){
    for (int i = 0; i < iterations; i++){
        bump_alloc->alloc<char>(size);
        bump_alloc->alloc<int>(size);
    }
}

int main(){
    // Benchmark the bump allocator and bump down allocator with 10,000 small allocations
    {
        bump_allocator bump_up(10000000);
        bump_down_allocator bump_down(1000000);

        double down_timeTaken = benchmark(*allocate_test_down, 10, &bump_down, 10000, 1);
        double up_timeTaken = benchmark(*allocate_test_up, 10, &bump_up, 10000, 1);

        std::cout << "10,000 Small-sized Allocations" << std::endl;
        std::cout << "Time taken to benchmark DOWN allocator is " << down_timeTaken << "ms" << std::endl;
        std::cout << "Time taken to benchmark UP allocator is " << up_timeTaken << "ms" << std::endl;
    }
    // Benchmark the bump allocator and bump down allocator with 5,000 medium allocations
    {
        bump_allocator bump_up(100000000);
        bump_down_allocator bump_down(100000000);

        double down_timeTaken = benchmark(*allocate_test_down, 10, &bump_down, 5000, 50);
        double up_timeTaken = benchmark(*allocate_test_up, 10, &bump_up, 5000, 50);

        std::cout << "5,000 Medium-sized Allocations" << std::endl;
        std::cout << "Time taken to benchmark DOWN allocator is " << down_timeTaken << "ms" << std::endl;
        std::cout << "Time taken to benchmark UP allocator is " << up_timeTaken << "ms" << std::endl;
    }
    // Benchmark the bump allocator and bump down allocator with 2,500 large allocations
    {
        bump_allocator bump_up(100000000);
        bump_down_allocator bump_down(100000000);

        double down_timeTaken = benchmark(*allocate_test_down, 10, &bump_down, 2500, 100);
        double up_timeTaken = benchmark(*allocate_test_up, 10, &bump_up, 2500, 100);

        std::cout << "2,500 Large-sized Allocations" << std::endl;
        std::cout << "Time taken to benchmark DOWN allocator is " << down_timeTaken << "ms" << std::endl;
        std::cout << "Time taken to benchmark UP allocator is " << up_timeTaken << "ms" << std::endl;
    }
    return 0;
};
