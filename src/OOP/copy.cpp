#include<iostream>
#include<cstring>

struct Vector2
{
    float x;
    float y;
    Vector2(float x, float y):x(x), y(y){}  
};

class String{
private:
    char* m_buffer;
    unsigned int m_size;
public:
    String(const char* string)
    {
        m_size = strlen(string);
        m_buffer = new char[m_size+1];
        memcpy(m_buffer,string, m_size+1);
        m_buffer[m_size] = 0;
    }
    ~String()
    {
        std::cout << "the destructor is called!" << std::endl;
        delete[] m_buffer;
    }
    // copy constructor, deep copy
    String(const String& other):m_size(other.m_size)
    {
        std::cout<<"copy constructor is called!" << std::endl;
        m_buffer = new char[m_size+1];
        memcpy(m_buffer, other.m_buffer, m_size+1);
    }

    char& operator[](unsigned int index)
    {
        return m_buffer[index];
    }

    friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

// pass by reference, avoid waste of memory
std::ostream& operator<<(std::ostream& stream, const String& string)
{
    stream<<string.m_buffer;
    return stream;
}

void printString(const String& string)
{
    std::cout<<string<<std::endl;
}
int main(){
    // int a=3;
    // // b and a have different memory address, but the value of a is copied to b
    // int b = a;

    // Vector2 A = {2,3};
    // // the same for A and B, changing B will not have influence on A
    // Vector2 B = A;
    // // the value of the pointer is copied (aka address) now changing the value of the object through p2 will influence p1
    // Vector2* p1 = new Vector2(3,4);
    // Vector2* p2 = p1;

    String string = "Hello";
    // with out copy constructor, shalow copy, only the pointer will be copyied, but the memory it pointing to
    // will not be copy. so m_buffer of string and string1 points to the same block of memory
    String string1 = string;
    string1[1] = 'a';
    printString(string1);
    std::cout<<string<<std::endl;
    return 0;
}