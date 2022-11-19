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

# Week 13

## Parallel programming

### Exercise 4) Brute force optimization

A typically problem arising in scientific computing is minimization of some function of your input parameters. For example you can can have a function that represents the misfit between your model and data. Say that you have an ODE describing some some physical phenomena and some data that you want to fit to that model. Then you could try different parameters in your model and see which one that best describes your data.

In this exercise we will only try to find the minimum of the [Ackley function](https://en.wikipedia.org/wiki/Ackley_function) by only sampling the parameter space. The Ackley function is a special function that is considered difficult to minimize and is used as a [test function for optimization algorithms](https://en.wikipedia.org/wiki/Test_functions_for_optimization). It has a global minimum at $(x, y) = (0,0)$, but it has also several local minima.

```python
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d


def func(x, y):
    return (
        -20 * np.exp(-0.2 * np.sqrt(0.5 * (x**2 + y**2)))
        - np.exp(0.5 * (np.cos(2 * np.pi * x) + np.cos(2 * np.pi * y)))
        + np.exp(1)
        + 20
    )
```

To see that this is a difficult function to minimize we can try one one the standard minimization methods from [scipy](https://docs.scipy.org/doc/scipy/reference/generated/scipy.optimize.minimize.html).

```python
from scipy.optimize import minimize

f = lambda x: func(*x)
res = minimize(f, x0=(1, 3), method="Nelder-Mead")
print(res)
```

The global minimum value is at (0.0), but you will see that the results will heavily depend on the initial starting point ($x_0$). A more robust approach is to simply loop over all possible values and keep track of the minimum value.


#### Exercise 4a)
Plot the Ackley function surface for $x, y \in [-5, 5]$.

```python
x = np.arange(-5, 5, 0.01)
y = np.arange(-5, 5, 0.1)
X, Y = np.meshgrid(x, y)
Z = func(X, Y)


fig = plt.figure(figsize=(6, 6))
ax = fig.add_subplot(111, projection="3d")
ax.plot_surface(X, Y, Z, cmap="jet")
plt.show()
```

#### Exercise 4b)
Implement a function that loops over a uniform grid for $x, y \in [-5, 5]$, and find the minimum of the Ackley function. Choose appropriate grid size and compute the time it takes to find the minimum.

```python
import time


def brute_force_serial(x, y):
    fmin = np.inf
    min_x = None
    min_y = None

    for xi in x:
        for yi in y:

            f = func(xi, yi)
            if f < fmin:
                min_x = xi
                min_y = yi
                fmin = f

    return (min_x, min_y), fmin


t0 = time.time()
N = 2000
x = np.linspace(-5, 5, N)
y = np.linspace(-5, 5, N)
min_index, fmin = brute_force_serial(x, y)
t1 = time.time()
print(f"Minimum index = ({min_index[0]:.3f}, {min_index[1]:.3f}), Value = {fmin:.3f}")
print(f"Elapsed time {t1 - t0:3f} seconds")
```

#### Exercise 4c)
Split the grid into smaller subgrids and apply the brute force method by looping over the points on each subgrid on different processes. Estimate the time it takes to run the program and compare with the serial version.

```python
from concurrent.futures import ProcessPoolExecutor


def func_parallel(index):
    return brute_force_serial(x[index::4], y[index::4])


inds = []
values = []
t0 = time.time()
with ProcessPoolExecutor() as executor:
    for index, value in executor.map(func_parallel, range(4)):
        print(index, value)
        inds.append(index)
        values.append(value)

t1 = time.time()
fmin = np.min(values)
min_index = inds[np.argmin(values)]
print(f"Minimum index = ({min_index[0]:.3f}, {min_index[1]:.3f}), Value = {fmin:.3f}")
print(f"Elapsed time {t1 - t0:3f} seconds")
```
