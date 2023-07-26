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


# Functional programming in Python

Throughout this material, we have talked a lot about object-oriented programming, which is all about making classes. We will now introduce another programming paradigm called functional programming. In this paradigm, functions are the primary building block.

Many programming languages are considered either object-oriented or functional. However, both paradigms can be used in Python. Being proficient in both object-oriented and functional programming will help improve one's coding skills. We will not argue that one paradigm is better than the other. It is a matter of preference.

## Functions as arguments to functions

In Python, functions are *first class objects*, meaning they can be treated as variables and be passed to other functions. Consider the following example

```{code-cell} python
def square(x):
    return x * x


def map_func_over_list(func, lst):
    return [func(x) for x in lst]


y = [1, 2, 3]
z = map_func_over_list(square, y)

print(f"{y = }")
print(f"{z = }")
```
The function `map_func_over_list` takes in a function and a list as arguments and returns a new list where the function is applied to each element. Being able to pass functions as arguments to other functions is a very powerful idea! In fact, the function `map_func_over_list` is already a built-in function in Python called `map`
```{code-cell} python
print(list(map(square, y)))
```



## Higher-order functions

A higher-order function is a fancy name for a function that takes another function as an argument. One example is the `map` function, as described above.


## Pure functions

A pure function is a function that always returns the same value if the given argument is the same. One example is the `square` function. If the same argument (`x`) is passed twice, e.g.,
```python
y = square(x)
z = square(x)
```
`y` is always going to be equal to `z`. Hence `square` is a pure function.

What would be an example of a non-pure function?

Any function that depends on the program's state will not be a pure function. Instance methods in a class are typically not pure (but they can be). Here is a simple example of a function that is not pure

```python
import datetime


def compute_age_this_year_unpure(year_born):
    return datetime.datetime.now().year - year_born
```
If we compute the following
```python
year_born = 1999
y = compute_age_this_year_unpure(year_born)
z = compute_age_this_year_unpure(year_born)
```
Can we make this function pure? Of course, we just have to pass in the current year as a `year_today` argument

```python
def compute_age_this_year_pure(year_born, year_today):
    return year_today - year_born


year_born = 1999
year_today = datetime.datetime.now().year
y = compute_age_this_year_pure(year_born, year_today)
z = compute_age_this_year_pure(year_born, year_today)
```
Will `y` and `z` be equal in this case? Yes!

### Why are pure functions nice?

There are several reasons why pure functions are useful. One reason is that they are much easier to test. If we want to test `compute_age_this_year_pure` it would be straight-forward, e.g.,


```python
def test_compute_age_this_year_pure():
    assert compute_age_this_year_pure(2000, 2022) == 22
```

Testing the unpure function is much more challenging. One would need to apply an advanced technique called [mocking](https://realpython.com/python-mock-library/), which is not covered in this material.

Another nice thing about pure functions is that we can use [*memoization*](https://www.knowledgehut.com/blog/programming/memoization-in-python) to increase performance. The idea behind memoization is to store the argument and the function's returned value in storage. The memorized value can be returned if the function is called with the same argument twice. We will look at this later in this section after we have covered {ref}`python-scopes`.


## Names, Namespaces and Scope

* We constantly define new names for variables, functions and classes and import numerous others from modules and packages.
* It would be impossible to keep track of all the names used throughout an extensive program and all its imports.
* Potential name conflicts are resolved using the concepts of *namespaces* and *scope*.



### Python namespaces
A *namespace* is simply a mapping from names to objects. Names should uniquely define an object within a single namespace, but objects in different namespaces may have the same name. A real-world analogy is license plate numbers for cars. The license plate uniquely identifies a car in Norway, but a car can have the same number combination in Denmark. The two countries define different *namespaces*, and to uniquely identify a car, one needs to know *both the namespace and local name*. An example closer to the programming world is a file system directory. Each directory defines a local namespace, so two files having identical names but stored in different directories are uniquely identified.


In Python, namespaces are created dynamically as objects are created. A namespace containing all the built-in Python names is created when Python starts and is never deleted. Similarly, all variables created in the top-level script exist in the global namespace (`__main__`). Each module has its own global namespace, which exists until Python ends. A class definition creates a new namespace local to that class. Since a class definition is usually not deleted, this namespace also exists until we end Python. Every time a class instance is created, a new local namespace is created, which is deleted when the object is deleted. When a function is called, it creates a new local namespace, which exists until the function is done executing.



We access names in different namespaces using the standard *dot* notation, as in `math.exp`, `numpy.array`, `Sphere.from_volume` and `p.Name`. If the dot notation is not used, Python will search for the name according to a predefined set of rules, starting with the local namespace and moving up the hierarchy of more "global" namespaces. See the discussion of scope below for a more precise definition.



If Python namespaces are understood, the difference between the various ways to import modules becomes quite clear.
```{code-cell} python
import numpy
```
will create a new namespace with the name `numpy`, containing all the variable and function names defined in the `numpy` module. The statement
```{code-cell} python
import numpy as np
```
does the same thing but gives the name `np` to the new namespace. Prefixing with `np.` gives access to all the names defined by the module. On the other hand, the statement
```python
from numpy import *
```
will not create a new namespace but instead imports all the names defined by NumPy into the current global namespace. This makes the names directly accessible without prefixing and creates the potential for name conflicts. To see the difference, call the function `dir()` in an interactive Python window. This function returns a list of names currently available in the local namespace and the names of all the existing namespaces. After checking the output of `dir()`, import NumPy using the different approaches and call the function again.


(python-scopes)=
### Scope of names and namespaces

A variable's *scope* is the part of the program where a variable name is accessible. When a Python program is running, there are several nested scopes in which the variable names are directly accessible, i.e., whose namespaces are searched automatically (without the need to prefix). The namespace search priority is
* The local (innermost) scope includes the local variables defined inside a function and all parameters passed to a function.
* The local scope of all enclosing functions. This can happen if a function is defined inside another function.
* The global scope of the module or program, i.e., variables and function names defined at the top level of the program.
* The global namespace of Python built-in names.


Variables in Python are local by default. If a variable is declared inside a function, the variable does not exist when the function is finished executing. Technically, the variable name is defined in the local namespace of the function, and this namespace is deleted when the function is done executing


```{code-cell} python
def pancake_area():
    pi = 3.14159
    r = 15

    return pi * r**2


print(pancake_area())

# print(r)  #Will not work since r does not exist outside function
```

If a global variable with the same name exists, it can be used inside a function.

```{code-cell} python
pi = 3.14159
r = 10


def pancake_area():
    return pi * r**2  # here both pi and r are global


print(pancake_area())
```

We can also create a new local variable inside the function, which will overwrite the variable in the global scope.


```{code-cell} python
pi = 3.14159
r = 10


def pancake_area():
    r = 15  # creates a new local variable
    return pi * r**2  # here r is local, pi is global


print(pancake_area())

print(r)  # prints the global r
```

Now, here comes a mysterious error. Let us try to change the global variable in the function, decrement it by 5 and then use that value

```{code-cell} python
pi = 3.14159
r = 10


def pancake_area():
    r -= 5  # Try to decrement the global variable (DOES NOT WORK!)

    return pi * r**2  # here r is local, pi is global


print(pancake_area())
```

We get
```
UnboundLocalError: local variable 'r' referenced before assignment
```
Why? This is because we are trying to change a value in the local scope, but there is no variable with the name `r` defined in the local scope (only in the global scope). The rule of thumb is that changing a value can only be done in the scope where the variable is defined.


### The `locals` and `globals` dictionaries

We can access the global and local variables with the built-in functions `globals()` and `locals()`, which return dictionaries of the available names


```{code-cell} python
# print(globals()) #gives lots of output (all the names defined so far)
# print(locals()) #same output since we are in the global scope

print(locals() == globals())  # should return True


def tiny_function():
    a = 1
    b = 1.5
    # print the variables in the local scope:
    print(locals())
    return a + b


# look up a name in the globals dictionary:
print(globals()["tiny_function"])

tiny_function()
```

It is even possible to add variables to the global scope by adding them to the globals dictionary. For example, `c` is not defined, so let us put it in the `globals` dictionary

```{code-cell} python
globals()["c"] = 0
print(c)
```


This is not recommended, but it is useful to know how it works.

The output from `locals()` is similar to that of `dir()`, which, when called without arguments, will return a list of valid names in the current local scope. However, while `dir` returns a list of names, `locals()` gives a dictionary of variable names and values. As described above, there may be several nested scopes, but `locals()` will always return the names of the innermost local scope, and `globals()` will return the names of variables defined in the outermost global scope.



### Closure

Suppose one sticks to the general coding practice of passing variables as arguments and return values. In that case, one rarely needs to think about how Python searches its namespaces or how names are transferred from one namespace to another. However, one particular example worth knowing and frequently used by Python programmers is known as *closure*. Consider the example of a function that uses some parameters, which can be implemented as a class with a `__call__` special method

```{code-cell} python
class ThrowClass:
    def __init__(self, v0):
        self.v0 = v0
        self.g = 9.81

    def __call__(self, t):
        return self.v0 * t - 0.5 * self.g * t**2


throw1 = ThrowClass(v0=5.0)

for i in range(5):
    t = i * 0.05
    print(f"{t:.2f} {throw1(t):.2f}")
```


An alternative implementation, which many will consider more "Pythonic", avoids the class concept completely

```{code-cell} python
def throw_fun(v0):
    g = 9.81

    def height(t):
        return v0 * t - 0.5 * g * t**2

    return height


throw2 = throw_fun(5.0)

for i in range(5):
    t = i * 0.05
    print(f"{t:.2f} {throw2(t):.2f}")
```


What happens here is that when the function `throw_fun` is called, it defines a local namespace containing `v0` and `g`. The function `height` will search this namespace for variable names that it cannot find in its local namespace. The magic happens when the `throw_fun` function returns a `height` function (note that the function itself is returned, not the result of the function call). Now, the returned function will remember the namespace defined by the outer function, even after `throw_fun` is finished executing. This namespace is locked to the function object `throw2`, and even if we create a new global `v0` variable, all calls to `throw2` will use the value 5.0.

There is also a function called `partial` from the `functools` library, which returns a partial function where some of the arguments are set


```{code-cell} python
from functools import partial


def throw_fun(v0, t, g=9.81):
    return v0 * t - 0.5 * g * t**2


# Sets the first argument (i.e v0) to 5.0
throw3 = partial(throw_fun, 5.0)

for i in range(5):
    t = i * 0.05
    print(f"{t:.2f} {throw3(t):.2f}")
```

### Timing the function

It is often insightful to time a function's execution. For example, consider the sum of the truncated alternating harmonic sequence, as given by

$$
\sum_{i=1}^n (-1)^{i+1} \frac{1}{i} .
$$

The following function returns such a sum
```{code-cell} python
def alt_h(n):
    return sum((-1) ** (i + 1) * (1 / i) for i in range(1, n + 1))
```
One way we could time this function is to do the following (we will see better ways of doing this later in the material)

```{code-cell} python
import time

# Take the time right now
t0 = time.time()
# Call the function
alt_h(100_000)
# Print the difference between the time now and the time before
print(f"Elapsed time {time.time() - t0}")
```

A cleaner way to do this would be to create a function `timed_func` that takes in another function, `f`, as an argument. Then we declare a third function, `new_f`, that calls `f` and measures the elapsed time. This is best explained with the following code.

```{code-cell} python
def timed_func(f):
    # Takes the function we want to time as input

    # Now create a new function (assume it only takes one argument - similar to alt_h)
    def new_f(n):
        t0 = time.time()
        # Call the function
        f(n)
        # Print the difference between the time now and the time before
        print(f"Elapsed time {time.time() - t0}")

    # Return the new timed function
    return new_f
```

Now we can first create a version of the `alt_h` function and use that instead
```{code-cell} python
timed_alt_h = timed_func(alt_h)
timed_alt_h(100_000)
```

We have now created a decorator, which has been discussed several times in this material.

A decorator is a function that takes another function as an argument and returns a new (decorated) function. In this case, the "decoration" prints the time it takes to run the function.

We can now write the function like this instead

```{code-cell} python
@timed_func
def alt_h_v2(n):
    return sum((-1) ** (i + 1) * (1 / i) for i in range(1, n + 1))
```
and this should be equivalent to `timed_alt_h` that we created above, but we do not need to go through all the hassle of creating a new function

```{code-cell} python
alt_h_v2(100_000)
```


### Memoization

Let us go back to the pure functions we discussed at the beginning of this section and see how we can apply memoization to speed up the performance. Consider a classic use case of memoization, the recursive Fibonacci function.

```{code-cell} python
def fib(n):
    print(f"Computing fib({n})")
    if n == 0:
        return 0
    if n == 1:
        return 1
    return fib(n - 1) + fib(n - 2)
```
This function seems pretty expensive to run for large numbers. Let us try to run this function with `n = 5` and see what is printed.

```{code-cell} python
fib(5)
```
Since `fib` is a pure function, it is perfect for memoization. We will do this by wrapping it into another function where we store the values in a dictionary.

```{code-cell} python
def memoize(f):

    # Create a dictionary to store the values
    storage = {}

    def wrap(n):
        if n not in storage:
            # The value is not been computed yet
            # So lets compute it and put it in the storage
            storage[n] = f(n)
        return storage[n]

    return wrap
```
Since `memoize` is a decorator, it can be applied to `fib`.
```{code-cell} python
@memoize
def fib(n):
    print(f"Computing fib({n})")
    if n == 0:
        return 0
    if n == 1:
        return 1
    return fib(n - 1) + fib(n - 2)
```
Let us see now how many times the `fib` method is called.
```{code-cell} python
fib(5)
```
As expected, the method is called only once for each new argument. Otherwise, it uses the stored value.



### Summary of scopes and namespaces
* Python variables are, by default, local. When a name is read, Python will first search the local namespace, then successively more "global" spaces until it finds a variable with that name.
* A variable defined in the global scope can be accessed inside functions, but any attempt to modify it will create a new, local variable.
* The keyword `global` can override the default behavior and modify global variables inside functions. However, this is bad practice that should generally be avoided.
* To avoid name conflicts, use import statements like `import math` to create a new namespace for the imported module, rather than importing everything into the existing namespace with `from math import *`
* The functions `globals(), locals(), dir()` are useful for examining existing namespaces.
* When a function is defined inside another function, it remembers the namespace of the outer function. This technique, called closure, can be used to create parameterized functions.
