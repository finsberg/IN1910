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

The first topic we will cover is *structs*, short for structures, or data structures, more specifically. These are a way of bundling data together in meaningful ways. Put simply, structs are like classes in that we can define our own data types, but unlike classes, structs do not have any *methods*. (Strictly speaking, in C++, structs can have methods, but we ignore this for now.)

One of the major differences between C++ and C is that C++ supports classes. In fact, when Bjarne Stroustrup started the development of C++, he originally called it "C with Classes". While C does not have classes, it does have structs, which is the closest thing to classes in C.

### Defining structs

A struct is a data type we define, and it can be thought of as a data container. We define a struct by specifying what kind of data it should contain as different attributes of the data type. An example could be a position in a 2D plane.
```C++
struct Position
{
    double x;
    double y;
};
```
Another example is a set of parameters for a given modeling system
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
    std::string name;
    int age;
    Date birthday; // Date would be another Struct
    ...
};
```
Note especially the semicolon at the end of the struct definition. In this case, it is required and easy to forget, as we do not use them at the end of function definitions.

### Creating struct instances

After a struct is defined, we can create objects of the new data type as we would with any other object
```C++
Position p;
```
Once we have defined the variable, it is possible to access the data fields the same way as for instances of classes in Python.
```C++
p.x = 1.5;
p.y = 2.2;
```
We can also initialize the struct on creation
```C++
Position p{1.5, 2.2};
```
Notice the order of the input is in the same order as we defined the data fields of the struct.

In addition to creating struct objects, it is possible to create functions that take the structs as input or output. We could, for example, define a function that finds the distance between two points in the plane
```C++
double distance(Position a, Position b)
{
    double dx = (a.x - b.x);
    double dy = (a.y - b.y);
    return std::sqrt(dx * dx + dy * dy)
}
```
Where `std::sqrt` is included from the `<cmath>` standard header.

Similarly, a function can be made to return a struct
```C++
Position origin()
{
    Position tmp{0, 0};
    return tmp;
```

Unlike Python, C++ functions cannot return more than one variable, so structs are a useful way to return more data from a function by wrapping them into a useful data structure. The other common way to "return" multiple variables is to do a call by reference, as discussed in [Arrays, References, Pointers](arrays_and_pointers.md).


### Example: function solving vertical throw with air resistance

We return to the vertical throw example, solving the ODE system

$$
    \frac{{\rm d}v}{{\rm d}t} = -m g - D |v| v,
\qquad
    \frac{{\rm d}y}{{\rm d}t} = v.
$$

We now want to implement a function that solves this ODE system and returns vectors for the solutions $t$, $v$, and $y$. We use a struct to bundle these together and return them

```C++
const double G = 9.81;

struct Solution
{
    std::vector<double> t;
    std::vector<double> v;
    std::vector<double> y;
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

### Unimportant detail: the semicolon

The reason we need a semicolon at the end of a struct definition (as opposed to functions/tests/loops) is that it is possible to declare instances of the struct as they are defined, as below
```C++
struct Position
{
    double x;
    double y;
} p, q;
```
This is a small shortcut one can take when defining a struct that will be used right away. It is, however, important to consider readability when using this syntax.


## Classes

To define a new class in C++, we use the `class` keyword, much like in Python. A major difference from Python, however, is that it is necessary to declare all attributes of the class and their types explicitly. This is done much like shown for structs: we define the variables inside the class definition
```C++
class Circle
{
    double radius;
    double cx;
    double cy;
};
```
However, any attribute defined in this manner will become a *private* variable, meaning it cannot be accessed from outside the class. Trying to read or change the variable would simply return an error as below
```C++
Circle s;
s.radius = 10;
```
Would return
```
error: ‘double Circle::radius’ is private within this context
```
Therefore, when defining a C++ class, we explicitly state which attributes (both data fields and methods) should be private and which should be public. We do this by specifying all public attributes in their own public block as follows
```C++
class Circle
{
  public:
    double radius;
    double cx;
    double cy;
};
```
Any attribute, be it a data field or a method, declared under the `private` block will throw an error if used from outside the class. The attributes declared under the `public` block, however, can be freely accessed and used outside the class.

We can now create objects of the class and set their attributes
```C++
Circle s;
s.radius = 2;
s.cx = -0.5;
s.cy = 0.5;
```
It is equally possible to initialize the object as shown for structs
```C++
Circle s{2, -0.5, 0.5};
```
We will soon discuss how to define constructors for the class, which gives more control when creating class instances.

### Declaring Methods

In analogy to Python, a class method is declared in C++ by simply defining a function inside the class definition.
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
In this example, note that the function is declared as it is usually done outside classes, starting with the return type and then specifying the input argument with a type. Because the above method is public, it can be called from outside the class
```C++
Quadratic f{1, 2, 1};
std::cout << f.evaluate(3) << std::endl;
```

An alternative way to do this, which is more common for larger projects, is to only declare the signature of the function and write the implementation elsewhere. One example of this can be seen below

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
Notice that in this case, we need to tell the compiler that the implementation for the `evaluate` method is provided on the class `Quadratic`, using the notation `Quadratic::evaluate`. Also, in the `double evaluate(double);` declaration, we do not need to provide a name for `evaluate`'s argument (although it is not wrong to do so).


### Implicit self-reference

Another important thing to notice from the `Quadratic.evaluate` example is that there is no `self` argument in the method like there would be in Python. This is because C++ has an implicit self-reference system. Consequently, any attribute that is defined within the class can be used without having to refer to any `self.`. For example, we just use `a`, `b` and `c` freely. Likewise, other methods can be referred to in the class simply by using their names.

Whenever a reference to the object itself is needed, it can be done through the keyword `this`, which is a pointer to the object's address. It is not required, however, to take the keyword `this` explicitly in the function definitions. Note that `this` in C++ is rarely used because of the implicit self-reference to attributes.

### Defining a constructor

In Python, the special method `__init__` is used to define the constructor. In C++, there is a similar special method that defines the constructor of the class. This method's name is the same as the name of the class, and we specify the method without giving it any type (not even `void`)
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
The defined constructor sets the radius according to the given value, while the coordinates of the circle's center are set to 0. Note that we made the constructor public but the data fields private. Indeed, we want to set the radius on creation while not wanting other users to go in and tamper with them afterward. Also, `PI` is neither defined in C++ nor in a standard header, so we define it outside the class as `const double PI = 3.14159265;`.


To create an instance of the class using the constructor, we do as follows
```C++
Circle s(4);
```
If this syntax seems confusing, it can be helpful to compare it to how we would do it in Python
```Python
s = Circle(4)
```
In both cases, the same information is used. Nonetheless, the approaches differ in the order and the fact we skip the `=` sign in C++.

After creating the object, it can be used as
```C++
std::cout << s.area() << std::endl;
```
However, we cannot access the radius or the center directly, as these are private variables.

### Why privacy?

At this point, one might be questioning the usefulness of declaring variables and methods as private. After all, why should the use and change of variables be *restricted* from outside the class? It comes down to *encapsulation*, one of the fundamental concepts of object-oriented programming.

Encapsulation is about hiding away the implementation details and data, only revealing an easy-to-use interface to the outside world. By defining attributes as private, we are performing *data hiding*, making it explicit what the users of the class are and are not meant to interact with.

There is also an element of control and safety in declaring variables as private. By making it impossible to change certain variables from outside the class, we are "fool-proofing" the implementation. In Python, this is done by naming variables with a leading underscore (`self._radius`), but nothing prevents someone from changing these variables and perhaps producing erroneous results. In C++, however, specifying variables as private guarantees they are not tampered with.

### Getters and Setters

While it is useful to make it impossible for a user to change a given variable, sometimes it is necessary to at least give read permission. For the above Circle example, it could be necessary to *read* the radius value. By setting the variable as private, this would not be possible.

It is then common to define a get-method, nicknamed "getter". A get-method is called from outside the class and asks the class to "get" some information from inside. Sometimes, a get-method has to do some calculation or data manipulation to find the desired values; other times, it is just reading and returning a private variable.
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
Declaring `radius` to be private while also defining a public method that returns its value means the circle's radius can be read but not set. This is an example of a get-method. Notice that the method does not need to have the word "get" in its name, but it is widespread to do so.

Similarly, it is common to define "setters": methods used for *setting* private variables. It is reasonable, at this point, to question the usefulness of defining a getter and setter instead of making the variable private. One advantage of the former over the latter is that setter methods can be used to change multiple variables at once, as follows
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
Another possibility is to use setter methods to do data validation of the input. Suppose we want to disallow negative radii or set some upper limit on the possible radius values. This can be done as follows
```C++
class Circle
{
  private:
    double MAX_RADIUS = 1e4;
    double radius;
    ...

        public : void
                 set_radius(double r)
    {
        if (r < 0)
        {
            throw std::invalid_argument("negative radius not allowed");
        }
        else if (r > MAX_RADIUS)
        {
            throw std::invalid_argument("radius exceeds maximum");
        }
        radius = r;
    }
};
```
The `set_radius` method now checks the input; if it is not acceptable, an exception is thrown (similar to raising an exception in Python). Here we are using a `std::invalid_argument` exception.

Defining setters and getters like this is very common in C-style languages like C++ and Java. In Python, although this is equally feasible, there are more efficient and elegant alternatives that rely on using properties. C++ and Python have slightly different ways of organizing classes and methods.

## Function Overloading

In C++, functions can be *overloaded*. This means giving multiple functionalities to one function. To describe how this works, first recall that in Python, a function can be *redefined* whenever necessary.

```{code-cell} python
def f(x):
    return 2 * x + 2


print(f(2))


def f(x):
    return 2 * x - 2


print(f(2))
```

Here, we created a new function, and the name `f` now refers to this new function, rather than the old one.

In C++ however, trying to redefine an existing function incurs an error, as shown below
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
The following error is returned
```
error: redefinition of ‘double f(double)’
```

However, this issue only appears when using the same function signature. It is possible to define several functions with the same name, given that their inputs differ. This is what we mean by function overloading.

For example, if we wanted to create a function that behaves like the `range` function in Python, we could define it as follows
```C++
std::vector<int> range(int n)
{
    std::vector<int> v;

    for (int i = 0; i < n; i++)
    {
        v.push_back(i);
    }
    return v;
}
```
Which would give the values $0, 1, \ldots n-1$, just like the range function in Python. However, in Python, range can be given two arguments: `range(2, 10)`. Therefore, let us *also* implement this as follows
```C++
std::vector<int> range(int start, int stop)
{
    std::vector<int> v;

    for (int i = start; i < stop; i++)
    {
        v.push_back(i);
    }
    return v;
}
```
We have now implemented two versions of `range`, but because they have different inputs, they are considered different functions: `range(int)` and `range(int, int)`. Extending this even further, we could add the third option of having a step
```C++
std::vector<int> range(int start, int stop, int step)
{
    std::vector<int> v;

    for (int i = start; i < stop; i += step)
    {
        v.push_back(i);
    }
    return v;
}
```

When we now use the `range` function, we can send in one, two, or three integers, and depending on the given input, C++ calls the appropriate function definition. The `range` function is therefore said to be *overloaded* in this case. We can go even further and overload the range function to also take doubles, similarly to `np.arange`, which takes floats (and returns an array, but we ignore this for now).
```C++
std::vector<double> range(double start, double stop, double step)
{
    std::vector<double> v;

    for (double i = start; i < stop; i += step)
    {
        v.push_back(i);
    }
    return v;
}
```
Note that the number of arguments is the same as before, but because we take doubles in, instead of ints, this is technically a different function.

We can now check all of the functions to see if they behave as expected
```C++
for (int e : range(5))
{
    std::cout << e << std::endl;
}
std::cout << std::endl;

for (int e : range(4, 8))
{
    std::cout << e << std::endl;
}
std::cout << std::endl;

for (int e : range(0, 10, 2))
{
    std::out << e << std::endl;
}
std::cout << std::endl;

for (double e : range(0., 1., 0.1))
{
    std::cout << e << std::endl;
}
std::cout << std::endl;
```

From this example, note that there are two ways of overloading a function:
* Taking a different number of arguments in
* Taking arguments of different types in

Also note that when overloading a function, the different "versions" of that function (the different definitions) can pass outputs of different types.

### Constructor Overloading

The reason we spend time covering function overloading when discussing OOP is that it is very common to overload the constructor of a class. This gives the user different options on how to create instances of the class.

Take the circle class, for example. We could decide to store the center of the circle as its own struct, requiring different constructors as follows
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
        m_radius = radius;
        m_center = center;
    }
};
```
By overloading the constructor, we give a lot of flexibility in the use of the class. One can create a "default" circle by just writing `Circle circ();`, one can also give a radius, but not a center, or even give the center as coordinates. A final possibility, in this case, is to send in a struct for the center if the user already has one.

### Overloading vs. Keyword arguments

In Python, we usually use keyword arguments, or tests on the input to the function, to handle different inputs to the constructor, while in C++, overloading is a common way to do it. Note however that a C++ function or method can also have default arguments, somewhat like keyword arguments in Python. Nonetheless, keyword arguments are *named parameters*, which C++ does not support.

### Member initializer lists and default arguments

The above code contains a lot of repetition which can be avoided by using default arguments as follows

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
Another common way to initialize a constructor is to use something called a [*member initializer list*](https://en.cppreference.com/w/cpp/language/constructor). Instead of setting the arguments to the construction inside the body of the constructor, we write a colon (`:`) followed by the arguments in the order they are defined in the class, i.e
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
We will not follow this convention strictly, but it is important to notice that it is the preferred way to initialize a constructor when working with modern C++ projects. More about the benefits of using initializer lists can be checked at [When do we use Initializer List in C++?](https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/).


## Declarations and implementations

Another common pattern in many C++ projects is to separate the declaration from the implementation. We will discuss this in more detail when dealing with [header files and compiling multiple files](cpptools.md).

We can put the declarations of functions on the top of the file

```C++
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

We can subsequently provide the implementation of the function at the bottom.

```C++
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

Note that in order to specify that we mean a method on a class, we use the scope symbol (`::`), so that `Circle::get_area` means the `get_area` method on the `Circle` class. However, even though classes and namespaces are similar in that they can define scoped methods and variables, they are two different concepts. For example, `use namespace X` only applies if `X` is a namespace and not a class.

We will see later that it is common to put the declarations in so-called header files (ending with `.h` or `.hpp`), and the implementation in source files (ending with `.cpp`)

## A note on structs in C++

We have described structs as simple structures that can contain data fields, but not methods. This is how structs behave in C, but in C++ we can do more with them. In fact, in C++, there is little to differentiate a struct from a class, and we could also implement methods for our structs, including constructors, as shown here. What separates a C++ struct from a class is simply that its attributes by default will be public, while for a class they will by default be private.

However, because of how structs are defined in the C language, they are usually used as simple data structures, while classes are used for more complicated objects, as a convention. Nonetheless, it might be useful to give structs a constructor sometimes.
