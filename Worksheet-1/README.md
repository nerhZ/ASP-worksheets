# Worksheet 1

This README is dedicated to worksheet 1 only, and will detail each of the four tasks.

## Task 1

GOAL: Implement simplified version of C++ string class.

For Task 1 I implemented my own string class utilising the interface provided. I initially set out to write it without using standard functions, but was assured that using standard functions is perfectly fine, so switched to simpler implementations - for example using `strlen()` & `strcpy()`.

I added one extra variable to the class: `m_data` of type `char*` which is used to store the string, but I decided not to store the size of the string as I believe the minor computation time required for `strlen()` to run is worth removing the chance of storing stale data. This leads to the following interface:

```c++
class my_string {
    public:
        my_string();
        my_string(const char*);

        my_string(my_string const& s);
        my_string& operator= (my_string const& s);
        // ~my_string();

        char getChar(const int& i) const;
        void setChar(const int& i, const char& c);
        void print() const;
    private:
        // Stores the string data
        char* m_data;
};
```

It is important to note that during initialisation I ensure to set the character array size to `strlen(input + 1)` to ensure that `strcpy(m_data, input)` can store the null terminator at the end of the string, as `strlen()` does not include the null terminator in it's length calculation. This is shown below:

```c++
// Default constructor
my_string::my_string(){
    m_data = nullptr;
};

// Constructor with string input
my_string::my_string(const char* input){
    m_data = new char[strlen(input) + 1];
    strcpy(m_data, input);
}
```

Two important parts of my implementation are ensuring that the overloaded `=` operator and the copy constructor both utilise shallow copies by address, rather than copying to a new place in memory, shown below:

```c++
// Copy constructor - using another my_string by reference, not a deep copy
my_string::my_string(my_string const& s){
    m_data = s.m_data;
};

// Assignment operator - by reference, not a deep copy
my_string& my_string::operator= (my_string const& s){
    if (this != &s){
        m_data = s.m_data;
    }
    return *this;
};
```

Both of these functions utilise the adress of the string to copy, so that it is directly set to the same point in memory. This means changing one string also changes the other. The assignment operator will also just return a reference to the current string object (if the strings are the same). This functionality in action is shown below (from the provided test file).

![Output of filetest_string.cpp running](./README_Images/image-1.png)

## Task 2-3

GOAL: Extend string class to include reference counting, and add print statements to display when the reference counter reaches zero.

In order to add reference counting to the class I added one new private variable to the class, `m_refCount`. This variable would be used to track the current number of references to the string. `m_refCount` is of `size_t` type for best practice, as it supports storing the count of the largest value possible (which could in theory be required). In initialisation I made sure to initialise `m_refCount` in memory and set it to 1, shown below:

```c++
// Default constructor
my_string::my_string(){
    m_data = nullptr;
    m_refCount = new size_t(0);
};

// Constructor with string input
my_string::my_string(const char* input){
    // Include + 1 to ensure strcpy has enough space to include the null terminator
    m_data = new char[strlen(input) + 1];
    strcpy(m_data, input);
    m_refCount = new size_t(1);
}
```

In order to implement reference counting correctly the assignment and copy operators had to both be altered to include incrementing `m_refCount`, and the destructor had to be implemented to decrement `m_refCount` when a reference goes out of scope. If `m_refCount` reached 0 then `m_data` and `m_refCount` both get freed from memory entirely.

```c++
// Copy constructor - using another my_string by reference, not a deep copy
my_string::my_string(my_string const& s){
    m_data = s.m_data;
    m_refCount = s.m_refCount;
    (*m_refCount)++;
};

// Assignment operator - by reference, not a deep copy
my_string& my_string::operator= (my_string const& s){
    if (this != &s){
        m_data = s.m_data;
        m_refCount = s.m_refCount;
        (*m_refCount)++;
    }
    return *this;
};
```

In order to prove the reference counter implementation was working as expected, I also altered the print function to print out the current reference count when printing the contents of the string:

```c++
void my_string::print() const{
    std::cout << m_data << " [" << *m_refCount << "]" << std::endl;
};
```

Destructor implementation:

```c++
// Destructor, deletes the string data and the reference count
// (if it is the last reference) or just decrements the reference counter
my_string::~my_string(){
    (*m_refCount)--;
    if (*m_refCount == 0){
        delete []m_data;
        delete m_refCount;
        // Task 3 print statement
        std::cout << "Destructor called: m_data and m_refCount fully deleted" << std::endl;
    } else {
        // Task 3 print statement
        std::cout << "Destructor called: m_refCount decremented to " << *m_refCount << std::endl;
    }
}
```

For Task 3 the goal was to display when the reference count reached zero, so I added two print statements to the destructor that stated when `m_refCount` gets decremented and also when `m_refCount` reaches zero (visible above).

When ran through the test suite it worked as expected, giving the following result, which satisfies both Task 2 and 3:

![Output of filetest_string.cpp running](./README_Images/image-2.png)

## Task 4

GOAL: Move reference counting to a separate template class that can be used to reference count any type.

First of all, I removed reference counting from the my_string class itself by removing `m_refCount` as a private variable, and all instances where it is handled (initialised, decremented, incremented) as this would now be handled by a separate template class `ref_counter`.

Due to how the compiler handles templates it is not possible to separate the interface of the class from the implementation for template classes. My reference counter's interface is shown below (method implementation removed for screenshot purposes):

```c++
template <typename T>
class ref_counter{
    public:
        // Default constructor, initialsie to nullptrs
        ref_counter();
        // Constructor with data, initialise ref_count to 1 and set p_data to data
        ref_counter(T* data);
        // Destructor, decrement ref_count and delete data if ref_count is 0
        ~ref_counter();
        // Dereference operator, return data
        T& operator*();
        // Arrow operator, return data
        T* operator->();
        // Assignment operator, copy data and increment ref_count (unless copying itself)
        ref_counter& operator=(ref_counter const& input);
        // Copy constructor, copy data and increment ref_count
        ref_counter(ref_counter const& input);
        //  Return the ref_count
        int returnRefCount();
    private:
        // Reference count and data
        size_t* m_refCount;
        T* p_data;
};
```

In my implementation `m_refCount` is now moved to this separate class, as well as a new private variable `p_data` which is a generic type, holding the same type the class is initialised with.

The two initialisers are both incredibly simple and simply set `m_refCount` and `p_data`.

```c++
// Default constructor, initialsie to nullptrs
ref_counter(): m_refCount(nullptr), p_data(nullptr){};
// Constructor with data, initialise ref_count to 1 and set p_data to data
ref_counter(T* data): m_refCount(new size_t(1)), p_data(data){};
```

The copy and assignment operator are both extremely similar to the implementation that was found natively inside the `my_string` class but stores the data relating to the referenced object entirely.

```c++
// Assignment operator, copy data and increment ref_count (unless copying itself)
ref_counter& operator=(ref_counter const& input){
    if (this != &input){
        p_data = input.p_data;
        m_refCount = input.m_refCount;
        (*m_refCount)++;
    }
    return *this;
}
// Copy constructor, copy data and increment ref_count
ref_counter(ref_counter const& input){
    p_data = input.p_data;
    m_refCount = input.m_refCount;
    (*m_refCount)++;
}
```

The deference & arrow operator both return the underlying object stored in `p_data`, allowing access of the stored variable and the stored type's attached methods, such as `getChar()` (in the case of `my_string` type).

```c++
// Dereference operator, return data
T& operator*(){
    if (p_data == nullptr){
        throw std::invalid_argument("Dereferencing nullptr");
    }
    return *p_data;
}
// Arrow operator, return data
T* operator->(){
    if (p_data == nullptr){
        throw std::invalid_argument("Dereferencing nullptr");
    }
    return p_data;
}
```

The destructor method decrements the reference counter like the original implementation in `my_string`, and fully frees `m_refCount` and `p_data` when the counter reaches zero.

```c++
// Destructor, decrement ref_count and delete data if ref_count is 0
~ref_counter(){
    (*m_refCount)--;
    if (*m_refCount == 0){
        delete p_data;
        delete m_refCount;
        std::cout << "Destructor called: m_data and ref_count fully deleted" << std::endl;
    } else {
        std::cout << "Destructor called: ref_count decremented to " << *m_refCount << std::endl;
    }
}
```

In order to test this new implementation I created the following test file (since one was not provided for Task 4):

```c++
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
        ref_counter<my_string> copied_string = test;
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
```

As you can see, it is being tested with the custom my_string class, as well as with a built in type (`integer`). I created an extra method for the class, being `returnRefCount()` in order to better illustrate the status of the reference counter for testing. Output of the test file can be seen below:

![Output of the testing file](./README_Images/image-3.png)

The test file features multiple defined scopes, in order to show fully removing the data, and testing the reference counter with an `int` has been shown in order to display the classes ability to be used for any type. Due to the implementation of the arrow and dereference operator, the stored type's built in functions can be called - for example `my_string` can call the `.print()` method and "Hello world" is printed as expected above.
