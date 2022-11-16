#include <iostream>

void reduction_by_halves(int n)
{
    for (int i = n; i > 0; i /= 2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int n = 100;
    reduction_by_halves(1000);

    return 0;
}
