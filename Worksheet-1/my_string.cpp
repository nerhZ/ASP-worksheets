#include "my_string.hpp"
#include <iostream>
#include <stdexcept>

// '\0';

my_string::my_string(){
    m_data = new char[1];
    m_size = strlen(m_data);
};


my_string::my_string(const char* input){
    
    m_data = new char[strlen(input) + 1];
    strcpy(m_data, input);
    m_size = strlen(m_data);

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

my_string::my_string(my_string const& s){
    m_data = s.m_data;
    m_size = s.m_size;
};

my_string& my_string::operator= (my_string const& s){
    m_data = s.m_data;
    m_size = s.m_size;
    return *this;
};

char my_string::getChar(const int& i) const{
    if (m_size < 0 || i > m_size){
        // std::cout << "String is empty" << std::endl;
        // return '\0';
        throw std::invalid_argument("Index out of bounds for string");
    }
    return m_data[i];
};

void my_string::setChar(const int& i, const char& c){
    if (m_size < 0 || i > m_size){
        // std::cout << "String is empty" << std::endl;
        throw std::invalid_argument("Index out of bounds for string");
    }
    m_data[i] = c;
};

void my_string::print() const{
    std::cout << m_data << std::endl;
};

// my_string::~my_string();