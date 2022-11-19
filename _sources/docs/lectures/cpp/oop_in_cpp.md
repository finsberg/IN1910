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

# Object-oriented Programming in C++

We will now start looking at how to program object-oriented in C++, i.e., how to define custom data types through the use of classes.


## Structs

The first topic we will cover are *structs*, short for structures, or more specifically, data structures. These are a way of bundling together data in meaningful ways. Put simply, structs are like classes, in that we can define our own data types, but unlike classes, structs do not have any *methods*. (Strictly speaking, in C++, structs can have methods, but we ignore this for now.)

One of the major differences between C++ and C is that C++ supports classes. In fact, when Bjarne Stroustrup started the development of C++, he originally called it "C with Classes". While C does not have classes, they do have structs, which is the closest thing we have to classes in C.

### Defining structs

A struct is a data type we define, and you can think of it like a data container. We define a struct by specifying what kind of data it should contain as different attributes of the data type. An example could be a position in a 2D plane:
```C++
struct Position
{
    double x;
    double y;
};
```
A set of parameters for a given modelling system
```C++
struct DoublePendulum
{
    double M1;
    double M2;
    double L1;
    double L2;
};
```
Or maybe representing a person for some contact database
```C++
struct Person
{
    string name;
    int age;
    Date birthday; // Date would be another Struct
    ...
};
```
Note especially the semicolon at the end of the struct definition. It is required, and easy to forget, as we do not use them at the end of function definitions.

### Creating struct instances

After a struct is defined, we can create objects of the new data type as we would any other object
```C++
Position p;
```
Once we have defined the variable, you can access the data fields the same way as for instances of classes in Python.
```C++
p.x = 1.5;
p.y = 2.2;
```
You can also initialize the struct on creation:
```C++
Position p{1.5, 2.2};
```
Where the order of the input is in the same order as we defined the data fields of the struct.

In addition to creating struct objects, we can now create functions that take the structs as input or output. We could for example define this function which finds the distance between two points in the plane
```C++
double distance(Position a, Position b)
{
    double dx = (a.x - b.x);
    double dy = (a.y - b.y);
    return std::sqrt(dx * dx + dy * dy)
}
```
Where `std::sqrt` is included from the `<cmath>` standard header.

Similarly, a function can be made to return a struct:
```C++
Position origin()
{
    Position tmp{0, 0};
    return tmp;
```

Unlike Python, C++ functions cannot actually return more than one variable, and so structs are a useful way to return more data from a function, by wrapping them into a useful data structure. The other common way to "return" multiple variables is to do a call by reference.


### Example: Function solving vertical throw with air resistance

We return to the vertical throw example we used in the last lecture, solving the ODE system

$$
    \frac{{\rm d}v}{{\rm d}t} = -m g - D |v| v,
\qquad
    \frac{{\rm d}y}{{\rm d}t} = v.
$$

We now want to implement this as a function that solves this ODE system and returns vectors for the solutions $t$, $v$ and $y$. We use a struct to bundle these together and return them:

```C++
const double G = 9.81;

struct Solution
{
    vector<double> t;
    vector<double> v;
    vector<double> y;
};

Solution vertical_throw(double v0, double y0, double dt, double T, double m, double D)
{
    Solution sol;
    double t = 0;
    double v = v0;
    double y = y0;
    sol.t.push_back(t);
    sol.v.push_back(v);
    sol.y.push_back(y);

    while (sol.t.back() < T)
    {
        t += dt;
        v += -(m * G + D * v * abs(v)) * dt;
        y += v * dt;
        sol.t.push_back(t);
        sol.v.push_back(v);
        sol.y.push_back(y);
    }
    return sol;
}
```

### Unimportant detail: The semicolon

The reason we need a semicolon at the end of a struct definition (as opposed to for functions/tests/loops) is that we can declare instances of the struct as we define the struct if desired:
```C++
struct Position
{
    double x;
    double y;
} p, q;
```
This is a small shortcut one can take if you define a struct and know you want to use it right away. Although, do keep in mind readability if you use it.


## Classes

To define a new class in C++, we use the `class` keyword, much like in Python. A major difference from Python however, is that you have to explicitly declare all attributes of the class and their types. This is done much like shown for structs, we simply define the variables inside the class definition:
```C++
class Circle
{
    double radius;
    double cx;
    double cy;
};
```
However, any attribute defined in this manner will become a *private* variable, meaning you won't be able to access it from outside the class. Trying to read or change the variable:
```C++
Circle s;
s.radius = 10;
```
would simply give an error:
```
error: ‘double Circle::radius’ is private within this context
```
Therefore, when defining a C++ class, we explicitly state what attributes (both data fields and methods) should be private and which should be public. We do this by specifying all public attributes in it's own public block as follows:
```C++
class Circle
{
  public:
    double radius;
    double cx;
    double cy;
};
```
Any attribute, be it a data field or a method, declared under the `private:` block will throw an error if used from outside the class, they can only be used inside the class itself. The attributes declared under the `public:` block however, can freely be accessed and used outside the class.

You can now create objects of the class and set its attributes
```C++
Circle s;
s.radius = 2;
s.cx = -0.5;
s.cy = 0.5;
```
Or you can initialize it as shown for structs:
```C++
Circle s{2, -0.5, 0.5};
```
You will soon learn how to define constructors for the class as well, which gives you even more control when creating class instances.

### Declaring Methods

To declare a class method, simply define a function inside the class definition, just like in Python.
```C++
class Quadratic
{
  public:
    double a;
    double b;
    double c;

    double evaluate(double x)
    {
        return a * x * x + b * x + c;
    }
};
```
In this example, note that the function is declared like you are used to outside classes, starting with the return type, and then specifying the input argument with a type. Because the method is public, you can now call it from outside the class:
```C++
Quadratic f{1, 2, 1};
cout << f.evaluate(3) << endl;
```

An alternative way to do this, which is actually more common for larger project is it to only declare the signature of the function and then write the implementation elsewhere

```C++
class Quadratic
{
  public:
    double a;
    double b;
    double c;

    double evaluate(double);
};

double Quadratic::evaluate(double x)
{
    return a * x * x + b * x + c;
}
```
Notice that we in this case need to tell the compiler that we provide the implementation for the `evaluate` method on the class `Quadratic` using the notation `Quadratic::evaluate`. Also note that in the declaration `double evaluate(double);` we do not need to provide a name of the argument to `evaluate` (but it is also OK if you do).


### Implicit self-reference

Another important thing to notice from the `Quadratic.evaluate` example is that there is no `self` argument into the method, like you are used to from Python. This is because `C++` has an implicit self-reference system. This means you can use any attribute that is defined within the class without having to refer to any `self.`. For example, we just use `a`, `b` and `c` freely. Likewise, you can refer to other methods in the class simply by using their names.

If you ever do need to refer to the object itself, you can do so through the keyword `this`, which is a pointer to the address of the object itself. You do not have to take `this` in explicitly in the function definitions, it is just always available. Note that you will rarely need `this` in C++, because of the implicit self-reference to attributes.

### Defining a constructor

In Python, you use the special method `__init__` to define the constructor. In C++ there is a similar special method that defines the constructor of the class, the name of this method is the same as the name of the class, and we specify the method without giving it any type (not even `void`):
```C++
const double PI = 3.14159265;

class Circle
{
  private:
    double radius;
    double cx;
    double cy;

  public:
    Circle(double r)
    {
        radius = r;
        cx = 0;
        cy = 0;
    }

    double area()
    {
        return PI * radius * radius;
    }
};
```
The constructor we define sets the radius according to the given value, while the coordinates of the center of the circle will be set to 0. Note that we make our constructor to public, but our data fields to private. This is because we want to set the radius on creation, but then we do not want people to go in and tamper with them afterwards. Also, `PI` is not defined in C++ or in a standard header, so we define it outside our class as `const double PI = 3.14159265;`.


To create an instance of the class using the constructor, we do as follows:
```C++
Circle s(4);
```
If you find this syntax confusing, it can be helpful to compare it to how we would do it in Python:
```Python
s = Circle(4)
```
All the same info is used, we just swap the order around and skip the `=` sign.

After creating the object, we are free to use it
```C++
cout << s.area() << endl;
```
However, we cannot access the radius or the center directly, as these are private variables.

### Why privacy?

At this point, you might be asking what the use of declaring variables and methods to be private is. After all, why would you want to *restrict* the option of using or changing things outside the class. It comes down to *encapsulation*, one of the fundamental concepts of object-oriented programming.

Encapsulation is about hiding away the implementation details and data, only revealing an easy-to-use interface to the outside world. By defining attributes as private we are performing *data hiding*, and it makes it more explicit what users of the class are actually meant to interact with.

There is also an element of control and safety in declaring variables as private. By making it impossible to change certain variables from outside the class, you are basically "fool-proofing" your implementation. In Python, this is done by naming variables with a leading underscore (`self._radius`), but there is still nothing there to prevent someone from actually changing it, and perhaps producing erroneous results. In C++ however, specifying something as private guarantees that these variables are not tampered with.

### Getters and Setters

While it might be nice to make it impossible for a user to change a given variable, it would perhaps for them to at least be able to read it out. Take our Circle example, it would be nice to be able to *read* the radius. But this is also prevented when the variable is private.

The common thing to do here is define a "getter", a nickname for a get-method. A get-method is something we call from the outside, asking the class to go "get" some information from inside the class. Sometimes, a get method has to do some calculation or data manipulation to find the desired values, other times it is just about reading and returning a private variable.
```C++
class Circle
{
  private:
    double radius;

  public:
    Circle(double r)
    {
        radius = r;
    }

    double get_radius()
    {
        return radius;
    }
}
```
By declaring `radius` to be private, but also a public method that returns the value means the radius of the circle can be read, but not set. This is an example of a getter method, it doesn't need to have the word "get" in its name, but it is quite common to do so.

Similarly, it is common to define "setters", these are methods that are used for *setting* private variables. Why would you define a getter and setter, instead of just making the variable private? One reason is that the setter method potentially could change multiple variables at once. We could for example do the following
```C++
class Circle
{
  private:
    double radius;
    double cx;
    double cy;

  public:
    Circle(double r)
    {
        radius = r;
        cx = 0;
        cy = 0;
    }
    void set_center(double new_x, double new_y)
    {
        cx = new_x;
        cy = new_y;
    }
};
```
Or you could use it to do data validation of the input for example. Let us say we want to disallow negative radius, or set some upper limit on the possible radius, we could do this as follows
```C++
class Circle
{
  private
    double MAX_RADIUS = 1e4;
    double radius;
    ...

        public : void
                 set_radius(double r)
    {
        if (r < 0)
        {
            throw invalid_argument("negative radius not allowed");
        }
        else if (r > MAX_RADIUS)
        {
            throw invalid_argument("radius exceeds maximum");
            radius = r;
        }
    };
```
The `set_radius` method now checks the input, and if it is not acceptable, we throw an exception (similar to raising an exception in python. Here we go for an `std::invalid_argument` exception, which must be included:
```C++
#include <exception>
```

Defining setters and getters like this is very common in C-style languages like C++ and Java. In Python, you could also do this, but there using properties gives an alternative way of doing things that is considered more efficient and elegant. The two languages therefore has a slightly different way of organizing classes and methods.

## Function Overloading

In C++, functions can be *overloaded*, this means giving multiple functionalities to one function. To describe how this works, first recall that in Python, you can *redefine* a function whenever you wish:

```{code-cell} python
def f(x):
    return 2*x + 2


print(f(2))


def f(x):
    return 2*x - 2


print(f(2))
```

What happens when we redefine the variable is that we simply create a new function, and the name `f` now refers to this new function, rather than the old one.

In C++ however, if you try to redefine an existing function like this:
```C++
double f(double x)
{
    return 2 * x + 2;
}

double f(double x)
{
    return 2 * x - 2;
}
```
you get an error-message:
```
error: redefinition of ‘double f(double)’
```

However, if you explore this a little, you will find that it is only if you use the same  function signature you get an issue, you can define several functions with the same name, if their inputs differ. This is what we mean by function overloading.

For example, if we wanted to create a function that behaves like the range-function in Python, we could define it as follows
```C++
vector<int> range(int n)
{
    vector<int> v;

    for (int i = 0; i < n; i++)
    {
        v.push_back(i);
    }
    return v;
}
```
Which would give the values $0, 1, \ldots n-1$, just like the `range` function in Python. However, in Python, you could give two arguments: `range(2, 10)`, so let us *also* implement this
```C++
vector<int> range(int start, int stop)
{
    vector<int> v;

    for (int i = start; i < stop; i++)
    {
        v.push_back(i);
    }
    return v;
}
```
We have now implemented two versions of `range`, but because they have a different input, they are considered different functions: `range(int)` and `range(int, int)`. Extending this even further, we could add the third option:
```C++
vector<int> range(int start, int stop, int step)
{
    vector<int> v;

    for (int i = start; i < stop; i += step)
    {
        v.push_back(i);
    }
    return v;
}
```

When we now go to use the `range`-function, we can send in one, two, or three integers, and depending on the input we give, C++ calls the appropriate function definition. We say that the `range` function is *overloaded*. We can go even further. The normal range in Python takes integer input, but `np.arange` takes floats (and returns an array, but we ignore this for now), so let us overload our range function to also take doubles in.
```C++
vector<double> range(double start, double stop, double step)
{
    vector<double> v;

    for (double i = start; i < stop; i += step)
    {
        v.push_back(i);
    }
    return v;
}
```
Note that the number of arguments is the same as before, but because we take doubles in, instead of ints, this is technically a different function.

We can now check all of our functions to see if they behave as expected:
```C++
for (int e : range(5))
{
    cout << e << endl;
}
cout << endl;

for (int e : range(4, 8))
{
    cout << e << endl;
}
cout << endl;

for (int e : range(0, 10, 2))
{
    cout << e << endl;
}
cout << endl;

for (double e : range(0., 1., 0.1))
{
    cout << e << endl;
}
cout << endl;
```

From this example, note that there are two ways of overloading a function:
* Taking a different number of arguments in
* Taking arguments of different types in

Also note that if you are overloading a function, the different "versions" of that function (the different definitions) can pass output of different types.

### Constructor Overloading

The reason we spend time covering function overloading here in the lecture on OOP, is that it is very common to overload the constructor of a class, to give the user different options on how to create instances of the class.

Take our circle for example. Say we want to store the center of the circle as its own struct, then we could make different constructors as follows:
```C++
struct Point
{
    double x;
    double y;
};

class Circle
{
  private:
    double m_radius;
    Point m_center;

  public:
    Circle()
    {
        m_radius = 1;
        m_center = {0, 0};
    }

    Circle(double radius)
    {
        m_radius = radius;
        m_center{0, 0};
    }

    Circle(double radius, double cx, double cy)
    {
        m_radius = radius;
        m_center{cx, cy};
    }

    Circle(double radius, Point center)
    {
        m_radius = r;
        m_center = c;
    }
};
```
By overloading the constructor in this way, we are giving a lot of flexibility in the use of our class. One can create a "default" circle by just writing `Circle circ();`, or you can give a radius, but not a center, or you can give the center as coordinates, or you can send in a struct for the center if you already have one.

### Overloading vs Keyword arguments

In Python, we usually use keyword arguments, or tests on the input to the function, to handle different inputs to the constructor, while in C++, overloading is a common way to do it. Note however that a C++ function or method can also have default arguments, somewhat like keyword arguments in Python. Keyword arguments however, are *named parameters*, which C++ does not support.

### Member initializer lists and default arguments

The above code actually contains a lot of repetitive and we can fix a lot of this by using default arguments as follows

```C++
class Circle
{
  private:
    double m_radius = 1;
    Point m_center{0, 0};

  public:
    Circle()
    {
    }

    Circle(double radius)
    {
        m_radius = radius;
    }

    Circle(double radius, double cx, double cy)
    {
        m_radius = radius;
        m_center{cx, cy};
    }

    Circle(double radius, Point center)
    {
        m_radius = radius;
        m_center = center;
    }
};
```
If not specified we will use `center = Point{0, 0}` and `radius = 1`.
Another common way to initialize a constructor is to use something called a [*member initializer list*](https://en.cppreference.com/w/cpp/language/constructor). Instead of setting the arguments to the construction inside the body of the constructor, we instead write a colon (`:`) followed by the arguments in the order they are defined in the class, i.e
```c++
class Circle
{
  private:
    double m_radius = 1;
    Point m_center{0, 0};

  public:
    Circle()
    {
    }

    Circle(double radius) : m_radius(radius)
    {
    }

    Circle(double radius, double cx, double cy) : m_radius(radius), m_center({cx, cy})
    {
    }

    Circle(double radius, Point center) : m_radius(radius), m_center(center)
    {
    }
};
```
We will not follow this convention strictly in this course, but be aware that this is the preferred way to initialize a constructor when working with modern C++ projects. You can read more about the benefits of using initializer lists [here](https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/).


## Declarations and implementations

Another common pattern that you will see in many C++ project is to separate the declaration from the implementation. We will discuss this in more  details when we discuss [header files and compiling multiple files](cpptools.md).

We can put the declarations on the top of the file

```c++
class Circle
{
  private:
    double m_radius{1.0};
    Point m_center{0, 0};

  public:
    Circle();
    Circle(double radius);
    Circle(double radius, double cx, double cy);
    Circle(double radius, Point center);
    double get_area();
};
```

And then provide the implementation of at the bottom.

```c++
Circle::Circle()
{
}

Circle::Circle(double radius) : m_radius(radius)
{
}

Circle::Circle(double radius, double cx, double cy) : m_radius(radius), m_center({cx, cy})
{
}

Circle::Circle(double radius, Point center) : m_radius(radius), m_center(center)
{
}
double Circle::get_area()
{
    return PI * m_radius * m_radius;
}
```

Note that in order to specify that we mean a method on a class, we use the scope symbol (`::`), so that `Circle::get_area` means the `get_area` method on the `Circle` class. However, even though classes and namespaces are similar in that they can defined scoped methods and variables they are two different concepts. For example `use namespace X` only applies if `X` is a namespace and not a class.

We will see later that it is common to put the declarations in so called header files (ending with `.h` or `.hpp`) and the implementation in source files (ending with `.cpp`)

## A note on structs in C++

In this lecture we have described structs as simple structures that can contain data fields, but not methods. This is how structs behave in C, but in C++ we can do more with them. In fact, in C++, there is little to differentiate a struct from a class, we could also implement methods for our structs, including constructors, as shown here. What separates a C++ struct from a class is simply that its attributes by default will be public, while they for a class by default will be private.

However, because of how structs in the C language, you will most likely see structs used as simple data structures, and classes used for more complicated objects, as this is more of a convention. However, it might be useful to give structs a constructor sometimes.
