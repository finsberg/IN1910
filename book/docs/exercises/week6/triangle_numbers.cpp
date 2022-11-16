#include <cassert>
#include <iostream>
#include <vector>

int triangle(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }

    return sum;
}

void test_triangle()
{
    std::vector<int> expected{0, 1, 3, 6, 10, 15};

    for (int i = 0; i < expected.size(); i++)
    {
        std::cout << triangle(i) << ", " << expected[i] << std::endl;
        assert(triangle(i) == expected[i]);
    }

    int triangle_76 = 76 * (76 + 1) / 2;
    assert(triangle(76) == triangle_76);
}

int main()
{

    int n;
    std::cout << "Please enter a number: ";
    std::cin >> n;

    std::cout << "The triangle number for " << n << " is " << triangle(n) << "." << std::endl;

    return 0;
}
