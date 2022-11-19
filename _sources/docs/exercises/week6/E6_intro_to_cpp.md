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

# Week 6
## An Introduction to C++

This week, we start looking at a new programming language, C++. In these exercises, you will get a chance to solve some exercises using this new language. As the goal is to get you familiarized with the C++ syntax, and how to compile and run the programs, the exercises themselves are not that technical.


If you haven't set up your computer for C++ programming yet, have a look at [our setup guide](../../setup/cpp_compiler.md)


### Exercise 1) Hello World

**a)** Create a file `hello_world.cpp` and write code that writes out a small message to the user when run.

**b)** Compile your file through the terminal. This is explained in detail in this weeks [lecture notes](../../lectures/cpp/intro_to_cpp.md) but the basic command is
```
c++ <input_file> -o <output name>
```
**c)** Execute your compiled program and verify that it works.


### Exercise 2) Reduction by halves

**a)** Define an integer $n=100$

**b)** Define a while loop that first prints out $n$, then divides it by 2, until it reaches 0.

**c)** Compile and run your program. It should print out
$$100, 50, 25, ..., 1.$$

**d)** Change your program so that the while loop is inside a function, you should use the following signature:
```C++
void reduction_by_halves(int n)
{
    ...
}
```
Note that we use `void`, as the function should not return anything.

**e)** Call you function from the main function with $n=1000$.


### Exercise 3) Stirling's Approximation

Stirling's approximation is a much used approximation for the logarithm of factorials. It is given by

$$\ln x! \approx x\ln x - x.$$

**a)** Define a function `stirling` that takes in the integer $x$, and returns the approximation as a double.

**b)** Define the values
$$x = 2, 5, 10, 50, 100, 1000,$$

as a vector. Use a for loop to iterate through these values and compute Stirling's approximation for each one.

**c)** For each value, compare the approximation to the correct value of $\ln x!$. You can compute the correct value by using `std::lgamma` by including the `<cmath>` header, note that $\ln x!$ is given by `lgamma(x+1)`.



### Exercise 4) Triangle Numbers

The $n$'th triangle number is the sum of the integers from 1 up to and including $n$.

**a)** Define a function `triangle` that takes in an integer $n$, and returns the $n$'th triangle number. The function should use a loop and calculate the sum explicitly

**b)** Call the function from the main loop, and verify that it gives the right answer for the first 5 triangle numbers.

**c)** Check that the function gives the correct value for $n=761$. To see if the value is correct, you can use the analytical expression for the $n$'th triangle number, which is
$$n(n+1)/2.$$

**d)** Change your main function so that it asks the user for a number when executed. To ask for input, you can use `cin` as follows:
```
int n;

cout << "Please enter a number: ";
cin >> n;
```

### Exercise 5) Linspace

You might be familiar with the Python function `np.linspace(a, b)`, which gives a numpy array of 50 linearly spaced points between $a$ and $b$ inclusive.

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

### Exercise 6) Finite Differences

In this exercise, you will numerically solve the exponential decay ODE model:

$$\frac{{\rm d}u}{{\rm d}t} = -au,$$
using C++.

**a)** Allocate two arrays, $u$ and $t$, each with 10001 elements.

**b)** Let $u_0 = 15.7$ and $a=4.3$.

**c)** Compute $t_i$ and $u_i$ for $i = 1, \ldots, 10001$, with a time step $\Delta t = 0.001$.

Hint: Use a for-loop, and a forward euler scheme, which you can derive from the expression:

$$\frac{u_{i+1} - u_i}{\Delta t} = -au_i.$$


### More exercises

If you have finished all the exercises for this week, but want to do more. Take a look at this week's [challenge](C1_primes_by_trial_division.md).
