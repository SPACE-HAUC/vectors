/**
 * @file test.cpp
 * @author Mit Bailey (mitbailey99@gmail.com)
 * @brief 
 * @version See Git tags for version information.
 * @date 2021.11.02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "vectors.hpp"

int main()
{
    vec::Vector3<float> a = vec::Vector3<float>(1, 2, 3);
    vec::Vector3<int> b = vec::Vector3<int>(1, 2, 3);
    vec::Vector3<int> c = 4;
    vec::Vector3<int> d(1, 2, 4);
    // vec::Vector3<vec::Vector3<int>> f(b, c, d);
    // std::cout << f << std::endl;
    vec::Vector3<double> e;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << (a == b) << std::endl;
    std::cout << a << std::endl;
    std::cout << (a & a) << std::endl;
    std::cout << (a ^ a) << std::endl;
    a = a / 20;
    a = 20 / a;
    std::cout << a << std::endl;
    std::cout << e << std::endl;
    return 0;
}