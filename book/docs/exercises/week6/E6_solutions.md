# Week 6 solutions

## Introduction to C++

### Exercise 1) Hello World
```cpp
#include <iostream>

int main() {
  std::cout << "Hello, world!" << std::endl;
  return 0;
}
```

### Exercise 2) Reduction by halves
```cpp
#include <iostream>

void reduction_by_halves(int n) {
    for (int i = n; i > 0; i /= 2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n = 100;
    reduction_by_halves(1000);

    return 0;
}
```

### Exercise 3) Stirling's Approximation
```cpp
#include <iostream>
#include <cmath>
#include <vector>

double stirling(int x) {
    return x*std::log(x) - x;
}

int main() {
    std::vector<int> xs {2, 5, 10, 50, 100, 1000};

    for (int i : xs) {
        std::cout
            << "Approx: "
            << stirling(i)
            << ", Exact: "
            << std::lgamma(i+1)
            << std::endl;
    }

    return 0;
}
```

### Exercise 4) Triangle Numbers
```cpp
#include <iostream>
#include <vector>
#include <cassert>

int triangle(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }

    return sum;
}

void test_triangle() {
    std::vector<int> expected {0, 1, 3, 6, 10, 15};

    for (int i = 0; i < expected.size(); i++) {
        std::cout << triangle(i) << ", " << expected[i] << std::endl;
        assert(triangle(i) == expected[i]);
    }

    int triangle_76 = 76*(76+1) / 2;
    assert(triangle(76) == triangle_76);
}

int main() {

    int n;
    std::cout << "Please enter a number: ";
    std::cin >> n;

    std::cout << "The triangle number for " << n << " is "
              << triangle(n) << "." << std::endl;

    return 0;
}
```

### Exercise 5) Linspace
```cpp
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

const double pi = M_PI;

std::vector<double> linspace(double a, double b, int n) {
    std::vector<double> vec;

    for (double i = 0; i < n; i++) {
        vec.push_back(a + i * (b - a) / (n - 1));
    }

    return vec;
}

std::vector<double> linspace(double a, double b) {
    return linspace(a, b, 50);
}

void test_linspace() {
    auto vec = linspace(1, 50);
    assert(vec[0] == 1);
    assert(vec[vec.size() - 1] == 50);
    assert(vec.size() == 50);

    vec = linspace(0, pi, 1000);
    assert(vec[0] == 0);
    assert(vec[vec.size() - 1] == pi);
    assert(vec.size() == 1000);
}

int main() {
    test_linspace();

    return 0;
}
```

### Exercise 6) Finite Differences
```cpp
#include <iostream>

void solve() {
    int N = 10001;

    double *t = new double[N];
    double *u = new double[N];

    double a = 4.3;
    double u0 = 15.7;

    double dt = 0.001;
    t[0] = 0;
    u[0] = u0;

    for (int i = 1; i < N; i++) {
        t[i] = t[i-1] + dt;
        u[i] = u[i-1] + dt*(-a * u[i-1]);
        if (i % 100 == 0) {
            //std::cout << "t=" << t[i] << " u=" << u[i] << std::endl;
            printf("t=%4.1f u=%g\n", t[i], u[i]);
        }
    }

    delete[] t;
    delete[] u;
}

int main() {
    solve();

    return 0;
}
```

## References and pointers in C++

### Exercise 1) Returning several values using *Call by reference*
```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void stats(vector<double> data, double &mean, double &median, vector<double> &data_sorted)
{
    /*Note that "data" has not been called by reference. By skipping "&" we call
    "data" by value, meaning "data" inside this function is just a copy of the
    original. This is important so that we avoid sorting the original vector.
    */
    mean = 0;
    for (int i = 0; i < data.size(); i++)
    {
        mean += data[i];
    }
    mean = mean/data.size();

    sort(data.begin(), data.end()); //Sorting copy of data
    data_sorted = data;

    if (data.size()%2 == 0)
    {
        median = (data_sorted[data.size()/2 - 1] + data_sorted[data.size()/2])/2;
    }
    else
    {
        median = data_sorted[data.size()/2];
    }
}

int main()
{
    double mean, median;
    vector<double> data = {1.2, 5.3, 7.1, -2.4, 9.2}, data_sorted;
    stats(data, mean, median, data_sorted);
    cout << "Mean: " << mean << ". Median: " << median << endl;

    cout << "Sorted vector: {";
    for (int i = 0; i < data.size(); i++)
    {
      cout << data_sorted[i] << " ";
    }
    cout << "}" << endl;

    cout << "Unsorted vector: {";
    for (int i = 0; i < data.size(); i++)
    {
      cout << data[i] << " ";
    }
    cout << "}" << endl;

    return 0;
}
```

### Exercise 2) Pointers and pointer arithmetic
```cpp
#include <iostream>

using namespace std;

void int_address(int* data, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout <<"Address of integer value number " << i <<":" << &data[i] << endl;
    }
}

void double_address(double* data, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout <<"Address of double value number " << i <<":" << &data[i] << endl;
    }
}

void pointer_arithmetic(int* numbers, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Value: " << *(numbers + i) << ". Incremented address "
             << (numbers + i) << ". Address of element: " << &numbers[i]
             << endl;
    }
}

int main()
{
  int a; float b; double c;

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
```
