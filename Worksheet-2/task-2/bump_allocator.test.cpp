#include "../task-1/bump_allocator.hpp"
#include "simpletest/simpletest.h"
#include "bump_allocator.test.hpp"

char const * groups[] = {
    "BumpUp",
    "BumpDown"
};

DEFINE_TEST_G(TestAllocationOverLimitReturnsNullptr, BumpUp){
    bump_allocator bump(1);

    char* a = bump.alloc<char>(2);
    TEST_MESSAGE(a == nullptr, "Allocation should be a nullptr due to being over memory limit!");
}

DEFINE_TEST_GF(TestAllocationUnderLimitReturnsPtr, BumpUp, BumpUpFixture){
    char* a = m_bumpAllocator->alloc<char>(1);
    TEST_MESSAGE(a != nullptr, "Allocation should not be a nullptr due to memory being available!");
}

DEFINE_TEST_GF(TestAllocationForIntIs4Bytes, BumpUp, BumpUpFixture){
    int* a = m_bumpAllocator->alloc<int>(1);
    int* b = m_bumpAllocator->alloc<int>(1);

    TEST_MESSAGE((reinterpret_cast<char*>(b) - reinterpret_cast<char*>(a)) == sizeof(int), "Difference between the memory addresses should be 4 bytes for int!");
}

DEFINE_TEST_GF(TestAllocationForCharis1Byte, BumpUp, BumpUpFixture){
    char* a = m_bumpAllocator->alloc<char>(1);
    char* b = m_bumpAllocator->alloc<char>(1);

    TEST_MESSAGE((reinterpret_cast<char*>(b) - reinterpret_cast<char*>(a)) == sizeof(char), "Difference between the memory addresses should be 1 byte for char!");
}

// NEEDS FIXING - Alignment is not correct
DEFINE_TEST_GF(TestAlignmentForIntAfterCharIs3Bytes, BumpUp, BumpUpFixture){
    char* a = m_bumpAllocator->alloc<char>(1);
    int* b = m_bumpAllocator->alloc<int>(1);
    char* c = m_bumpAllocator->alloc<char>(1);

    TEST_MESSAGE((int(c - a) -1) == 7, "Alignment should be equal to 3 bytes if assigning an integer after a char!");
}

// Also need to figure out how to check for free memory
DEFINE_TEST_GF(TestAllocatorFreesMemoryWhenAllAllocationsDeallocated, BumpUp, BumpUpFixture){
    int* a = m_bumpAllocator->alloc<int>(1);
    int* b = m_bumpAllocator->alloc<int>(1);
    int* c = m_bumpAllocator->alloc<int>(1);

    m_bumpAllocator->dealloc();
    m_bumpAllocator->dealloc();
    m_bumpAllocator->dealloc();

    int* d = m_bumpAllocator->alloc<int>(1);

    TEST_MESSAGE(a == d, "Memory should be allocated at the same address after deallocating all memory!");
}

int main() {
    bool pass = true;

    for (auto group : groups) {
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }

    return pass ? 0 : 1;
}