#pragma once

#include <memory>
#include "../task-1/bump_allocator.hpp"
#include "simpletest/simpletest.h"

// Fixture that allows test cases to be run on the bump allocator without manually redeclaring the bump allocator 
// (Unless a different size is needed)
class BumpUpFixture: public TestFixture{
    public:
        void Setup() override {
            m_bumpAllocator = std::make_unique<bump_allocator>(1024);
        }

        void TearDown() override { 
            size_t allocCount = m_bumpAllocator->getAllocCounter();
            while (allocCount > 0){
                m_bumpAllocator->dealloc();
                allocCount--;
            };

            // Reset the bump allocator to nullptr to free memory
            m_bumpAllocator.reset(nullptr);
        }

    std::unique_ptr<bump_allocator> m_bumpAllocator;
};