#pragma once

template <typename T>
class ref_counter{
    public:
        // Default constructor, initialsie to nullptrs
        ref_counter(): m_refCount(nullptr), p_data(nullptr){};
        // Constructor with data, initialise ref_count to 1 and set p_data to data
        ref_counter(T* data): m_refCount(new int(1)), p_data(data){};
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
        //  Return the ref_count
        int returnRefCount(){
            return *m_refCount;
        }
    private:
        // Reference count and data
        int* m_refCount;
        T* p_data;
};