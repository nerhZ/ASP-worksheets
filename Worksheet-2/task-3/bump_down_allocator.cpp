#include "bump_down_allocator.hpp"
#include <cstring>
#include <cstdlib>
#include <iostream>

// Constructor for the bump allocator - takes in the size of the memory block and allocates memory

bump_down_allocator::bump_down_allocator(size_t size) 
    : m_size(size), m_allocCounter(0) {
    // Allocate memory for the bump allocator and set to the start of the memory block
    m_start = new char[size];

    // set the next pointer to the end of the memory block

    m_next = m_start + (size - 1);
}

void bump_down_allocator::dealloc(){
    --m_allocCounter;
    if (m_allocCounter == 0){
        // Reset the next pointer to the start of the memory block
        m_next = m_start + (m_size - 1);
        // Set the memory from the start pointer to the size allocated to 0
        std::memset(reinterpret_cast<void*>(m_start), 0, (m_size-1));
    }
}

size_t bump_down_allocator::getAllocCounter(){
    return m_allocCounter;
}

bump_down_allocator::~bump_down_allocator(){
    std::cout << "Destructor called, freeing allocated memory" << std::endl;
    delete(m_start);
    m_start = nullptr;
}