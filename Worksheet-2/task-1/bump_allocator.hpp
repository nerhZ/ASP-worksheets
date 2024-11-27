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
            uintptr_t curAdr = reinterpret_cast<uintptr_t>(m_next);

            // Allocate memory for the object based on size of T and the number of objects
            size_t sizeBytes = sizeof(T) * numObjects;

            // Calculate the alignment offset & clear the lower bits, rounding up to the nearest multiple of the alignment
            uintptr_t alignedAdr = (curAdr + (alignof(T) - 1)) & ~(alignof(T) - 1);
            // Calculate the alignment offset - no chance of curAdr being less than alignedAdr
            uintptr_t alignmentOffset = alignedAdr - curAdr;

            // Check if there is enough memory to allocate after alignment
            if (sizeBytes + alignmentOffset + m_sizeAllocated > m_size) {
                std::cout << "Not enough memory to allocate" << std::endl;
                return nullptr;
            }

            m_sizeAllocated += sizeBytes + alignmentOffset;
            m_allocCounter++;
            m_next += alignmentOffset + sizeBytes;
            
            // Print the memory addresses of the next and current memory block to compare the difference    
            // std::cout << static_cast<void*>(m_next) << " " << reinterpret_cast<void*>(curAdr) << std::endl;
            // Print out the number of bytes difference between each address pointer by casting to an integer
            // std::cout << "Difference in bytes (including alignment) between the memory addresses is " << reinterpret_cast<size_t>(m_next) - curAdr << std::endl;

            // Return the aligned address before sizeBytes is added (points to start of newly allocated memory after alignment)
            return reinterpret_cast<T*>(alignedAdr);
        }
        size_t getAllocCounter();
        void dealloc();
        ~bump_allocator();
    private:
        char* m_start;
        char* m_next;
        size_t m_allocCounter;
        size_t m_size;
        size_t m_sizeAllocated;
};