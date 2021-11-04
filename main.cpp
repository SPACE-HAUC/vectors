/**
 * @file main.cpp
 * @author Mit Bailey (mitbailey99@gmail.com)
 * @brief 
 * @version See Git tags for version information.
 * @date 2021.11.03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

class Test
{
public:
    Test()
    {
        for (int i = 0; i < 9; i++)
            a[i] = 0;
    }

    Test(int x, int y)
    {
        a[0] = x;
        a[1] = y;
    }

    int& operator()(int x, int y)
    {
        return at(x, y);
    }

    int& at(int x, int y)
    {
        int idx = x * 3 + y;
        return a[idx];
    }

    int a[9];
};

class Test2
{
    public:
    int a;
    bool transposed;

    Test2(int x)
    {
        a = x;
        transposed = false;
    }

    Test2 transpose() const
    {
        Test2 b(this->a);
        b.transposed = !transposed;
        return b;
    }

    void operator=(Test2 &in)
    {
        a = in.a;
        transposed = in.transposed;
    }

    int operator()() const
    {
        return a;
    }

    int test()
    {
        return (*this)();
    }

    friend Test2 operator/(int x, Test2 y)
    {
        
    }
};

#include <stdio.h>

int main ()
{
    Test B(10, 20);
    B(0, 2) = 1901;
    for (int i = 0; i < 9; i++)
        printf("%d ", B.a[i]);
    printf("\n");
    Test2 X(10);
    Test2 Y(20);
    printf("%d %d\n", X.test(), X.transposed);
}