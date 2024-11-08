#include "bump_allocator.hpp"
#include <cstring>

// Constructor for the bump allocator - takes in the size of the memory block and allocates memory
bump_allocator::bump_allocator(size_t size) 
    : m_size(size), m_allocCounter(0), m_sizeAllocated(0) {
    // Allocate memory for the bump allocator and set to the start of the memory block
    m_start = new char[size];
    // set the next pointer to the start pointer
    m_next = m_start;
}

void bump_allocator::dealloc(){
    --m_allocCounter;
    if (m_allocCounter == 0){
        // Reset the next pointer to the start of the memory block
        m_next -= m_sizeAllocated;
        // Set the memory from the start pointer to the size allocated to 0
        std::memset(reinterpret_cast<void*>(m_start), 0, m_sizeAllocated);
        std::cout << "m_allocCounter reached 0, memory block has been reset" << std::endl;
    }
}

size_t bump_allocator::getAllocCounter(){
    return m_allocCounter;
}

bump_allocator::~bump_allocator(){
    std::cout << "Destructor called, freeing allocated memory" << std::endl;
    delete(m_start);
    m_start = nullptr;
}