---
jupytext:
  formats: md:myst
  text_representation:
    extension: .md
    format_name: myst
kernelspec:
  display_name: Python 3
  language: python
  name: python3
---

# Week 12

## Optimization and mixed programming

The goal of this weeks exercises is to implement some algorithms and to use different forms of optimization.


### Exercise 1) Benchmarking and High Level Optimization of Matrix-Vector Multiplication

One of the most common calculations in scientific computing is perhaps matrix-vector-multiplication(MVM). For a $n\times n$ matrix

$$ A= \left(\begin{matrix}a_{11}&\cdots&a_{1n}\\\vdots&\ddots&\vdots\\a_{n1}&\cdots&a_{nn}\end{matrix}\right) $$
and two $n$ long vectors

$$ \vec{x}= \left(\begin{matrix}x_{1}\\\vdots\\x_{n}\end{matrix}\right), \text{  } \vec{y}= \left(\begin{matrix}y_{1}\\\vdots\\y_{n}\end{matrix}\right), $$

the matrix-vector-multiplication $\vec{y} = A\vec{x}$ is defined as $$y_i = \sum_{j=1}^{n}a_{ij}x_j$$.


#### Exercise 1a) Implementing MVM using numpy arrays

Make a function `mvm(A,x)` in Python that implements MVM. Assume that the matrix is represented by a row-wise nested numpy array  `A`, row-wise meaning that each of element of `A` is itself an array containing a **row** of the matrix. `x` is a normal array containing the elements of $x$. The function should return an array `y`. Time the function using `time` or `timeit` and `n = 100`.

```python
import numpy as np
```

```python
def test_mvm():
    A = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    x = np.array([1, 2, 3])
    y = mvm(A, x)

    assert np.array_equal(y, np.array([14, 32, 50]))


# test_mvm()  # uncomment this line when testing your code
```

#### Exercise 1b) Complexity and benchmarking



By looking at your implementation of MVM, can you deduce the complexity of the algorithm? For example when $n$ doubles, how much do we expect the runtime to increase? Use $Big\text{ } O$ notation to give the complexity.

Make a benchmark for your function where you try running it several times for different $n$ while timing it. Try running it for $n = 100, 200, ..., 1000$ while measuring the amount of time it uses. You can use the package `time` to measure the time. You will need to make differently sized matrices and vectors filled with some values, though it is not important what exactly these values are. Finally, make a plot where you present the time used as a function of $n$. Is it in accordance with you estimate of the complexity?

```python
import time
import matplotlib.pyplot as plt
```

*Hint*: In terms of amount of time used to execute, computers are not perfect machines and are susceptible to variance and noise, especially when running very short programs(small n). To get a good benchmark, it is recommended to call the function several times for each $n$(e.i. in a for-loop) and take the average.


#### Exercise 1c) High level optimization

From this point, there is a huge number of ways you can start optimizing your algorithm. However, we are only going to explore high level optimization in this exercise. High level optimization means doing huge changes to the algorithm, making it more tailored to the specific problem we want to solve. To do be able to move from a general algorithm to a more specialized one, we must first establish some assumptions about the problem we are going to solve.

We are going to assume that the matrix is a *sparse matrix*, meaning most of its elements are zero. More specifically, it is tridiagonal:

$$\begin{pmatrix}
b_{1} & c_{1} & 0 & \cdots & 0 \\
a_{1} & b_{2} & c_{2} & \ddots & \vdots\\
0 & a_{2} & \ddots & \ddots & 0\\
\vdots & \ddots & \ddots & b_{n-1} & c_{n-1}\\
0 & \cdots & 0 & a_{n-1} & b_{n}
\end{pmatrix}$$

To be precise, this is a matrix with non-zero values on the main diagonal, the diagonal above it, and below it. Elsewhere it is zero.

Create a new function `mvm_tridiagonal` that implements MVM for a tridiagonal matrix `A`. Try to visualize the flow of the original algorithm, and rewrite it such that all the unnecessary multiplications with zeros is skipped.

```python
```

```python
def test_mvm_tridiagonal():
    A = np.array(
        [
            [1, 2, 3, 4, 5],
            [4, 5, 6, 7, 8],
            [10, 9, 8, 7, 6],
            [1, 1, 1, 1, 1],
            [2, 2, 2, 2, 2],
        ]
    )
    x = np.array([1, 2, 3, 4, 5])
    y = mvm_tridiagonal(A, x)
    assert np.array_equal(y, np.array([5, 32, 70, 12, 18]))


# test_mvm_tridiagonal()  # uncomment this line when testing your code
```

#### Exercise 1d) Benchmarking tailored algorithm

Deduce what the complexity of the new algorithm is, again using $Big\text{ }O$ notation. Also make a similar benchmark for the new algorithm. You might want to use bigger matrices and more repetitions for this benchmark since the algorithm is hopefully much faster. How much is the improvement?

```python
```

#### Exercise 1e) Optimizing with respect to memory

Tailoring the algorithm to avoid all the unnecessary multiplications with zero should have greatly increased the speed, though we still have a potential problem with the implementation. The zeros, which account for the majority of elements, are still store in the matrix and therefore also in memory. This is potentially a huge problem. Assuming each element is stored with double precision(8 bytes), a $n \times n$ matrix where $n=10000$ requires $10000 \cdot 10000 \cdot 8B \approx 0.8GB$ of memory. For $n = 100000$, we are looking at $80GB$, more than virtually any personal computer.

Since the zeros are irrelevant for our computation, we might as well get rid of them. Rewrite `mvm_tridiagonal` so that instead of passing a matrix, you pass the three vectors $\vec{a} = (a_1, a_2, \cdots, a_{n-1})$, $\vec{b} = (b_1, b_2, \cdots, b_{n})$ and $\vec{c} = (c_1, c_2, \cdots, c_{n-1})$ that define the tridiagonal matrix. Try running it for $n = 100000$. What is the total memory required when the matrix is represented only by the three diagonals?

```python
```

```python
def test_mvm_tridiagonal():
    a = np.array([1, 2, 1, -4])
    b = np.array([1, -2, 3, 6, 6])
    c = np.array([3, 2, 2, 1])
    x = np.array([1, 2, 3, 4, 5])
    y = mvm_tridiagonal(a, b, c, x)
    assert np.array_equal(y, np.array([7, 3, 21, 32, 14]))


# test_mvm_tridiagonal()  # uncomment this line when testing your code
```

A common use for tridiagonal matrices is for calculation the second derivative of a function numerically. By applying Forward Euler and Backward Euler together, one can derive the approximation

$$
u''(x) \approx \frac{u(x+\Delta x) - 2u(x) + u(x-\Delta x)}{\Delta x ^2} = \frac{u[i+1] - 2u[i] + u[i-1]}{\Delta x ^2}
$$

By staring at the last expression, using index notation, one might see that it can be represented by a matrix equation, such that



$$u''= \frac{1}{\Delta x^2}\begin{pmatrix}
-2 & 1 & 0 & \cdots & 0 \\
1 & -2 & 1 & \ddots & \vdots\\
0 & 1 & \ddots & \ddots & 0\\
\vdots & \ddots & \ddots & -2 & 1\\
0 & \cdots & 0 & 1 & -2
\end{pmatrix}
\begin{pmatrix}
 u_1 \\
 u_2\\
 u_3\\
 \vdots\\
 u_n
\end{pmatrix}$$


where the matrix is tridiagonal with $\vec{a} = \vec{c} = (1, 1, \cdots, 1)$ and $\vec{b} = (-2, -2, \cdots, -2)$.


### Exercise 2) Mixed programming with upper triangular matrix

Another common matrix form that pop up in scientific use is the upper triangular matrix, on the form:

$$\begin{pmatrix}
a_{11} & a_{12} & a_{13} & \cdots & a_{1n} \\
0 & a_{22} & a_{23} & \cdots & a_{2n}\\
\vdots & \ddots & \ddots & \ddots & \vdots\\
\vdots & \ddots & \ddots & \ddots & a_{n-1,n}\\
0 & \cdots & \cdots & 0 & a_{n,n}
\end{pmatrix}$$

Its main characteristic is that all elements on the diagonal and above it is non-zero. Elsewhere, it is zero. We might calculate the matrix-vector product(see beginning of previous exercise for definition, though it is not crucial to know) as though it were a general matrix, but there ought to exist a more efficient algorithm since roughly half of the elements are zero. A possible implementation that skips all the zero-elements in the lower triangle is as follows:

```python
import numpy as np
import time


def mvm_upper(A, x):
    n = len(x)
    y = np.zeros(n)

    for i in range(n):
        sum = 0
        for j in range(i):
            sum += A[i, j] * x[j]

        y[i] = sum
    return y


n = 100
A = np.ones((n, n))
x = np.ones(n)
```

```python tags=[]
%timeit mvm_upper(A,x)
```

`A` is our upper triangular matrix represented by a row-wise nested numpy array, row-wise meaning each element of `A` is an array itself that stores a row of the matrix. `x` is the vector that is being multiplied with `A`. The resulting vector is `y`.

#### Exercise 2a) Optimization using vectorization

Copy this implementation and optimize it using *vectorization*. The goal is to replace slow python for-loops with faster alternatives from numpy where possible. Keep in mind the structure of the upper triangular matrix. All elements below the diagonal is assumed to be zero, so we should avoid multiplications with these elements. Time the function in the same manner as the previous example. The matrix need not be upper triangular for the purpose of timing, because the value of the elements don't matter for the measured time.

```python
```

```python
def test_mvm_upper_vectorized():
    A = np.array([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]])
    x = np.array([1.0, 2.0, 3.0])
    y = mvm_upper_vectorized(A, x)

    assert np.allclose(y, np.array([14.0, 28.0, 27.0]))


# test_mvm_upper_vectorized()  # uncomment this line when testing your code
```

```python
# %timeit mvm_upper_vectorized(A,x)  # uncomment this line when testing your code
```

#### Exercise 2b) Cython

Go back to the original implementation and optimize using cython rather than vectorization. Make use of `cdef` when declaring and passing variables. These function as hints for the compiler that helps it optimize more efficiently. You may implement the cython code directly into this notebook by running the line below first. Remember to include `%%cython` and necessary imports at the top of your program. Also make sure that you have a c++ compiler on your machine, e.g. visual studios for windows.

To check if you have done a good job declaring variables to help the compiler, replace `%%cython` with `%%cython -a` to annotate your program when it runs. Parts of the code that the compiler found hard to compile will be highlighted in yellow, and may be subject to further improvement. Yellow highlighting can be caused by undeclared variables, or interaction with python objects. If you are checking the length of an array in the code for example, this is an interaction with a python object.

```python tags=[]
%load_ext Cython
```

```cython magic_args="-a"

def test_mvm_upper_cython():
    A = np.array([[1.,2.,3.],[4.,5.,6.],[7.,8.,9.]])
    x = np.array([1.,2.,3.])
    y = mvm_upper_cython(A,x)

    assert np.allclose(y, np.array([14., 28., 27.]))

# test_mvm_upper_cython()  # uncomment this line when testing your code
```

```python
# %timeit mvm_upper_cython(A,x)  # uncomment this line when testing your code
```

#### Exercise 2c) Optimizing with jit from numba

Yet again, go back to the original implementation. Make a function `mvm_upper_jit` by optimizing the code using the decorator `jit()` from `numba`. How does it compare to Cython?

```python
from numba import jit
```

```python
def test_mvm_upper_jit():
    A = np.array([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]])
    x = np.array([1.0, 2.0, 3.0])
    y = mvm_upper_cython(A, x)

    assert np.allclose(y, np.array([14.0, 28.0, 27.0]))


# test_mvm_upper_jit()
```

```python
# %timeit mvm_upper_jit(A,x)  # uncomment this line when testing your code
```
