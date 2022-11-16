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


# Functional programming in python

During this course we have talked a lot about object-oriented programming, which is all about making classes. We will now introduce another programming paradigm called functional programming. In this paradigm, functions are the main building block.

Many programming languages are considered either object-oriented or functional. However, in python we can use both paradigms. Knowing a little bit about both object-oriented programming and functional programming will make you a better programmer in general because you will have a larger arsenal of tools in your toolbox. We will not argue that one paradigm is better than the other. It is a matter of preference.

## Functions as arguments to functions

In Python, functions are *first class objects* which means that you can treat functions as variables and pass them to other functions. Consider the following example

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
In this example we first create a function called `square` that expects a number and returns the square of it. Next we define another function `map_func_over_list` that takes as a function and a list and returns a new list where the function is applied to each element in the input list. Being able to pass functions as arguments to other functions is a very powerful idea! In fact the function `map_func_over_list` is already a built in function in python called `map`:
```{code-cell} python
print(list(map(square, y)))
```



## Higher order functions

A higher order function is just a fancy name for a function that takes another function as one of its argument. One example is the `map` function that takes a function as the first argument and an iterable (e.g a list) as the seconds argument and returns a new iterable where the function is applied to each element in that list.


## Pure functions

A pure function is a function that for a given argument always return the same value. One example is the `square` function we just saw. If we have
```python
y = square(x)
z = square(x)
```
for some argument `x`, we know that `y` is always going to be equal to `z`. Hence `square` is a pure function.

What would be an example of a non-pure function?

Any function that depends on the state of the program will not be a pure function. Instance methods on a class are typically not pure (but they can be). Here is a simple example of a function that is not pure

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
Will `y` and `z` be equal? Well, in most cases they will, but if you happen to run this program at new years eve then you might be unlucky. Can we make this function pure? Of course, we just have to pass in the year today as an argument

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

There are several reasons why we like pure functions. One reason is that they are much easier to test. If we want to test `compute_age_this_year_pure` it would be fairly straight forward, e.g


```python
def test_compute_age_this_year_pure():
    assert compute_age_this_year_pure(2000, 2022) == 22
```

Testing the unpure function is much more tricky. In fact you would need to apply a a rather advanced technique called [mocking](https://realpython.com/python-mock-library/) in order to do it, which is not covered in this course.

Another nice thing about pure functions is that since they are always returning the same value for a given argument we can use something called [*memoization*](https://en.wikipedia.org/wiki/Memoization) to increase the performance. The idea behind memoization is to store the argument and the returned value of the function in some storage. Then, when the function is called we check if the value is already computed, and if it is we return the value from the storage. Otherwise we run the function and update the storage. We will look at this a bit later in this section after we have covered {ref}`python-scopes`.


## Names, Namespaces and Scope

* We constantly define new names for variables, functions, classes, etc., and import numerous others from modules and packages.
* It would be impossible to keep track of all the names that are used throughout a large program and all its imports.
* Potential name conflicts are resolved using the concepts of *namespaces* and *scope*.



### Python namespaces
A *namespace* is simply a mapping from names to objects. Within a single namespace, names should uniquely define an object, but objects in different namespaces may have the same local name. A real-world analogy is license plate numbers for cars. In Norway, the license plate uniquely identifies a car, but if you go to Denmark a car can have exactly the same number combination. The two countries define different *namespaces*, and to uniquely identify a car you need to know *both the namespace and local name*. An example closer to the world of programming is a directory in a file system. Each directory defines a local namespace, so two files having identical names but stored in different directories are uniquely identified.


In Python, namespaces are created dynamically as objects are created. A namespace containing all the builtin Python names is created when Python starts, and is never deleted. Similarly, all variables created in the top level script exist in the global namespace (`__main__`), and each module has its own global namespace, which also normally exist until Python ends. A class definition creates a new namespace local to that class. Since a class definition is usually not deleted, this namespace also exists until we end Python. On the other hand, every time we create an instance of the class we create a new local namespace, which is deleted when the object is deleted, and when a function is called it creates a new local namespace, which exists until the function is done executing.



We access names in different namespaces using the standard *dot* notation, as in `math.exp`, `numpy.array`, `Sphere.from_volume`, `p.Name`, etc. If we don't use the dot notation to specify which namespace a variable name belongs to, Python will search for the name according to a predefined set of rules, starting with the local namespace and moving up the hierarchy of more "global" namespaces. See the discussion of scope below for a more precise definition.



If we understand how Python namespaces work, the difference between the various ways we import module becomes quite clear:
```{code-cell} python
import numpy
```
will simply create a new namespace with the name `numpy`, containing all the variable and function names defined in the `numpy` module. The statement
```{code-cell} python
import numpy as np
```
does the same thing, but gives the name `np` to the new namespace we have created. Prefixing with `np.` gives access to all the names defined by the module. On the other hand, the statement
```python
from numpy import *
```
will not create a new namespace, but instead imports all the names defined by NumPy into the current, global namespace. This makes the names directly accessible without prefixing, but also creates potential for name conflicts. To clearly see the difference you can call the function `dir()` in an interactive Python window. This function returns a list of names currently available in the local namespace, and the names of all the existing namespaces. After checking the output of `dir()` import NumPy using the different approaches and call the function again.


(python-scopes)=
### Scope of names and namespaces

A *scope* of a variable is defined as the part of the program where a variable name is accessible. When a Python program is running, there are several nested scopes in which the variable names are directly accessible, i.e. whose namespaces are searched automatically (without the need to prefix):
* The local (innermost) scope includes the local variables defined inside a function, as well as all parameters passed to a function. This namespace is searched first
* The local scope of all enclosing functions, if you have a function definition inside a function definition.
* The global scope of the module or program, i.e., variables and function names defined at the top level of the program.
* The global namespace of Python builtin names.


Variables in Python are local by default. If you define a variable inside a function, the variable does no longer exist when the function is done executing. Technically, the variable name is defined in the local namespace of the function, and this namespace is deleted when the function is done executing:


```{code-cell} python
def pancake_area():
    pi = 3.14159
    r = 15

    return pi * r**2


print(pancake_area())

# print(r)  #Will not work since r does not exist outside function
```


If a global variable with the same name exists you can use that variable inside a function

```{code-cell} python
pi = 3.14159
r = 10


def pancake_area():
    return pi * r**2  # here r is local, pi is global


print(pancake_area())
```

You can also create a new local variable inside the function, and this will overwrite the variable in the global scope.


```{code-cell} python
pi = 3.14159
r = 10


def pancake_area():
    r = 15  # creates a new local variable

    return pi * r**2  # here r is local, pi is global


print(pancake_area())

print(r)  # prints the global r
```

Now, here comes a rather mysterious error. Lets try to change the global variable in inside the function, be decrementing it by 5 and then use that value

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
Why? This is because we are trying to change a value in the local scope but there is no variable with the name `r` defined in the local scope (only in the global scope). The rule of thumb is that changing a value can only be done in the scope where the variable is defined.


### The `locals` and `globals` dictionaries

We can access the global and local variables with the built-in functions `globals()` and `locals()`, which return dictionaries of the available names:


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


# look up a name the globals dictionary:
print(globals()["tiny_function"])

tiny_function()
```

It is even possible to add variables to the global scope by simply sticking it in the globals dictionary. For example `c` is not defined, so let us put it in the `globals` dictionary

```{code-cell} python
globals()["c"] = 0
print(c)
```


This is not something you should do, but it is nice to know how it works.

The output from `locals()` is similar to that of `dir()`, which when called without arguments will return a list of valid names in the current local scope. However, while `dir` returns a list of names, `locals()` gives a dictionary of variable names and values. As described above there may be several nested scopes, but `locals()` will always return the names of the innermost local scope, and `globals()` returns the names of variables defined in the outermost global scope.



### Closure

If one sticks to the general coding practice of passing variables as arguments and return values, and avoiding the use of global variables, one rarely needs to think about how Python searches its namespaces or how names are transferred from one namespace to another. However, one particular example worth knowing about is known as *closure*, and is frequently used by Python programmers. Consider the example of a function that uses some parameters, which can be implemented as a class with a `__call__` special method:

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


An alternative implementation, which many will consider more "Pythonic" avoids the class concept completely:

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


What happens here is that when the function `throw_fun` is called, it defines a local namespace containing `v0,g`. The function `height` will search this namespace for variable names that it cannot find in its own local namespace. The magic happens when the `throw_fun` function returns a `height` function (note that the function itself is returned, not the result of the function call). Now, the returned function will remember the namespace defined by the outer function, even after `throw_fun` is done executing and the namespace is therefore deleted. This namespace is locked to the function object `throw2` and even if we create a new global `v0` variable all calls to `throw2` will use the value 5.0.

There is also a function called `partial` from the `functools` library which returns a partial function which some of the arguments set


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

One thing you might want to do is to time a function, to measure the execution time of the function call. For example, consider the sum of the truncated alternating harmonic sequence, as given by

$$
\sum_{i=0}^n (-1)^i \frac{1}{i} .
$$

The following function returns such a sum:
```{code-cell} python
def alt_h(n):
    return sum((-1) ** (i+1) *(1 / i) for i in range(1, n+1))
```
One way you could time this function is to do the following (we will see better ways of doing this later in the course):

```{code-cell} python
import time

# Take the time right now
t0 = time.time()
# Call the function
alt_h(100_000)
# Print the difference between the time now and the time before
print(f"Elapsed time {time.time() - t0}")
```
Now what we can do is to wrap out function inside another function that will simple run the function, but also print the time it took to run it. To do this we will make a function that takes as input the function we want to time, and return a new function that will do the same thing, but also print the elapsed time

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

Now we can first create a version of the `alt_h` function, and use that in stead
```{code-cell} python
timed_alt_h = timed_func(alt_h)
timed_alt_h(100_000)
```
That worked like a charm.

Actually, we have just created something that you have already seen several times in the course already. Do you know what it is? It's a decorator!

A decorator is just a function that takes another function as argument an return a new (decorated) function. In this case the "decoration" is to print the time it takes to run the function.

We can now actually write the function like this instead

```{code-cell} python
@timed_func
def alt_h_v2(n):
    return sum((-1) ** (i+1) *(1 / i) for i in range(1, n+1))
```
and this should be equivalent to `timed_alt_h` that we created above, but we don't need to go through all the hassle of creating a new function:

```{code-cell} python
alt_h_v2(100_000)
```


### Memoization

Let us go back to the pure functions we discussed in the beginning of this section and see how we can apply memoization to speed up the performance. Let ut consider a classic example of memoization, the recursive fibonacci function (lets also add a little print statement in there)

```{code-cell} python
def fib(n):
    print(f"Computing fib({n})")
    if n == 0:
        return 0
    if n == 1:
        return 1
    return fib(n-1) + fib(n-2)
```
This function will be quite expensive to run for large number. Let us try to run this function with `n = 5` and see what is printed.

```{code-cell} python
fib(5)
```
Wow! That is a lot of function calls. Now each, you can imagine that this will be quite expensive after a while. But, we known that the `fib` function is a pure function, so let's try to memoize it! We will do this by wrapping it into another function where we store the values in a dictionary, as shown below.

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
Again we have created a decorator so we could apply it as a decorator:
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
Let us see now how many times we actually call the `fib` method
```{code-cell} python
fib(5)
```
As expected, we only call the method one time for each argument and use the value in the storage otherwise.



### Summary of scopes and namespaces
* Python variables are by default local. When a name occurs, Python will first search the local namespace, then successively more "global" spaces until it finds a variable with that name.
* A variable defined in the global scope can be accessed inside functions, but any attempt to modify it will create a new, local variable.
* The keyword `global` can be used to override the default behavior, and modify global variables inside function. However, this is bad practice that should normally be avoided.
* To avoid name conflicts, use import statements like `import math` to create a new namespace for the imported module, rather than importing everything into the existing namespace with `from math import *`
* The functions `globals(), locals(), dir()` are useful for examining existing namespaces.
* When a function is defined inside another function, it remembers the namespace of the outer function. This technique, called closure, can be used to create parameterized function.
