---
jupyter:
  jupytext:
    text_representation:
      extension: .md
      format_name: markdown
      format_version: '1.3'
      jupytext_version: 1.10.3
  kernelspec:
    display_name: 'Python 3.9.2 64-bit (''in1910-book'': conda)'
    name: python3
---

# Week 7
## Object-oriented programming in C++

### Part A) Cartesian and polar coordinates

#### Defining structs

**a)** Create a struct that represents a point in the plane in cartesian coordinates:

$$\vec{r} = (x, y).$$

**b)** Create a struct that represents a point in the plane in polar coordinates.

$$\vec{r} = (r, \theta).$$

#### Translating between coordinate systems

**c)** Create a function `cart2polar` that takes in a point defined in cartesian coordinates, and returns the same point in polar coordinates. To do this, you will need some trigonometric functions, which you can include from the `<cmath>` standard header.

**d)** Create the inverse function, `polar2cart`.

**e)** Test your function by converting some points by hand, and making sure your functions act as intended. Then verify that using both functions:
```
polar2cart(cart2polar(u))
```
gives the same vector as the original.

#### Transforming vectors

We now define two operations we can do on these vectors. First we define *scaling*  as the operation that changes the length of the vector, but not its orientation. In polar coordinate this means $r$ is changed, but not $\theta$:

$$\mbox{scale}(\vec {r}, s) = (r\cdot s, \theta).$$

**f)** Implement a function `scale` that takes in a point defined in polar coordinates and returns a scaled variant.

In Cartesian coordinates, the scale operation is given by scaling $x$ and $y$ by the same factor:

$$\mbox{scale}(\vec {r}, s) = (x\cdot s, y\cdot s).$$

**g)** Overload the `scale` function, so that it also correctly scales input in cartesian coordinates.

Next we define the *rotate* operation, which changes the orientation ($\theta$), but not the length $r$. In polar coordinates, this operation is given as

$$\mbox{rotate}(\vec {r}, \omega) = (r, \theta + \omega).$$
While in Cartesian coordinates, it is a bit more complicated

$$\mbox{rotate}(\vec {r}, \omega) = \begin{bmatrix} \cos(\omega) & -\sin(\omega) \\ \sin(\omega) & \cos(\omega) \end{bmatrix} \begin{bmatrix} x \\ y \end{bmatrix}.$$

**h)** Implement the `rotate` function. Use function overloading so that it can take either struct as input.



### Part B) Affine Transforms

In 2D an affine transform can be written as
$$f(x, y) = \begin{bmatrix} a & b \\ c & d\end{bmatrix}\begin{bmatrix}x \\ y\end{bmatrix} + \begin{bmatrix}e \\ f\end{bmatrix}.$$

**a)** Define a class `AffineTransform` that stores the six parameters $a, \ldots, f$ as private variables in the class.

**b)** Define a constructor for the class that takes all six parameters in.

**c)** Also make it possible to only send in the four first ($a, b, c, d$) in, in which case the last two should default to 0. You can do this either by overloading the constructor, or by using default arguments.

**d)** Define a method to evaluate $f(x, y)$. You will need to create a struct of some sort to output your results.

### Part C) A Class for Polynomials

In this exercise, you will implement a class to represent a general Polynomial, much like you did in Python for E2.

To store the coefficients of the polynomial-object in Python, we used a dictionary. In C++, the data type most like a dictionary is the *map*. Before you turn to actually defining the class, let us first get familiar with the `map` data type.

First of, when creating a map object, you must specify what type the keys should be, and what type the values should be, like so:
```C++
map<int, int> partners;
map<string, double> params;
map<int, string> students;
```
After creating the variable, you can use it in the same way as in Python, by indexing with the key:
```C++
partners[2] = 4;
params["friction"] = 0.4;
students[147] = "John Doe";
```
You can iterate over a dictionary as follows:
```C++
for (pair<string, double> element : params)
{
    cout << element.first;
    cout << " -> ";
    cout << element.second;
    cout << endl;
}
```
Here, we loop over the dictionary, and the values are stored in a `pair` data type, to get the key access the `.first` attribute, while the value will be in `.second`.

Now it's time to make the class.

**a)** Define a `Polynomial` class that represents a general polynomial:

$$f(x) = \sum_{n=0}^\infty a_n x^n.$$

The class should store the coefficients $a_n$ as a private `map` variable.

**b)** Define a constructor for the class that takes the coefficients in as a map.

**c)** Define a method `evaluate(double x)`, that returns `f(x)`.

**d)** Define a method `print` that prints out the Polynomial in a pretty and readable way.

**e)** Verify that your class works by creating the polynomial

$$f(x) = x^{10} - 5x^5 + 1,$$

and computing the values for $x=-2, 0, 2$ by hand and comparing.


### More exercises
If you have finished all the exercises for this week, but want to do more. Take a look at this weeks [challenge](C2_primes_by_sieve.ipynb). If you want even more, feel free to send me an email (jonas@simula.no), and I will happily share more.
