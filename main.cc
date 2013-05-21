#include <iostream>
#include <range.hh>

int main()
{
    using namespace generator;

    for (auto i : range(10))
        std::cout << i << std::endl;
    for (auto i : range(42, 0, -1))
        std::cout << i << std::endl;

    return 0;
}
