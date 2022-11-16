#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

bool is_prime(int n)
{
    // 1, 2 and all negative numbers are not prime.
    if (n < 3)
        return false;

    int sqrt_n = ceil(sqrt(n));
    for (int i = 2; i <= sqrt_n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

void test_prime()
{
    std::vector<int> vec{31, 29, 23, 19, 17, 13, 11, 7, 5, 3};
    int stop = vec[0];
    for (int i = 1; i <= stop; i++)
    {
        if (is_prime(i))
        {
            assert(i == vec.back());
            vec.pop_back();
        }
    }
    assert(vec.empty());
}

int main()
{
    test_prime();

    return 0;
}
