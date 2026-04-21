#include "vect2.hpp"

#include <iostream>

int main()
{
    vect2 v1(3, 4);
    vect2 v2(1, 2);

    vect2 v3 = v1 + v2;
    vect2 v4 = v1 - v2;
    vect2 v5 = v1 * 2;

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v1 + v2 = " << v3 << std::endl;
    std::cout << "v1 - v2 = " << v4 << std::endl;
    std::cout << "v1 * 2 = " << v5 << std::endl;

    return 0;
}
