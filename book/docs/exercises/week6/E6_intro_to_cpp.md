---
jupyter:
  jupytext:
    text_representation:
      extension: .md
      format_name: markdown
      format_version: '1.3'
      jupytext_version: 1.10.3
  kernelspec:
    display_name: Python 3
    language: python
    name: python3
---

# An Introduction to C++

This week, we start looking at a new programming language, C++. In these exercises, you will get a chance to solve some exercises using this new language. As the goal is to get you familiarized with the C++ syntax, and how to compile and run the programs, the exercises themselves are not that technical.

If you have not set up your computer for C++ programming yet, have a look at the [Setup guide](../../setup/cpp_compiler.md).
To refresh the basic concepts about C++, we refer to the notes at [An introduction to C++](../../lectures/cpp/intro_to_cpp.md).


```{exercise-start} Hello World
:label: cpp_hello_world
```


**a)** Create a file `hello_world.cpp` and write code that writes out a small message to the user when run.

**b)** Compile your file through the terminal. This is explained in detail in the [introduction to C++](../../lectures/cpp/intro_to_cpp.md) material.

**c)** Execute your compiled program and verify that it works.

```{exercise-end}
```

```{solution-start} cpp_hello_world
:class: dropdown
```
The structure of the program can be seen below.

```cpp
#include <iostream>

int main() {
  std::cout << "Hello, world!" << std::endl;
  return 0;
}
```

The basic command to link and create the executable is (although the compiler call command might vary)
```
c++ <input_file> -o <output name>
```
And the executable can be run in the terminal via
```
./<output name>
```

```{solution-end}
```

```{exercise-start} Reduction by halves
:label: reduction_halves
```

**a)** Define an integer $n=100$

**b)** Define a while loop that first prints out $n$, then divides it by 2, until it reaches 0.

**c)** Compile and run your program. It should print out $100, 50, 25, ..., 1.$

**d)** Change your program so that the while loop is inside a function, you should use the following signature:
```C++
void reduction_by_halves(int n)
{
    ...
}
```
Note that we use `void`, as the function should not return anything.

**e)** Call your function from the main function with $n=1000$.

```{exercise-end}
```


```{solution-start} reduction_halves
:class: dropdown
```

By defining `int n = 100;` we initialize an integer variable n with a value of 100.

Afterward, we construct a while loop that will execute as long as n is greater than 0.
In each iteration of the loop, it prints the value of n and then divides n by 2.
The `std::cout << std::endl;` statement is used to print a newline character at the end of the output, and there different ways of doing it.


```cpp
while (n > 0) {
    std::cout << n << " ";
    n /= 2;
}
std::cout << std::endl;

```

Remember we need to structure the main function and a return value before compiling, as in

```cpp
#include <iostream>

int main() {
    int n = 100;

    while (n > 0) {
        std::cout << n << " ";
        n /= 2;
    }
    std::cout << std::endl;

    return 0;
}
```
If it is not clear how to compile and run the code, go back to the "Hello, World!" exercise.

Finally, we structure the program in the given signature

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

```{solution-end}
```


```{exercise-start} Stirling's Approximation
:label: stirling_approx
```


Stirling's approximation is a much-used approximation for the logarithm of factorials. It is given by

$$\ln x! \approx x\ln x - x.$$

**a)** Define a function `stirling` that takes in the integer $x$, and returns the approximation as a double.

**b)** Define the values $x = (2, 5, 10, 50, 100, 1000)$ as a vector. Use a for loop to iterate through these values and compute Stirling's approximation for each one.

**c)** For each value, compare the approximation to the correct value of $\ln x!$. You can compute the correct value by using `std::lgamma` by including the `<cmath>` header, note that $\ln x!$ is given by `lgamma(x+1)`.

```{exercise-end}
```

```{solution-start} stirling_approx
:class: dropdown
```
First, we define the function `stirling` that takes in an integer $x$ and returns the approximation given by $x\ln x - x$. The function is defined as follows

```cpp
double stirling(int x) {
    return x * std::log(x) - x;
}
```

We use std::log from the `<cmath>` header to compute the natural logarithm of $x$.

Next, we define the values of $x$ we want to use for the approximation, and store them in a vector

```cpp
std::vector<int> xs {2, 5, 10, 50, 100, 1000};
```

Finally, we iterate through each value of $x$ in the vector using a range-based for loop, and print out the approximation and the exact value of $\ln x!$ computed using `std::lgamma`, giving the complete code below

```cpp
#include <iostream>
#include <cmath>
#include <vector>

double stirling(int x) {
    return x * std::log(x) - x;
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

```{solution-end}
```


```{exercise-start} Triangle Numbers
:label: triangle_numbers
```

The $n$'th triangle number is the sum of the integers from 1 up to and including $n$.

**a)** Define a function `triangle` that takes in an integer $n$, and returns the $n$'th triangle number. The function should use a loop and calculate the sum explicitly

**b)** Call the function from the main loop, and verify that it gives the right answer for the first 5 triangle numbers.

**c)** Check that the function gives the correct value for $n=761$. To see if the value is correct, you can use the analytical expression for the $n$'th triangle number, which is $n(n+1)/2.$

**d)** Change your main function so that it asks the user for a number when executed. To ask for input, you can use `cin` as follows:
```
int n;

cout << "Please enter a number: ";
cin >> n;
```

```{exercise-end}
```


```{solution-start} triangle_numbers
:class: dropdown
```
Let's start by creating a function triangle that can calculate the $n$'th triangle number. The function should take an integer input and return the triangle number as an integer.

```cpp
int triangle(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }

    return sum;
}
```
The function triangle takes an integer n as an input and calculates the sum of integers from 1 up to and including n. The sum is stored in the variable sum, which is returned at the end of the function.

To verify that our triangle function is correct, we can write a function `test_triangle` that tests the function on some known inputs and expected outputs.
The function uses an assert statement to check if the function output matches the expected output.

```cpp
void test_triangle() {
    std::vector<int> expected {0, 1, 3, 6, 10, 15};

    for (int i = 0; i < expected.size(); i++) {
        assert(triangle(i) == expected[i]);
    }

    int triangle_76 = 76*(76+1) / 2;
    assert(triangle(76) == triangle_76);
}
```
Here, we create a vector with the expected triangle numbers for the first 5 integers. We then loop over the vector and compare the output of `triangle` with the expected output using assert.
Finally, we check if the function output matches the expected triangle number for n=761 using the analytical expression for the $n$'th triangle number.

We can now modify our main function to ask the user for an input and call the triangle function to calculate the triangle number. Here, we use `std::cin` to get user input and store it in the variable n.
We then call the triangle function to calculate the triangle number for the input n and print the result to the console.

Putting it all together, we get the following solution:

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

```{solution-end}
```



```{exercise-start} Linspace
:label: linspace
```


You might be familiar with the Python function `np.linspace(a, b)`, which gives a NumPy array of 50 linearly spaced points between $a$ and $b$ inclusive.

**a)** Define a function with the signature
```C++
vector<double> linspace(double a, double b)
```
It should return a vector with 50 linearily spaced points, just like `np.linspace`.

**b)** The function `np.linspace` can also take a third argument if we want a different number of points than 50, so `np.linspace(0, 2*pi, 1000)` would give 1000 points for example. Overload your `linspace` function by implementing the signature:
```C++
vector<double> linspace(double a, double b, int n)
```

**c)** Verify that you can call on linspace with either 2 or 3 arguments. And that the results are as expected in either case.

```{exercise-end}
```

```{solution-start} linspace
:class: dropdown
```

We start by implementing a C++ version of np.linspace(a, b), which creates a vector of 50 equally spaced points from a to b inclusive.

The function declaration should be

```cpp
std::vector<double> linspace(double a, double b);
```

To implement this function, we first create an empty vector to store the points. We then loop over the indices `i` from 0 to 49 and calculate the corresponding point using the formula for equally spaced points

```cpp
std::vector<double> vec;

for (int i = 0; i < 50; i++) {
    vec.push_back(a + i * (b - a) / 49);
}
```

Note that we use 49 instead of 50 in the denominator since we start counting at 0.

The goal of the second part is to add an overloaded version of linspace that takes a third argument n and returns a vector of n equally spaced points from a to b.
The function declaration should now be as asked, and to implement it, we use the same loop as before but with n instead of 50

```cpp
std::vector<double> linspace(double a, double b, int n) {
    std::vector<double> vec;

    for (int i = 0; i < n; i++) {
        vec.push_back(a + i * (b - a) / (n - 1));
    }

    return vec;
}
```

Again, note that we use n - 1 in the denominator since we start counting at 0.
Finally, we write a test function test_linspace which calls both versions of linspace and checks that the results are correct.
The full implementation can be seen below

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

```{solution-end}
```



```{exercise-start} Finite Differences
:label: finite_diff
```

In this exercise, you will numerically solve the exponential decay ODE model:

$$\frac{{\rm d}u}{{\rm d}t} = -au,$$
using C++.

**a)** Allocate two arrays, $u$ and $t$, each with 10001 elements.

**b)** Let $u_0 = 15.7$ and $a=4.3$.

**c)** Compute $t_i$ and $u_i$ for $i = 1, \ldots, 10001$, with a time step $\Delta t = 0.001$.

Hint: Use a for-loop, and a forward Euler scheme, which you can derive from the expression:

$$\frac{u_{i+1} - u_i}{\Delta t} = -au_i.$$
```{exercise-end}
```

```{solution-start} finite_diff
:class: dropdown
```

We start by initializing some variables: $N$ to 10001, $u_0$ to 15.7, $a$ to 4.3, and $\Delta t$ to 0.001.
We also create two arrays $t$ and $u$ to store the time points and the computed values of $u$, respectively.
All this can be done inside the `solve()` function, as follows

```cpp
void solve() {
    int N = 10001;

    double *t = new double[N];
    double *u = new double[N];

    double a = 4.3;
    double u0 = 15.7;

    double dt = 0.001;
    t[0] = 0;
    u[0] = u0;

    // ...
}
```

Notice here the two pointers to double type, t and u, are being created and assigned to the address of the first element of two dynamically allocated arrays of size N.
The keyword `new` is used to dynamically allocate memory for these arrays at runtime. In case the concept of dynamically allocated variables has been forgotten, we refer to  [Dynamic memory allocation](../../lectures/cpp/dynamic_allocation.md). In short, dynamically allocating memory means that the program requests the OS to reserve a block of memory on the heap at runtime, rather than at compile-time. In our case, the memory reserved is enough to store N doubles.

The next step is to loop from $i=1$ to $i=N-1$ computing at each time the value of $u_{i}$ using the forward Euler scheme. Note we print the value of $t_i$ and $u_i$ at every 100th iteration

```cpp
    // ...
    for (int i = 1; i < N; i++) {
        t[i] = t[i-1] + dt;
        u[i] = u[i-1] + dt*(-a * u[i-1]);
        if (i % 100 == 0) {
            printf("t=%4.1f u=%g\n", t[i], u[i]);
        }
    }
    // ...
```

In this case, the format string is `t=%4.1f u=%g\n`. The `%4`.1f specifier indicates that a floating-point value will be printed with at least 4 characters in total and 1 digit after the decimal point.
The %g specifier indicates that a floating-point value will be printed using the most compact representation possible (either fixed-point or scientific notation).

After the loop, it is important to use `delete[]` to deallocate the dynamically allocated memory to avoid memory leaks and shortage of available memory.
The complete code is available below.

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

```{solution-end}
```

## Additional exercises - Challenges

If you have finished all the exercises for this week, but want to do more, the following exercises are an additional challenge.

```{exercise-start} Challenge 1 - Checking Primality by Trial Division
:label: challenge
```

Integers have many different mathematical properties that could be of interest, in this exercise we will look at [*prime numbers*](https://en.wikipedia.org/wiki/Prime_number). Wikipedia's definition of a prime number is as follows:
> A prime number (or a prime) is a natural number greater than 1 that has no positive divisors other than 1 and itself. A natural number greater than 1 that is not a prime number is called a composite number. As an example, 5 is prime because 1 and 5 are its only positive integer factors, whereas 6 is composite because it has the divisors 2 and 3 (in addition to 1 and 6).

The goal of this exercise is to write a function `is_prime(n)` that takes an integer and checks if it is prime. We will start off with the *naive solution* and then make it more effective.

**Checking divisibility**

We first have to check if an integer is divisible by another integer. For any two integers, $a$ and $b$, we can write $a/b$ as

$$\frac{a}{b} = N + \frac{r}{b},$$

where $N$ is an integer denoting how many times $a$ evenly divides into $b$, and $r$ is a non-negative integer smaller than $b$, so that $r/b$ is a decimal number in the interval $[0, 1)$.

For example, if $a$ is 7 and $b$ is 3 we get

$$\frac{7}{3} = 2 + \frac{1}{3}.$$

So $N=3$ and $r=1$. We call $r$ the *remainder* of the division. We say that $a$ is *divisible* by $b$ if there is no remainder, i.e., $r = 0$.

We can find $N$ by integer division, and $r$ by using the modulo operator.


**Exercise (a)**

The *naive solution* to checking whether a number is a prime is to follow the definition of prime numbers and simply check every integer from 2 up to (but not including) the number itself.

Define a function `is_prime` that checks if a positive integer $n$ is prime using the naive solution. Use it to find the first ten prime numbers.

Hints:
1. You can handle the edge cases of n equal to 1, 2 and 3 by simply testing
2. Be careful not to test divisibility by 1 or $n$ itself, as all numbers are divisible by 1 and themselves
3. If you find a number that evenly divides $n$, you can immediately return `false` as the number is not a prime, no need to check all the numbers in this case.


*Optimization*

If implemented correctly, `is_prime` can now check the primality of any positive integer $n$, but as we have to loop over *all* numbers from 1 to n (exclusive), it will be very slow for large $n$. If we for example want to find all primes below 1 billion, we would have to loop over *a lot* of numbers. In the following exercises, you will improve your algorithm to make it a bit more efficient.

**Exercise (b)**

Our naive solution might be very basic and slow, but we are fairly sure it works precisely *because* of its simplicity, and we tested it by finding the first 10 primes. As we now go through and optimize our code, we must make sure we do not break our functionality. Write a test block or function that you can use after each change you make to ensure that while our function is getting faster, we are not changing its functionality.


**Exercise (c)**

The first thing we can ask is if we really need to check all numbers in the range $[2, n)$. Let us look at an example, 100 is a composite number and can be written out as the following products:
1. $2×50$
2. $4×25$
3. $5×20$
4. $10×10$
5. $20×5$
6. $25×4$
7. $50×2$

Note that we find 7 ways to create 100 by multiplying 2 integers. However, the final three versions are just the first three ones flipped around. This will be the case for any number. In this case, the turning point is $\sqrt{N}$ because $100$ is a square number, but from this, we see that for any number $n$ that can be written as a product of two divisors, at least one of them will be smaller or equal to $\sqrt{n}$. Thus we can reduce our range of numbers to check from $[2, \sqrt{n}]$. For large numbers, such as $10^6$, this is a huge reduction.

Update your `is_prime` function so that you only check the range [2, √n], and verify that your function still handles your test block/function from exercise (c).


**Exercise (d)**

We just narrowed down the range of numbers we check considerably, but do we have to check *every single* number in the range $[2, \sqrt{n}]$? You have probably noticed that all primes, except for 2, are odd numbers (as opposed to being even). Why is this? It happens because all even numbers are evenly divisible by 2, and so are not prime. This means we only have to check odd numbers. But even better, this also means we only have to check *odd-valued divisors* to check primality (why? Try to convince yourself why this is, or discuss it with a classmate).

Update your function so that you check if $n$ is even *before* you start looping over your divisor candidates. And then update your loop so that it skips all even numbers in the range $[3, \sqrt{n}]$. And then verify that your function still handles your test block/function from exercise (c).


**Exercise (e)**

By checking if a number was even, we could effectively skip checking *half* of the possible divisors, which is a very nice reduction. We can go one step further by also considering the number 3. No numbers that are divisible by $3$ can be prime (other than 3 itself).

To implement this, note that any integer $n$ can be written on exactly one of the six following forms:
* $n = 6k - 2$
* $n = 6k - 1$
* $n = 6k$
* $n = 6k + 1$
* $n = 6k + 2$
* $n = 6k + 3$

where $k$ is an integer. As $n$ grows, so does $k$. Now, note that the first, third and fifth possibilities are instantly discardable because they are even. This leaves us with the fact that all primes can be written as:
* $n = 6k - 1$
* $n = 6k + 1$
* $n = 6k + 3$

Of these remaining three, note that the last option is divisible by 3 for all $k$, so we can disregard them as well. This means all primes can be written as the two possibilities:
* $n = 6k - 1$
* $n = 6k + 1$

This also means all possible candidate divisors are on one of these two forms (as all divisors are prime).

Update your `is_prime` function so that when looping over candidate divisors, you only check the candidates on the form $6k\pm1$. Run your test block/function to verify your code.


**Project Euler Prime Number Problems**

You have now implemented a fairly optimized function for checking if a number is prime by trial division. Let us use your work to solve some [Project Euler problems](https://projecteuler.net/).

**Exercise (f)**

(This is the [7th problem of Project Euler](https://projecteuler.net/problem=7).)

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

**What is the 10001st prime number?**

**Exercise (g)**

(This is the [10th problem of Project Euler](https://projecteuler.net/problem=10).)

The sum of all primes below 10 is 2 + 3 + 5 + 7 = 17.

*Find the sum of all the primes below two million.*


```{exercise-end}
```

```{solution-start} challenge
:class: dropdown
```

Here we display the codes related to the previous explanation of the challenge. Notice that the different implementations can be organized in different `.cpp` files. Additionally, in the end, we included an example of a `Makefile`. As explained in [Header files, Debugging, Code style, Testing, Documentation and Makefiles](../../lectures/cpp/cpptools.md)), A Makefile is a script used to automate the build process of a program.
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

This final `Makefile` suggestion is added to facilitate building the multiple executables. It defines some variables and targets that specify how to build the source code into executables.

- **source_files:** This variable uses the wildcard function to find all the `.cpp` files in the current directory and store them in a list.
executables: This variable uses the `subst` function to replace the `.cpp` extension of each file in source_files with `.x` and store the resulting list of executable file names.

- **CXXFLAGS:** This variable is used to define the compiler flags, specifically the `-std=c++11` flag, which specifies the version of the C++ standard that the code adheres to.

- **all:** This target specifies that all of the executables should be built. It depends on the `$(executables)` variable.

- **%.x: %.cpp:** This target specifies how each .cpp file should be compiled into an executable. It uses pattern matching to match any `.cpp` file and generates a corresponding `.x` file. The `$@` variable is the name of the target (i.e., the name of the `.x` file), and the `$<` variable is the name of the first prerequisite (i.e., the `.cpp` file).

- **clean:** This target is used to remove all of the generated executables. It uses the `$(RM)` variable, which is a built-in variable that specifies the command to remove files. In this case, it is used to remove all of the files in `$(executables)`.
To use this makefile, simply navigate to the directory containing the source code files and the makefile and run the make command. This will build all of the executables specified in `$(executables)`. Running `make clean` will remove all of the generated executables. This makefile is useful because it automates the build process, allowing the user to easily compile all of the source code files with a single command. It also provides a convenient way to clean up the generated files.

```{solution-end}
```
