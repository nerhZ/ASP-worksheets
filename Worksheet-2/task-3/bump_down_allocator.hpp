#pragma once
#include <cstddef>
#include <cstdlib>
#include <iostream>

class bump_down_allocator {
    public:
        bump_down_allocator(size_t size);
        template <typename T>
        T* alloc(T numObjects){
            // Get the current address of the memory block
            uintptr_t curAdr = reinterpret_cast<uintptr_t>(m_next);

            // Allocate memory for the object based on sizeof T and the number of objects
            size_t sizeBytes = sizeof(T) * numObjects;

            // Calculate aligned address by rounding down the current address to the nearest multiple of the alignment
            uintptr_t alignedAdr = curAdr & ~(alignof(T) - 1);

            // Check if there is enough memory to allocate after alignment
            if ((alignedAdr - sizeBytes) < reinterpret_cast<uintptr_t>(m_start)) {
                std::cout << "Not enough memory to allocate" << std::endl;
                return nullptr;
            }

            m_allocCounter++;
            m_next -= sizeBytes + (curAdr - alignedAdr);
            
            // Print the memory addresses of the next and current memory block to compare the difference    
            // std::cout << static_cast<void*>(m_next) << " " << reinterpret_cast<void*>(curAdr) << std::endl;
            // Print out the number of bytes difference between each address pointer by casting to an integer
            // std::cout << "Difference in bytes between the memory addresses is " << curAdr - reinterpret_cast<size_t>(m_next) << std::endl;

            // Return the current address of the memory block
            return reinterpret_cast<T*>(m_next);
        }
        size_t getAllocCounter();
        void dealloc();
        ~bump_down_allocator();
    private:
        char* m_start;
        char* m_next;
        size_t m_allocCounter;
        size_t m_size;
};