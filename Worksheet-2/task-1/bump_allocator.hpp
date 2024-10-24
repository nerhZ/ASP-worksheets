#pragma once
#include <cstddef>
#include <cstdlib>
#include <iostream>

class bump_allocator {
    public:
        bump_allocator(size_t size);
        template <typename T>
        T* alloc(T numObjects){
            // Get the current address of the memory block
            char* curAdr = m_next;

            // Allocate memory for the object based on size of T and the number of objects
            size_t sizeBytes = sizeof(T) * numObjects;

            // Calculate the alignment offset & clear the lower bits
            size_t alignmentOffset = (reinterpret_cast<size_t>(m_next) + alignof(T) - 1) & ~(alignof(T) - 1);
            size_t alignmentDiff = alignmentOffset - reinterpret_cast<size_t>(curAdr);

            // Check if there is enough memory to allocate after alignment
            if (sizeBytes + alignmentDiff + m_sizeAllocated > m_size) {
                std::cout << "Not enough memory to allocate" << std::endl;
                return nullptr;
            }

            m_sizeAllocated += sizeBytes + alignmentDiff;
            m_allocCounter++;
            m_next = curAdr + sizeBytes + alignmentDiff;
            
            // Print the memory addresses of the next and current memory block to compare the difference    
            std::cout << static_cast<void*>(m_next) << " " << static_cast<void*>(curAdr) << std::endl;
            // Print out the number of bytes difference between each address pointer by casting to an integer
            std::cout << "Difference in bytes between the memory addresses is " << static_cast<size_t>(m_next - curAdr) << std::endl;

            // Return the current address of the memory block
            return reinterpret_cast<T*>(curAdr);
        }
        void dealloc();
        ~bump_allocator();
    private:
        char* m_start;
        char* m_next;
        size_t m_allocCounter;
        size_t m_size;
        size_t m_sizeAllocated;
};