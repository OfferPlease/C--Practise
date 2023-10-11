#include <memory>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    // safest way of allocate and use dynamic memory
    shared_ptr<int> p3 = make_shared<int>(42);
    shared_ptr<string> p4 = make_shared<string>(10, '9');
    shared_ptr<int> p5 = make_shared<int>(); // the memory p5 pointing to is made as 0
    // auto!
    auto p6 = make_shared<vector<string>>();
    return 0;
}