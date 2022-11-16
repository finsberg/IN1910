#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

bool is_prime(int n)
{
    // 1, 2 and all negative numbers are not prime.
    if (n < 3)
        return false;
    else if (n == 3)
        return true;
    else if (((n - 1) % 6 == 0) || ((n + 1) % 6 == 0))
    {
        int sqrt_n = ceil(sqrt(n));
        for (int i = 5; i <= sqrt_n; i += 2)
        {
            if (n % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    return false;
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
