#include "bump_allocator.hpp"
#include <iostream>
#include <cstring>

int main(){
    bump_allocator bump(40);

    char* a = bump.alloc<char>(1);
    *a = 'a';

    int* x = bump.alloc<int>(1);
    *x = 2;

    // *x.dealloc();

    char* y = bump.alloc<char>(1);
    *y = 'a';

    long* b = bump.alloc<long>(1);
    *b = 1234123123;

    // char* z = bump.alloc<char>(3);
    // strcpy(z, "abc");

    int* w = bump.alloc<int>(1);
    *w = 923;

    std::cout << "x: " << *x << std::endl;
    std::cout << "y: " << *y << std::endl;
    // std::cout << "z: " << *z << *(z+1) << *(z+2) << std::endl;
    std::cout << "w: " << *w << std::endl;
    return 0;
}