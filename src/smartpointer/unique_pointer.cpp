#include <memory>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class AA{
public:
    string m_name;
    AA(){cout << m_name << "consturctor AA() is called" << endl;}
    AA(const string& name):m_name(name){
        cout << "constructor AA(" << m_name << ") is called" << endl;
    }
    ~AA(){cout << "destructor ~AA(" << m_name << ") is called" << endl;}
};
unique_ptr<AA> func(){
    unique_ptr<AA> p1(new AA("Amber"));
    return p1;
}
int main()
{
    // special cases for unique pointers:
    // unique_pointer不允许拷贝也不允许赋值，但是有几种特殊情况下它可以作为临时右值
    // 1. 给匿名对象赋值
    unique_ptr<AA> p0;
    p0 = unique_ptr<AA>(new AA("Abby"));
    // 2.函数返回值，函数内的unique_pointer是局部变量，马上失效
    unique_ptr<AA> p1 = make_unique<AA>("Zoey");
    // p1 原来指向的zoey会被释放，接着接管Amber
    p1 = func();
    cout << p1->m_name << endl;
    return 0;
}