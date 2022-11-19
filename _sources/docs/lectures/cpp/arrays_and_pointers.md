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

# Arrays, Memory and Pointers

In this lecture we start by looking at arrays, a fundamental data structure in C++. In order to properly understand arrays we need to learn a bit more about memory handling and this leads to our next topic: pointers.


## Arrays

In the previous lecture, we covered the vector data type, which behaves much like a Python list. However, *arrays* are a more lower level and fundamental data structure in C++. You might be familiar with numpy arrays in Python, and while these are based on C arrays (which is why we call them numpy *arrays*), they are also more fancy, with additional built-in functionality. The arrays we will talk about here are a low-level structure, making them fairly "primitive", but also efficient.

### What is an array?

An array is a sequence of elements stored *contiguously* in memory. Contiguously means that each element follows each other directly in memory. Machine hardware can more effectively access and iterate over contiguous memory, making arrays efficient in both speed and size. Because the elements are stored contiguously, an array takes up a given chunk of memory and we cannot generally shrink or expand it, as there is no guarantee that the memory we want to expand into is free. In addition, all elements in an array has to be of the same datatype. While all of these properties might sound restrictive, they are what leads to arrays being so efficient.

To summarize, arrays are:
* A sequence of elements of a single datatype
* Stored contiguously in memory
* Highly efficient
* Size of the array cannot change

### Creating an empty array

Unlike the vector datatype which we covered the previous lecture, arrays are built into C++, and we do not need to include anything to use them. Arrays are actually a C datatype, and a much used one at that.

All elements of an array have to be of the same datatype and the size is fixed, so to specify it, we need to declare the type and the number of elements. We could for example state
```C++
double x[100];
```
Which would create an empty array of *doubles* with 100 elements. Note that we specify the datatype as `double`, although we are actually making an array of doubles, which is apparent from the square brackets.

You might expect that all 100 elements were set to 0, as we just created a new array, but this is not the case. Rather, what happens when we define the array is that the memory required to store the 100 doubles is requested from the system, and this memory is *allocated*, meaning it is made available. However, what is stored in that memory isn't actually changed, so the initial values of the elements is therefore whatever was stored in that memory previously, and so it is effectively random. You can check this yourself by initializing an array, and writing out all the values.
```C++
#include <iostream>

using namespace std;

int main()
{
    int n = 20;
    double x[n];
    for (int i = 0; i < n; i++)
    {
        cout << x[i] << endl;
    }
    return 0;
}
```
Which for a given run on my computer produced
```
6.9138e-310
...
2.12203e-314
```

So if we want an array initialized to all zeros, we need to do so manually. We could for example simply loop over each element and set it to zero:
```C++
int n = 20;
int x[n];
for (int i = 0; i < n; i++)
{
    x[i] = 0;
}
```
Note that the array won't remember it's own "length", and so we actually have to keep track of this ourselves, as there is no length/size method we can use to get the number of elements.

### Initializing an array with specific elements

We can also initialize an array with specific elements by listing them in semicolons like this:
```C++
int primes[] = {2, 3, 5, 7, 11};
```
Here, we do not need to specify the number of elements in the square brackets, because this can be implicitly understood from the number of elements on the right. We could however, specify *more* elements if we knew we would change them later however, for example:
```C++
int primes[100] = {2, 3, 5, 7, 11};
```
This syntax would allocate an array of 100 integers, set the first five to the supplied values, and the remaining ones to 0. Note however that the following might not work
```C++
int N = 100;
int primes[N] = {2, 3, 5, 7, 11};
```

### Using arrays

Working with arrays is like working with most sequences, you can access specific elements by index using square brackets. C++ starts counting at 0. However, arrays are more low-level than the sequences you might be used to, and so there will be no fancy operations available, such as slicing. Another point that might be a bit unusual for you is that an array does not remember its own size, and there is no built in size operator you can use to easily find it either! However it is possible to find the size by computing the amount to memory that is required to store the array using the function `sizeof`. For example
```C++
int primes[] = {2, 3, 5, 7, 11};
int size = sizeof(primes) / sizeof(primes[0]);
```
then `size` would be 5. However, you should be careful with using this syntax when arrays are passed as arguments to functions. In these cases only a pointer (which we will talk about later) to the first element is passed which does not necessarily take up the same amount of memory as the whole array. As a rule of thumb you should also keep track of the size of arrays yourselves.

### Example: Solving an ODE

Let us say we want to solve a coupled set of ODEs in C++ using arrays. Say for example we throw a ball straight up into the air. Assuming a quadratic expression for air resistance, we have

$$\frac{{\rm d}v}{{\rm d}t} = -m g - D v |v|, \qquad \frac{{\rm d}y}{{\rm d}t} = v.$$

To solve this equation we must initialize our parameters and initial conditions
```C++
double m = 0.5;
double g = 9.81;
double D = 0.05;

double y0 = 1.0;
double v0 = 5.0;
```

Next we want to initialize our arrays,
```C++
double dt = 0.01;
int N = 400;

// Initialize an array of size N+1 and set the first element
double y[N + 1];
y[0] = {y0};
double v[N + 1];
v[0] = {v0};
double t[N + 1];
t[0] = {0};
```

And we are now ready to solve the ODE using a for-loop and the Euler-Cromer finite difference scheme:


```C++
for (int i = 0; i < N; i++)
{
    t[i + 1] = t[i] + dt;
    v[i + 1] = v[i] - (m * g + D * v[i] * abs(v[i])) * dt;
    y[i + 1] = y[i] + v[i + 1] * dt;
}
```

This approach is very similar to how we might approach solving ODEs in Python using numpy arrays.
It would be convenient if we could store the ODE results in a file. We can do this using the following program

```c++
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    ofstream ofs{"output.txt"};
    if (!ofs)
    {
        throw runtime_error("Unable to open file");
    }

    double m = 0.5;
    double g = 9.81;
    double D = 0.05;

    double y0 = 1.0;
    double v0 = 5.0;
    double dt = 0.01;
    int N = 400;

    double y[N + 1];
    y[0] = {y0};
    double v[N + 1];
    v[0] = {v0};
    double t[N + 1];
    t[0] = {0};

    for (int i = 0; i < N; i++)
    {
        t[i + 1] = t[i] + dt;
        v[i + 1] = v[i] - (m * g + D * v[i] * abs(v[i])) * dt;
        y[i + 1] = y[i] + v[i + 1] * dt;
        // Save to file
        ofs << t[i + 1] << " " << v[i + 1] << " " << y[i + 1] << "\n";
    }

    return 0;
}
```
Now we can plot the results in python
```Python
import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("output.txt")
fig, ax = plt.subplots()
ax.plot(data.T[0], data.T[1], label="$v$")
ax.plot(data.T[0], data.T[2], label="$y$")
ax.legend()
plt.show()
```

```{figure} ../../figures/solving_ode_example.png
---
height: 300px
name: solve-ode
---
Plot from ODE solve.
```


### Be careful when looping over arrays

One major benefit of using C++ is speed and low level control. For example, running through a for loop in C++ is much faster than in python. However, this speed comes at a cost. Consider the following code


````{tab} C++
```c++
int x[] = {2, 4, 6, 8};
int y[4];
for (int i = 0; i < 8; i++)
{
    y[i] = x[i] * x[i];
    cout << y[i] << " ";
}
```
````
````{tab} Python
```python
x = [2, 4, 6, 8]
y = [0, 0, 0, 0]
for i in range(8):
    y[i] = x[i] * x[i]
```
````

When executing this in python you will get an `IndexError`, saying `IndexError: list index out of range`. This is expected because our index loops from 0 to 7, while the list we are accessing has only a size of 4. However in C++ it might run without any error. When I run this on my computer I get the following output
```
4 16 36 64 -1832894464 1073610756 -1311180279 -691194815
```
In this case we are reading and writing to a part of memory that the program does not own. The program will most likely crash if that part of the memory is used by another program.

When working with C++ arrays we don't have the safety-net that is provided in Python so we need to be a bit more careful. Often it is better to use a `vector`, in which case you could write
```c++
vector<int> x{2, 4, 6, 8};
vector<int> y(4);
for (int i = 0; i < x.size(); i++)
{
    y[i] = x[i] * x[i];
    cout << y[i] << " ";
}
```

### 2D arrays

We can also make arrays with both rows and columns, the approach is similar:
```C++
int u[100][100];
```
Here, `u`, would be a 2D matrix of 100 columns and 100 rows. To access elements, we now use two indices: `u[i][j]`. Note that you cannot do `u[i, j]`, like for numpy arrays.

Unlike numpy arrays and similar, these primitive C arrays are primarily data storage, and do not come with built in linear algebra operations such as matrix multiplication and similar, they are simply efficient ways to store data. If you are using C++ for matrix computations, then using a linear algebra package such as [Armadillo](http://arma.sourceforge.net) might be useful to gain some additional functionality.


## Mutability

### Calling functions in Python: A question of mutability

When you define a function in Python, you are used to creating input that takes different kinds of arguments as input. However, have you ever looked closer at how different kinds of input seem to behave differently depending on what type of variable you send in?

In Python, if you send in an immutable variable into a function, then that variable cannot be changed by that function (there are ways to do it, but in the general sense, it won't change):
```Python
x = 5
black_box(x)
print(x)
```
It does not matter what the function `black_box` is or does, the output of this code will be 5. Let us try a simple example:

```{code-cell} python
def black_box(x):
    x += 5


x = 5
black_box(x)
print(x)
```

You might have expected the program to print out 10, but we see that this is not the case.

In Python, variables are references to underlying objects. And when we call the function, we have to variables referring to the same object, both are called `x` (which might be a bit confusing), but one is defined in the main scope, and one inside the function. But variables refer to the same underlying int object. When we try to increase that int object by 5 by writing `+= 5`, a new int object is created behind the scenes. This is because `int`s are immutable. The variable `x` inside the function is now changed so that it references the new int object, which has a value of 10. However, the variable `x` in the main scope isn't changed and still references the original, unchanged, object.

Let us draw the situation:

```{figure} ../../figures/call_by_object.png
---
width: 300px
name: call-by-object
---
```


We can go one step further in illustrating this, by printing out the id of the objects. The id is a code each object in Python gets, that will be unique and unchanged throughout its lifetime.

```{code-cell} python
def black_box(x):
    print("Id of x inside function before stmt:", id(x))
    x += 5
    print("Id of x inside function after stmt: ", id(x))


print("Id of x in main before call:        ", id(x))
black_box(x)
print("Id of x in main after  call:        ", id(x))
```

And from this, we see that the x in the main scope, i.e., outside the function, is unchanged by the function call, it is the exact same, unchanged, object. The x inside the function however, first refers to the original int object, but then references another int object.


### Mutable objects

For mutable variables, such as a list object, things are different:
```Python
x = [1, 2, 3]
black_box(x)
print(x)
```
In this case, the list can be changed, or it may not. Let us see a simple example:

```{code-cell} python
def duplicate_list(input_list):
    input_list += input_list


x = [1, 2, 3]
duplicate_list(x)
print(x)
```

So for mutable objects in Python, a function call *can* change the object itself. This can lead to problems for programmers who are not aware of it, but can also be useful in many cases.

What is happening here is again that we have two variables that reference the same underlying object. However, when we now use `+=`, we are actually changing that underlying object, and so when the function call finishes, the outside variable will also have changed, because it refers to the changed list.

We can again check this using `id`:

```{code-cell} python
def duplicate_list(input_list):
    print("Inside function, before: ", id(x))
    input_list += input_list
    print("Inside function, after:  ", id(x))


x = [1, 2, 3]
print("Outside function, before:", id(x))
duplicate_list(x)
print("Outside function, after :", id(x))
```

As you can see, there is ever only one list *object*.


### Using mutators

Say for instance we want to make a function that sorts a list of numbers, we might want the function to produce and return a brand new list, leaving the original untouched, *or*, we might want it to sort the original list in-place. Both of these approaches are reasonable, and possible. In fact, in Python, you get both of these options built in. The built-in function `sorted()` returns a sorted *copy* of the original list, while the list method `.sort()` sorts the list in-place.

```{code-cell} python
x = [4, 1, 0, 5, 3, 2]
y = sorted(x)

print(x)
print(y)
```

```{code-cell} python
x = [4, 1, 0, 5, 3, 2]
y = x.sort()

print(x)
print(y)
```

Where we see that the `list.sort` method returns None, as it sorts the list in-place, and so does not actually need to return anything. Note that the in-place sorting is a list method, so we cannot use it for a tuple for example, which makes sense, because a tuple is immutable, and so *cannot* be sorted in-place.

A general advice is to avoid using methods that mutate objects, especially in function calls. A function that that does not mutate the input arguments, so that the `duplicate_list` function should be written like this

```{code-cell} python
def duplicate_list(input_list):
    return input_list + input_list


x = [1, 2, 3]
y = duplicate_list(x)
print(x)  # x is unchanged
print(y)
```

## Calling functions in C++

In C++, things work a bit differently, and we are given more control over the process. To start of with, in C++, different data types aren't mutable or immutable by nature. Instead, we must declare that a given object is to be immutable as we define it. By default, all objects will be mutable.

### Call by Value

Let us try to create a function that changes an integer *in-place*. We could for example define the following function:
```C++
void halve(double x)
{
    x /= 2;
}
```

However, if we try to use this function, we notice that things don't work exactly like they do in Python:
```C++
int main()
{
    double y = 10;
    halve(y);
    cout << y << endl;

    return 0;
}
```
From what you just learnt about Python, we would expect this program to write out 5 at the end, after all, we have a mutable variable `x` that we assign to 10 and then halve. But if you run this code, you will see that the value of `y` is still 10.

What is happening in this example is that we have created a function that uses what is a **call by value**. This means that when we call the function, what is sent into the function is the *value* of the input-variable, not the input variable itself. This means that inside the function, we have a separate variable, or a "copy" of the original variable. This happens because the variable `x` is instantiated and then the value is set equal to the input variable.

If you define a function in C++ in the manner we have shown so far in this course, it is a call by value, and it will act in this way. We will shortly show you how to define a function that behaves differently, but first, another example.

Call by value is not only in the case of primitive data types, but also for more complex data types, for example vectors. If we want to define a bubble sort for example, we can do it as follows
```C++
vector<int> bubble_sort(vector<int> numbers)
{
    int temp;
    bool changed = true;

    while (changed)
    {
        changed = false;
        for (int i = 0; i < numbers.size() - 1; i++)
        {
            if (numbers[i] > numbers[i + 1])
            {
                temp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = temp;
                changed = true;
            }
        }
    }
    return numbers;
}
```
When looking at this code, it might look like we are sorting the original input list in-place. After all, we are not creating a copy of the original list, like we would need to in Python. However, because the function is a call by value, then the input variable `numbers` inside the function is a separate variable, with the values copied, automatically.

You should verify this yourself, for example by running the following script
```C++
int main()
{
    vector<int> original{2, 4, 3, 0, 5, 1};
    vector<int> sorted = bubble_sort(original);

    cout << "Original" << endl;
    for (int e : original)
    {
        cout << e << endl;
    }

    cout << "Sorted" << endl;
    for (int e : sorted)
    {
        cout << e << endl;
    }

    return 0;
}
```

### Call by Reference

So what is the alternative to a call by value in C++? The alternative is to send in the actual variable itself, and not just the value of it. This is called a **call by reference**, because what you do, is send in a reference to the variable itself.

To better understand this, it's important to understand that things work slightly different in C++ and in Python. In Python, every variable is a reference to an underlying object, while in C++, some variables are objects, and other variables can be references to those variables.

When we define a function, we can use an ampersand `&`, to specify that a variable should be a *reference*, instead of just a value. For example:
```C++
void halve(double &x)
{
    x /= 2;
}
```
If you now repeat the experiment of sending in a number, and then checking, you will find the original actually is halved. This is because the ampersand signifies that we are sending in the *reference* of a double variable, not just the value of one.

Note that because we use a call by reference, the function is changing variables outside of it, despite being a `void` function that does not explicitly return anything. In this manner, call-by-reference is a common way of making functions in C++, as an alternative to actually returning things.

The bubble sort example with call by reference is given in the cell below.
```C++
void bubble_sort(vector<int> &numbers)
{
    int temp;
    bool changed = true;

    while (changed)
    {
        changed = false;
        for (int i = 0; i < numbers.size() - 1; i++)
        {
            if (numbers[i] > numbers[i + 1])
            {
                temp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = temp;
                changed = true;
            }
        }
    }
}
```
In this version of bubble-sort, we are sending in a reference of the list, and not just the value. You can see this because we have added the ampersand (`&`) in the input. Thus we are making actual changes to the original list, in-place. Because we are now sorting in-place, we do not need to return anything, so we remove the return statement and change the type to `void`.


### Multiple variables

Note also that a function can take in multiple variable references. We could for example make a function that swaps the contents of two integers
```C++
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
```
Here we send in the references of two integer objects, and swap their contents (their values). Note that we have to create a temporary integer object inside the function, as we need somewhere to store one number while copying the other. Imagine you have a glass of milk and a glass of juice, and you want to swap their contents, you need a third glass to temporarily store one of the contents.

This swap operations is mostly an example to show you what's possible, but it could for example be useful in the implementation of our bubble-sort! We leave it as an exercise to the reader to go back and improve the bubble-sort in this way.

A function could also easily take in some call-by-value variables, and some call-by-reference. For example:
```C++
void threshold_vector(vector<double> &input, double min, double max)
{
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] < min)
        {
            input[i] = min;
        }
        else if (input[i] > max)
        {
            input[i] = max;
        }
    }
}
```
This function would go through a vector and threshold small and large values according to the given arguments. The following code for example:

```C++
vector<double> numbers{2.2, 1.3, 4.8, 5.6, 1.9, 9.1, 7.2};

cout.precision(1);
cout << fixed;
for (double e : numbers)
{
    cout << e << " ";
}
cout << endl;

threshold_vector(numbers, 2, 8);

for (double e : numbers)
{
    cout << e << " ";
}
cout << endl;
```
Would give the output
```C++
2.2 1.3 4.8 5.6 1.9 9.1 7.2 2.2 2.0 4.8 5.6 2.0 8.0 7.2
```
(Here the use of `precision` and `fixed` is used to make sure it prints one decimal after each number.)

### Small note on call by value vs call by reference

One of the major benefits of using a call-by-reference is that you avoid copying the object you are using as your argument, which can be efficient with regards to both speed and memory. To see why, imagine you are working on some huge vector of data with millions of elements. If every time you call a function to do something with this vector, you had to copy the entire thing, you would use twice the memory and maybe some time for the actually copying of memory. Instead, if you could just call by reference you could read and work on the actual memory where it is stored.

So if call by reference is more memory efficient, why don't we just always use that? While calling by reference is efficient memory wise, it can also lead to side effects a lot more easily, and thus more easily lead to bugs. Most often when calling a function, you do not expect the input argument to be changed, and it would be confusing and hard to find bugs if all functions could change variables at any time. Thus calling by value is a better default, as one should need to be very explicit if one wants to break from the default conventions. Besides, copying simpler objects such as int and doubles has so little overhead it won't be noticeable, it is only for larger, more complex data structures where there is real gain in call by reference.

So to summarize briefly:
* Use call by value:
    * When you do not want functions to alter their input arguments (most of the time)
    * The argument is cheap to copy

* Use call by reference:
    * When you do want your function to alter their input arguments
    * The arguments are expensive to copy


#### Use case: Returning more than one thing

Another use case of call-by-reference is when we want to return more than one thing. Let us say we want to define a function that loops through a vector and returns the minimum and the maximum value found in that vector. In Python you could just find both values, and return them as a tuple:
```Python
return min_val, max_val
```
However, in C++, you cannot actually do this, you can only return a single variable. Instead, you could make the function a void function (not return anything) and instead send in the references for where you want your output to be stored:
```C++
void min_max(vector<double> data, int &min_val, int &max_val)
{
    ...
}
```

```{note}
It is possible to return a [`tuple`](https://www.cplusplus.com/reference/tuple/make_tuple/?kw=make_tuple) or a [`pair`](https://www.cplusplus.com/reference/utility/make_pair/?kw=make_pair) in C++ but this is beyond the scope of what we will cover in this course.
```

### Style guide: Void functions

So far, we have defined a `void` function every time our function changes the input argument, meaning we do not return anything. There is nothing to stop us from *both* returning things, and changing input arguments. However, this is considered bad style, because it can make it very confusing to the user what is actually going on. If a function returns something, it will be assumed that it does not change the input variables. This convention is important to follow, as it can easily lead to bugs when sharing or collaborating on code.

Some beginner programmers like to return things, even when doing call-by-reference. They might for example make a sorting function that sorts a list in-place, but then at the end, for good measure, they also return that list. This is completely unnecessary, and confusing. Make a choice of doing changes to actual input *or* if you are returning something.


### Is Python Call-by-value or Call-by-reference?

A much discussed question is whether Python is call-by-value or call-by-reference. Some claim it is call-by-value, others that it is call-by-reference. Hopefully, after reading through this lecture, you will realize that it actually is a sort of mix. When calling a function with an immutable variable, Python behaves as call-by-value, while if the input is mutable, then it is more like call-by-reference. Most often, people describe Python by stating that it is call-by-object. There is a [great talk by Ned Batchelder](https://nedbatchelder.com/text/names1.html) that you can watch yo learn more about this.


## Immutability in C++

Earlier we briefly mentioned that in C++ data types are not mutable or immutable in the same manner as in Python, instead we can declare any variable to be immutable when we define it. To do so, you can use the keyword `const`, short for "constant". The term constant is perhaps more descriptive than immutable, but the two mean the same, the object cannot change over time, it is constant.

You can for example define a constant integer as follows
```C++
const int MAX_ITERATIONS = 130;
```
After defining such a variable, we won't be able to change it. Therefore, you should initialize it to whatever value it should have at creating, as you won't be able to set that value later. If we do try to change it:
```C++
MAX_ITERATIONS++;
```
You would get an error message when compiling:
```
error: increment of read-only variable ‘MAX_ITERATIONS’
```
The exact error message would depend on your compiler.

Using the const keyword can for example be useful to define parameters or constants you know you need to set once, and won't need to be changed after compilation.

The const keyword can also be used when defining a call-by-reference, when you want to pass in large, complex data to a function in an efficient way, but you do not actually want the data to be changed, just read. You could for example create the following function:
```C++
double standard_deviation(vector<double> const &data)
{
    ...
}
```
This function takes in a vector by reference, so we avoid copying it. However, we only want to calculate the standard deviation and return it, so we do not actually expect to change any of the contents of the vector itself. We therefore add the `const` keyword to the argument input.

Note that the `const` keyword isn't really *needed*, but we add it for two important reasons. First of it makes our code more understandable, as when someone reads the function signature, they immediately see that the data input isn't changed, despite it being a call-by-reference. And secondly, it is a safeguard against bugs, because having the const keyword, making a change to the actual vector will cause a compile error. This is a good thing: trustworthy and reliable code should fail rather than return wrong results.

## Reference Variables

So far we have discussed doing call by reference. By adding the ampersand in a function signature, we denote we want to refer to a variable's *reference*:
```C++
void swap(int &a, int &b)
{
    ...
}
```
Note that it's possible to create *reference variables* outside of function definitions in the same manner
```C++
int a = 5;
int &b = a;
```
Here we create an integer `a`, and then create a reference variable `b`, `b` is just a reference to `a`. Effectively we have just made a new name for our variable, a process known as *aliasing* (the word "alias" meaning an alternative name in this context).

Notice that, just like with call by reference we see that if we change the value of `b` and `b` is a reference to `a`, then  the value of `a` will also change
```c++
int a = 5;
int &b = a;
b += 1;
std::cout << "a = " << a << ", b = " << b << std::endl;
// Will output 'a = 6, b = 6'
```

Because a reference is just an alias for an existing variable, we cannot create a reference variable that doesn't refer to anything. If you just write
```C++
int &my_reference;
```
The compiler would protest:
```
error: ‘my_reference’ declared as reference but not initialized
```

While reference variables can be made in this way, and there surely are some cases where it might be useful, this is rarely done in practice in C++. Rather, reference variables are mostly defined in function signatures, so that they are initialized when a function is called, as seen in our call-by-reference examples.

## Pointers

We now turn to a different kind of variable, that have several things in common to a reference variable, the pointer. A pointer is, as the name implies, a variable that points at something.

To create a pointer variable, we add an asterisk to a data type
```C++
int *x;
```
In this case, `x` will not be an integer, but a pointer variable that points to an integer. Technically speaking, it is a variable where the value is a memory address to an integer object.

After creating a pointer variable, it won't be pointing at anything (will explain this later). To get it to point to something, we have to store the address of some specific integer:
```C++
int *x;
int a;

x = &a
```
Here the final statement sets the value of our pointer (`x`) to be equal to our integer variable. Note that we use the ampersand (`&`) to find the address of a variable. The ampersand is sometimes referred to as the "address-of" operator for this reason. From this syntax, due to the use of the ampersand, we can see that the pointer stores a reference to `a`.

At this point, it might feel very unclear what the difference between a pointer and a reference is. This confusion is to be expected, as these concepts are very abstract and generally considered one of the trickier parts of C++ for beginners to understand. The two are also very similar, which doesn't help things now.

## Pointer vs reference variable

To make discussion a bit easier, let us create some different variables:
```C++
int a = 10;
int &b = a;

int x = 20;
int *y = &x;

int *z;
```
Here, `a` is an integer variable, and `b` a reference variable to `a`. Similarly, `x` is an integer, and `y` an integer-pointer, pointing at the address of `x`.

Whereas `b` is more or less just an alias, or alternative name, for `a`, the pointer `y` is more of a variable in its own right, that contains a value with the address to `x`. For one, we can create a pointer variable that doesn't point at anything, which we do in `z`, recall that this is not possible for a reference.

```{figure} ../../figures/ref_vs_pointer.png
---
width: 400px
name: ref-vs-pointer
---
A reference variable is an alias for another variable, while a pointer is a variable that stores a memory address as a value, and can thus point at something.
```

Because a reference is just an alias, we can use a reference variable as though it was the actual object we want to change, we could now for example do:
```C++
b += 5;
```
Which would change `a`. We can verify this by printing out both `a` and `b`:
```C++
cout << a << endl;
cout << b << endl;
```
And we see both have become 15.

For the pointer variable however, `y` refers to the pointer variable itself, so if we just do
```C++
y += 5;
```
Then we are actually changing the pointer variable, and *not* the variable it is pointing too. If we try to print out both `x` and `y` now, we get the following:
```C++
cout << x << endl;
cout << y << endl;
```
Result:
```
20
0x7ffc4258e59c
```
So we see that trying to change `y` directly does not impact `x`, and furthermore, if we try to print out `y` directly, we get the pointer value, i.e., the address, not the integer it is pointing at.

The major point we are trying to get to is that a reference variable is a simple alias/additional name for an object, which is useful when defining and using functions with a call-by-reference. But pointers are more variables in themselves, with their own value and can exist without anything to point at.

### The Dereference Operation

So if we cannot use a pointer to directly affect the variable it points at, what is it good for? While we cannot use it *directly*, we can use the *dereference operator* to get the variable it points at. This is done as follows
```C++
*y += 10 : cout << x << endl;
cout << *y << endl;
```
By putting an asterisk (`*`) before a pointer variable, we *dereference* the pointer and can interact with whatever the pointer is pointing at. The term itself is perhaps not very well named, but just remember that the pointer and the pointee are two different things! For the dereference operator to work properly, a pointer needs to know what kind of data it is pointing at, which is why we have to create an *integer pointer*, or a *vector pointer*, and so on. Why does the pointer need to know what it is pointing at? Well this will be clear later, but what we can say now is that when we store arrays in memory, the values will lie contiguously in memory, meaning that the memory addresses for `x[i+1]` will be next to the memory address of `x[i]`. That way we can actually use points it iterate through an array. But more on this later. Here is a table summarized the concepts so far.

| Syntax    | Meaning               |
|--------	|---------------------	|
| `int i`  	| integer variable    	|
| `int &r` 	| reference variable  	|
| `int *p` 	| pointer variable    	|
| `&i`     	| get address of something |
| `*p`     	| content of address/pointer |


## Null-pointers

So far, we have stated several times that a pointer does not need to point at something. Let us justify this statement somewhat.

Think of an integer, or a double, for a second. If we define these variable, but do not initialize them to any value:
```C++
int x;
double y;
```
What value does these variables have? The statement allocates memory to store these variables, and the given piece of memory for these variable has to be in some *state*, meaning these variables has to have some value, they cannot just be "empty". In C++, the value of these will effectively be random if we do not set them.

Similarly, a pointer is a variable that stores a memory address. When we define a pointer, memory for storing that memory address is allocated. So in the same manner as the other variables, the pointer has to have some value. So when we say the pointer doesn't point at anything, we do not mean it doesn't have any value, instead we mean it has the value "null".

Basically, null is a value we reserve to mean "pointing at nothing". By pointing our pointers at null, we are telling the compiler (and ourselves), that the pointer is not pointing at anything, it is rather, pointing at nothing.

Before C++11, it was common to refer to null as `NULL`. So if you wanted to "reset" a pointer for example, you would do it as follows:
```C++
int *x = &a;
x = NULL;
```
After C++11, this should still work, but C++11 also introduced the `nullptr`, which is the more modern way of doing things:
```C++
int *x = &a;
x = nullptr;
```
We can check whether a pointer is pointing at an actual object with a simple if-test
```C++
if (x == nullptr)
{
    ...
}
```


## A comment on style

So far we have defined reference and pointer variables by putting special characters next to the variable name, like so:
```C++
int *x vector<int> &primes
```
However, as usual, the whitespace is again arbitrary, so we could just as well have written
```C++
int *x vector<int> &primes
```
and some people prefer this at it looks like the character is referring to the datatype, which can be helpful. The downside to doing this if you are used to defining multiple variables on one line. You can for example do the following in C++:
```C++
int i, j, k;
```
which is equivalent to
```C++
int i;
int j;
int k;
```
However, if you do this with a pointer:
```C++
int *p, q, r
```
Only `p` would be a pointer, not q and not r, which would be normal integers. By instead writing
```C++
int q, r, *p
```
this is more clear. Which is why some prefer the first form.

However, confusions like this is one reason why many style guides state that one should avoid combining multiple definitions in the first place, as it would be more readable to just split it over multiple lines.

Lastly, some prefer to put a space on both sides of the special character:
```C++
int *x vector<int> &primes
```
Whatever style you prefer, be consistent!


## Call by pointers

We started of by showing you call-by-reference using reference variables, but you can achieve the same thing by using pointers
```C++
void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}
```
Note that we need to refer to `*a` and `*b` to actually use the variables (dereference). Similarly, when calling this function, we would need to send in actual integer pointers, or the address of integer variables (which can be gotten with the address-of operator):
```C++
int a = 100;
int b = 300;
swap(&a, &b);
```
Some refer to this as doing call-by-pointers, but most just consider this a type of call-by-reference.

Using pointers over references in a function call like this might seem like a lot of additional boilerplate compared to just using reference variables, and in many cases it might be, but if you are working with pointers, then using call-by-pointers makes more sense.
