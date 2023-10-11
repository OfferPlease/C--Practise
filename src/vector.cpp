#include <iostream>

/* Copy bit: copy the pit form position pos to number src to the position pos in number dst
   position is 0-based and starts form the right
*/
int copy_bit(int src, int dst, int pos)
{
    // 让dist的pos位为0，其余位不变， 需要将tmp取反
    dst =  dst & (~(1<<pos));
    dst += src & (1<<pos);
    return dst;
}

int main()
{
    // std:: cout << copy_bit(7, 12, 3) << std::endl;
    int8_t nums[3] = {2, 3, 4};
    std::cout << (nums[0] << nums[1] << nums[2]);
    return  0;
}