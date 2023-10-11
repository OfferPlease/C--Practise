// Learning Operator Overloading
#include <iostream>
struct Vector{
    float x, y;
    Vector(float x, float y): x(x), y(y){}
    // tip: the use of this oprator:
    // this: a const pointer to the current object, a pointer!
    Vector add(Vector other)
    {
        return *this + other;
    }
    // overload operator to define behaviour for addition and multiplation
    Vector operator+ (const Vector& other) const
    {
        Vector res(this->x + other.x, this->y + other.y);
        return res;
    }

    Vector operator* (const Vector& other) const
    {
        Vector res(x*other.x, y*other.y);
        return res;
    }

    bool operator==(const Vector& other) const
    {
        return x == other.x && y == other.y;
    }

    void print()
    {
        std::cout<<x<<","<<y<<std::endl;
    }
};


int main()
{
    Vector v1(1.0f, 2.0f);
    Vector v2(2.0f, 4.0f);
    Vector res = v1 + v2;
    res.print();
    Vector scale(2.0f, 2.0f);
    std::cout << (scale*v1 == v2);
    return 0;
}