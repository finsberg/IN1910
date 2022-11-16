# Exercises week 6 - challenge solutions

```c++
// is_prime_naive.cpp

#include <cassert>
#include <iostream>
#include <vector>

bool is_prime(int n)
{
    // 1, 2 and all negative numbers are not prime.
    if (n < 3)
        return false;

    for (int i = 2; i < n; i++)
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
```

```c++
// is_prime_candidate_divisors.cpp
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
```

```c++
// is_prime_odd.cpp
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

bool is_prime(int n)
{
    // 1 and all negative numbers are not prime.
    if (n < 2)
        return false;
    // All odd numbers
    else if (n % 2 == 0)
        return false;

    int sqrt_n = ceil(sqrt(n));
    for (int i = 3; i <= sqrt_n; i += 2)
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
```

```c++
// is_prime_squared_n.cpp
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
```

```bash
# Makefile
source_files = $(wildcard *.cpp)
executables = $(subst .cpp,.x,$(source_files))

CXXFLAGS = -std=c++11

all: $(executables)
%.x: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(executables)
```
