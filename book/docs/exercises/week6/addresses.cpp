#include <iostream>

using namespace std;

void int_address(int *data, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Address of integer value number " << i << ":" << &data[i] << endl;
    }
}

void double_address(double *data, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Address of double value number " << i << ":" << &data[i] << endl;
    }
}

void pointer_arithmetic(int *numbers, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Value: " << *(numbers + i) << ". Incremented address " << (numbers + i)
             << ". Address of element: " << &numbers[i] << endl;
    }
}

int main()
{
    int a;
    float b;
    double c;

    cout << &a << " " << &b << " " << &c << endl;

    int const n = 10;
    int int_data[n];
    double double_data[n];

    int_address(int_data, n);
    double_address(double_data, n);

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    pointer_arithmetic(numbers, 10);

    return 0;
}
