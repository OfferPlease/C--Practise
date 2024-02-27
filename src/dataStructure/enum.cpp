#include <iostream>

enum Example : unsigned char
// 0,1,2,3... by default
// at least must be integer
{
A = 6, B, C, D
};

int main()
{
    // example must be A, B, C, or D
    // restric example to only A, B, C or D
    Example example = A;
    int tmp = A;
    if(example == A){
        std::cout << A << std::endl;
    }
    if(example == B)
    {
        std::cout << B << std::endl;
    }
    if(example == C)
    {
        std::cout << C << std::endl;
    }
    return 0;
}