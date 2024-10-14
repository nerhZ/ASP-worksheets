#include "my_string.hpp"
#include "reference_counter.hpp"

// Test suite from the worksheets
int main(){
    {
        std::cout << "Testing reference counter with my_string" << std::endl;
        ref_counter<my_string> test(new my_string("Hello world"));
        test->print();
        std::cout << test.returnRefCount() << std::endl;
        {
            ref_counter<my_string> x = test;
            std::cout << test.returnRefCount() << std::endl;
        }
        std::cout << test.returnRefCount() << std::endl;
        ref_counter<my_string> copied_string = (test);
        std::cout << test.returnRefCount() << std::endl;
    }
    {
        std::cout << "Testing reference counter with int" << std::endl;
        ref_counter<int> test(new int(5));
        std::cout << test.returnRefCount() << std::endl;
        {
            ref_counter<int> x = test;
            std::cout << x.returnRefCount() << std::endl;
        }
        std::cout << test.returnRefCount() << std::endl;
    }
}