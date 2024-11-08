#include "bump_allocator.hpp"
#include <iostream>
#include <cstring>

int main(){
    bump_allocator bump(40);

    char* a = bump.alloc<char>(1);
    *a = 'a';

    char* b = bump.alloc<char>(1);
    *b = 'b';

    int* c = bump.alloc<int>(1);
    *c = 10;

    std::cout << "a address: " << static_cast<void*>(a) << std::endl;
    std::cout << "a value: " << *a << std::endl;
    std::cout << "b address: " << static_cast<void*>(b) << std::endl;
    std::cout << "b value: " << *b << std::endl;
    std::cout << "c address: " << static_cast<void*>(c) << std::endl;
    std::cout << "c value: " << *c << std::endl;

    bump.dealloc();
    bump.dealloc();
    bump.dealloc();

    int* d = bump.alloc<int>(1);
    *d = 20;

    std::cout << "d address: " << static_cast<void*>(d) << std::endl;
    std::cout << "d value: " << *d << std::endl;

    return 0;
}