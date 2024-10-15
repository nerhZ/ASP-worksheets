#include "my_string.hpp"
#include <iostream>
#include <stdexcept>

// '\0';

// Default constructor
my_string::my_string(){
    m_data = nullptr;
    m_size = 0;
    m_refCount = new size_t(1);
};

// Constructor with string input
my_string::my_string(const char* input){
    m_size = strlen(input) - 1; // Removes null terminator due to storage of string size (unnecessary character)
    m_data = new char[m_size];
    strcpy(m_data, input);
    m_refCount = new size_t(1);

    // BELOW CODE IS MY ORIGINAL IMPLEMENTATION:
    // Switched my implementation for simpler built in functions
    // const char* inputPointer = input;

    // while (*inputPointer != '\0'){
    //     // std::cout << inputPointer << std::endl;
    //     inputPointer++;
    //     m_size++;
    // }

    // str = new char[m_size];

    // for (int i = 0; i < m_size; i++){
    //     std::cout << str[i] << " " << input << std::endl;
    //     str[i] = input[i];
    // }

    // std::cout << m_data << std::endl;
    // std::cout << int(m_data[m_size]) << std::endl;
    // std::cout << int(m_data[m_size-1]) << std::endl;
};

// Copy constructor - using another my_string by reference, not a deep copy
my_string::my_string(my_string const& s){
    m_data = s.m_data;
    m_size = s.m_size;
    m_refCount = s.m_refCount;
    (*m_refCount)++;
};

// Assignment operator - by reference, not a deep copy
my_string& my_string::operator= (my_string const& s){
    if (this != &s){
        m_data = s.m_data;
        m_size = s.m_size;
        m_refCount = s.m_refCount;
        (*m_refCount)++;
    }
    return *this;
};

// Get a character from the string at a given index
char my_string::getChar(const int& i) const{
    if (i < 0 || i >= m_size){
        throw std::invalid_argument("Index out of bounds for string");
    }
    return m_data[i];
};

//  Set a character in the string at a given index
void my_string::setChar(const int& i, const char& c){
    if (m_size < 0 || i > m_size){
        // std::cout << "String is empty" << std::endl;
        throw std::invalid_argument("Index out of bounds for string");
    }
    m_data[i] = c;
};

void my_string::print() const{
    std::cout << m_data << " [" << *m_refCount << "]" << std::endl;
};

// Destructor, deletes the string data and the reference count 
// (if it is the last reference) or just decrements the reference counter
my_string::~my_string(){
    (*m_refCount)--;
    if (*m_refCount == 0){
        delete []m_data;
        delete m_refCount;
        std::cout << "Destructor called: m_data and m_refCount fully deleted" << std::endl;
    } else {
        std::cout << "Destructor called: m_refCount decremented to " << *m_refCount << std::endl;
    }
}