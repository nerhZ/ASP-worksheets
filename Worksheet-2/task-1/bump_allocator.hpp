#pragma once
#include <cstddef>
#include <cstdlib>
#include <iostream>

class bump_allocator {
    public:
        bump_allocator(size_t size, size_t alignmentNum = sizeof(int));
        template <typename T>
        T* alloc(T numObjects){
            // Allocate memory for the object based on size of T and the number of objects
            size_t sizeBytes = sizeof(T) * numObjects;
            // Check if there is enough memory to allocate
            if (sizeBytes + m_sizeAllocated > m_size){
                std::cout << "Not enough memory to allocate" << std::endl;
                return nullptr;
            }

            // Get the current address of the memory block
            char* curAdr = m_next;

            m_sizeAllocated += sizeof(T) * numObjects;
            m_allocCounter++;
            m_next += sizeBytes;
            
            // Print the memory addresses of the next and current memory block to compare the difference    
            std::cout << static_cast<void*>(m_next) << " " << static_cast<void*>(curAdr) << std::endl;
            // Print out the number of bytes difference between each address pointer by casting to an integer
            std::cout << "Difference in bytes between the memory addresses is " << static_cast<int>(m_next - curAdr) << std::endl;

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
        size_t m_alignmentNum;
};