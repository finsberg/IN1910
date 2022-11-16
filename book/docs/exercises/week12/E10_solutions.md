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



### Exercise 1) Benchmarking and High Level Optimization of Matrix-Vector Multiplication

#### Exercise 1a) Implementing MVM using numpy arrays

```ipython
import numpy as np

def mvm(A,x):
    n = len(x)
    y = np.zeros(n)
    for i in range(n):
        sum = 0
        for j in range(n):
            sum += A[i,j]*x[j]

        y[i] = sum

    return y

n = 100
A = np.ones((n,n))
x = np.ones(n)

%timeit mvm(A,x)
```

#### Exercise 1b) Complexity and benchmarking

The above implementation have a double for-loop. For each particular `i`, the inner loop incrementing `j` does `n` iterations, where each iteration consists of one additions and one multiplication. This results in $(1+1)n = 2n$ floating point operations(FLOPs).
The outer loops also iterates $n$ times, meaning the the inner loop is repeated $n$ times for a total of $2n*n = 2n^2$ FLOPs. The complexity is thus $O(n^2)$. If $n$ doubles, we expect to use four times as much time.

```python
import time
import matplotlib.pyplot as plt

time_used = []
N = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
for n in N:
    repeat = 10

    A = np.ones((n, n))
    x = np.ones(n)

    start = time.time()
    for i in range(repeat):
        y = mvm(A, x)
    end = time.time()

    time_used.append((end - start) / repeat)

plt.plot(N, time_used)
plt.show()
```

From the plot, we see that $n=300$ used about 0.05 seconds, while $n=600$ used 0.2 seconds, which is in accordance with our estimate of the complexity.

#### Exercise 1c) High level optimization

We remove the inner for-loop and write out the three multiplications explicitly, avoiding all the multiplications with zero. The endpoints are handled separately.

```python
def mvm_tridiagonal(A, x):
    n = len(x)
    y = np.zeros(n)

    y[0] = A[0, 0] * x[0] + A[0, 1] * x[1]

    for i in range(1, n - 1):
        y[i] = A[i, i - 1] * x[i - 1] + A[i, i] * x[i] + A[i, i + 1] * x[i + 1]

    y[n - 1] = A[n - 1, n - 2] * x[n - 2] + A[n - 1, n - 1] * x[n - 1]
    return y
```

#### Exercise 1d) Benchmarking tailored algorithm


For each `i`, disregarding the endpoints `i=0` and`i=n-1`, 3 multiplications and 2 additions are done. The for-loop therefore totals $(n-2)*(3+2) = 5n - 10$ FLOPs. The endpoints accounts for 6 FLOPs(4 mult and 2 add), meaning the algorithm performs a grand total of $5n - 4$ FLOPs. Thus, the complexity is $O(n)$. We expect a linear relationship between $n$ and the time used.

```python
time_used = []
N = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]
for n in N:
    repeat = 100

    A = np.ones((n, n))
    x = np.ones(n)

    start = time.time()
    for i in range(repeat):
        y = mvm_tridiagonal(A, x)
    end = time.time()

    time_used.append((end - start) / repeat)

plt.plot(N, time_used)
plt.show()
```

The plot looks very linear, confirming that the relationship in indeed linear. We also see that for $n=1000$, the new method used about 0.002 seconds instead of close to 0.6 second, amounting to a considerable speedup.


#### Exercise 1e) Optimizing with respect to memory

```python
def mvm_tridiagonal(a, b, c, x):
    n = len(x)
    y = np.zeros(n)

    y[0] = b[0] * x[0] + c[0] * x[1]

    for i in range(1, n - 1):
        y[i] = a[i - 1] * x[i - 1] + b[i] * x[i] + c[i] * x[i + 1]

    y[n - 1] = a[n - 2] * x[n - 2] + b[n - 1] * x[n - 1]

    return y
```

Given $n = 100000$ and each element is double precision(8B), the total size of the three vectors a, b and c is $(99999 + 100000 + 99999)*8B \approx 2.4\text{MB}$. In matrix form, this was previously $80\text{GB}$! A very dramatic reduction in use of memory.


### Exercise 2) Mixed programming with the upper triangular matrix

#### Exercise 2a) Optimization using vectorization

We have replaced the inner for-loop using the built in numpy dot product, which invokes fast C-code. The arrays are sliced such that only the non-zero elements are multiplied.

```python
def mvm_upper_vectorized(A, x):
    n = len(x)
    y = np.zeros(n)

    for i in range(n):
        y[i] = np.dot(A[i, i:], x[i:])

    return y
```

#### Exercise 2b) Cython

All variables have been declared, including the return type of the function itself. `#cython: boundscheck=False` and `#cython: wraparound=False` has been used to stop boundary checking when indexing the array. To circumvent the highlighting of `len(x)`, which is an interaction with a python object, `n` can be passed as an argument instead. The only yellow highlights left are `np.zeros` and the function itself, since these are python objects.

```ipython
%load_ext Cython
```

```cython magic_args="-a"
#cython: boundscheck=False
#cython: wraparound=False

import numpy as np
cimport numpy as np

cpdef np.ndarray[double, ndim=1] mvm_upper_cython(np.ndarray[double, ndim=2] A, np.ndarray[double, ndim=1] x):
    cdef size_t n = len(x)
    cdef np.ndarray[double, ndim=1] y = np.zeros(n)

    cdef int i, j
    cdef double sum

    for i in range(n):
        sum = 0
        for j in range(i,n):
            sum += A[i,j]*x[j]

        y[i] = sum
    return y
```

#### Exercise 2c)

`jit` is simply implemented by writing the decorator. The speedup is as good as cython, if not better in this case.

```python
from numba import jit


@jit()
def mvm_upper_jit(A, x):
    n = len(x)
    y = np.zeros(n)

    for i in range(n):
        sum = 0
        for j in range(i):
            sum += A[i, j] * x[j]

        y[i] = sum
    return y
```
