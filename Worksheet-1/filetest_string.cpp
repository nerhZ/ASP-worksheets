#include "my_string.hpp"

// Test suite from the worksheets
int main(){
    my_string s("Hello world");
    s.print();
    {
    my_string t = s;

    s.print();
    t.print();
    std::cout << s.getChar(1) << std::endl;
    s.print();
    t.print();
    }
    s.setChar(1,'E');
    s.print();
    
}

// Original test suite I used
// int main(){

//     // Test default constructor
//     // my_string s;

//     // Test initialisation
//     my_string s("hello");

//     // Test print method
//     std::cout << "Printing string: " << std::endl;
//     s.print();

//     // Test get character method
//     std::cout << "Get character return: " << s.getChar(1) << std::endl;

//     // Test set character method
//     std::cout << "Set character at index 1, new string: " << std::endl;
//     s.setChar(1, 'E');
//     s.print();

//     // Test copy constructor
//     my_string x;
//     x = s;
//     x.print();
//     x.setChar(1, 'T');
//     s.print();

//     return 0;
// }