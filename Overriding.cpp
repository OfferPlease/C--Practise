#include <iostream>
class Test
{
public:
    Test(){std::cout << "Construcotr!\n";}
    ~Test(){std::cout << "Destructor!\n";}
    // override operator "new" to allocate with malloc
    static void* operator new(size_t size)
    {
        std::cout << "Custom new!\n";
        return malloc(size);
    }
    // Override operator "delete" to free with free
    static void operator delete(void* ptr)
    {
        std::cout << "Custom delete!\n";
        free(ptr);
    }
};

int main()
{
    // both customized memory allocator and the constructor and the deconstructor will be called
    Test* myTest = new Test();
    delete myTest;
    return 0;
}