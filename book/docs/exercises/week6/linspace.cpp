#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

const double pi = M_PI;

std::vector<double> linspace(double a, double b, int n)
{
    std::vector<double> vec;

    for (double i = 0; i < n; i++)
    {
        vec.push_back(a + i * (b - a) / (n - 1));
    }

    return vec;
}

std::vector<double> linspace(double a, double b)
{
    return linspace(a, b, 50);
}

void test_linspace()
{
    auto vec = linspace(1, 50);
    assert(vec[0] == 1);
    assert(vec[vec.size() - 1] == 50);
    assert(vec.size() == 50);

    vec = linspace(0, pi, 1000);
    assert(vec[0] == 0);
    assert(vec[vec.size() - 1] == pi);
    assert(vec.size() == 1000);
}

int main()
{
    test_linspace();

    return 0;
}
