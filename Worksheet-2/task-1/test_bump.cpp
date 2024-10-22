#include "bump_allocator.hpp"
#include <iostream>
#include <cstring>

int main(){
    bump_allocator bump(10);

    int* x = bump.alloc<int>(1);
    *x = 2;

    // *x.dealloc();

    char* y = bump.alloc<char>(1);
    *y = 'a';

    char* z = bump.alloc<char>(3);
    strcpy(z, "abc");

    std::cout << "x: " << *x << std::endl;
    std::cout << "y: " << *y << std::endl;
    std::cout << "z: " << *z << *(z+1) << *(z+2) << std::endl;
    return 0;
}