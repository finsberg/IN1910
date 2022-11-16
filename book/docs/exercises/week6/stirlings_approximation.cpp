#include <cmath>
#include <iostream>
#include <vector>

double stirling(int x)
{
    return x * std::log(x) - x;
}

int main()
{
    std::vector<int> xs{2, 5, 10, 50, 100, 1000};

    for (int i : xs)
    {
        std::cout << "Approx: " << stirling(i) << ", Exact: " << std::lgamma(i + 1) << std::endl;
    }

    return 0;
}
