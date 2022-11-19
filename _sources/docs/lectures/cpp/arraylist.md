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

(arraylist)=
# Dynamic Arrays aka Array Lists

We now turn to something different, where we use what we have learned in C++ so far, to implement a data structure.

In Python you are used to using lists, but have you ever thought about how they actually work, behind the scenes? In C++, we claimed a similar object is the *vector*. What we will do now, is assume that python lists/c++ vectors do not exist, and instead build our own from the bottom up.

To make such "list" objects, we will use a technique called *dynamic arrays*, not to be confused with dynamically allocated arrays, which is what we discussed earlier. An alternative name is *array lists*, because we will be using arrays to create a list class.

## Arrays with variable size

One of the most important things we want to be able to do to our list objects, is append new elements to them. However, in C++, arrays are created with a certain size, and once created, cannot change size. So how could we possible append elements to this array?

We cannot resize an array, but we will *fake* it, using some clever encapsulation. When allocating the array, we simply make it much bigger than what we want to store, that way, we have extra memory reserved when we want to append additional elements.

Inside the class, we store the actual data array we use (which is static in size) in a pointer variable called `_data`. We also store a private variable `_capacity`, that is a measure of how long the actual array is. We also have a `_size` variable, that denotes how many elements are actually stored in the array and that can be read using the method `length` . From the outside, the array will look like it is this big.

```C++
class ArrayList
{
  private:
    int *_data;
    int _capacity;
    int _size;

  public:
    int length()
    {
        return _size;
    }
```

Note that we will use the convention that all private variable and methods will will have a name starting with an underscore (`_`), which is the same convention that we are used to from Python.

By default we set the capacity to a large number (say 1000), and the size should be zero, and we can therefore add these default values directly in the class as follows

```C++
class ArrayList
{
  private:
    int *_data;
    int _capacity = 1000;
    int _size = 0;

  public:
    int length()
    {
        return _size;
    }
};
```

## Constructor and Destructor
We now make the constructor where we will allocate the required memory for our Array list using the `new` keyword.
```C++
ArrayList()
{
    _data = new int[_capacity];
}
```
Whenever we write `new` in our code we need to remember to add a `delete`, otherwise we will get a memory leak. We will do this in the destructor.
```C++
~ArrayList()
{
    delete[] _data;
}
```

### Testing the constructor

Now is a good time to compile the program into an executable and make sure that it behaves as expected. We should also make sure that we can create an `ArrayList` and we can also check that the `length` is zero. We can do so in a separate function that is called from the `main` function.

```c++
#include <cassert>

void test_empty_array_has_length_zero()
{
    ArrayList a{};
    assert(a.length() == 0);
}

int main()
{
    test_empty_array_has_length_zero();
}
```
Here we create a function called `test_empty_array_has_length_zero` where we first instantiate an empty `ArrayList` named `a` and asserts that the length is zero.
Note that we have included `cassert` where the `assert` function is defined. See {ref}`cpp-testing` for more info about testing in C++.

Assuming that all your code is written in a single file called `array_list.cpp` you can compile it into an executable called `array_list` by executing the following command
```
c++ -std=c++14 array_list.cpp -o array_list
```
This will create a new file called `array_list`. You can run the program by executing the file
```
./array_list
```
In this case there will be no output, but you can of course add some printing to indicate that your test ran successfully, e.g
```c++
#include <iostream>

void test_empty_array_has_length_zero()
{
    ArrayList a{};
    std::cout << "Test that empty array has length zero\n";
    assert(a.length() == 0);
    std::cout << "Success!\n";
}
```

```{admonition} Click to see the full source code
:class: dropdown

```c++
// array_list.cpp
#include <cassert>
#include <iostream>

class ArrayList
{
  private:
    int *_data;
    int _capacity = 1000;
    int _size = 0;

  public:
    int length()
    {
        return _size;
    }

    ArrayList()
    {
        _data = new int[_capacity];
    }

    ~ArrayList()
    {
        delete[] _data;
    }
};

void test_empty_array_has_length_zero()
{
    ArrayList a{};
    std::cout << "Test that empty array has length zero\n";
    assert(a.length() == 0);
    std::cout << "Success!\n";
}

int main()
{
    test_empty_array_has_length_zero();
}
```

(array-list-two-files)=
## Adding you tests in a separate test file
Before continuing we will try to organize the code a bit better by putting the class declaration in one file called `array_list.cpp` and the tests in another files called `test_array_list.cpp`.

In {ref}`cpp-header-files` we discuss how to compile multiple files together. In that section we also discuss the usage of header files. While you are more than welcomed use header files, we will not enforce it and in this example we will not use header files for the sake of simplicity.

Create new file called `test_array_list.cpp`. Move the function `test_empty_array_has_length_zero` and the `main` function from `array_list.cpp` to this new file so that `array_list.cpp` look as follows

```c++
class ArrayList
{
  private:
    int *_data;
    int _capacity = 1;
    int _size = 0;

  public:
    int length()
    {
        return _size;
    }

    ArrayList()
    {
        _data = new int[_capacity];
    }

    ~ArrayList()
    {
        delete[] _data;
    }
};
```

and `test_array_list.cpp` look as follows
```c++
#include <cassert>
#include <iostream>

#include "array_list.cpp"

void test_empty_array_has_length_zero()
{
    ArrayList a{};
    std::cout << "Test that empty array has length zero\n";
    assert(a.length() == 0);
    std::cout << "Success!\n";
}

int main()
{
    test_empty_array_has_length_zero();
}
```
Note that we have also added the line

```c++
#include "array_list.cpp"
```
which will basically import all the content from `array_list.cpp` into `test_array_list.cpp`.

In {ref}`cpp-compilation-linked` you can read more about how to compile multiple files together. When you have the declarations in a separate header file, you need to first compile the individual files into separate object files and link them together. However if you do include the `cpp` file directly like we do in this example, you don't need to compile the the individual files separately, and you should be able to simply create an `array_list` binary using the command
```
c++ test_array_list.cpp -std=c++14 -o array_list
```

## Appending
Next we add a public method for appending a new element to our list. When we append an element, we want it to go to the first unused location in our storage array, this will be `_data[_size]`, because the indices $0, 1, \ldots, n-1$ are used for actual storage. However, if we go over our allocated capacity we are in danger, so we should check for this explicitly:
```C++
void append(int n)
{
    if (_size >= _capacity)
    {
        throw std::range_error("Capacity full");
    }
    _data[_size] = n;
    _size++;
}
```
Here we will throw a `range_error` exception if capacity size exceeds the capacity. Note that to use this you might also need to include the following line in your file
```c++
#include <stdexcept>
```
Now we can append elements to our list, and they will be stored in the underlying array. As long as we do not go over our initially allocated capacity, everything works fine.


## Getting
We will also need to have some way of accessing the stored elements, as they are stored in a private array. We define a getter. This getter takes the index of the element you want, and sends a reference to the entry back, so that the variable can be changed if desired:
```C++
int get(int index)
{
    if ((index < 0) || (index >= _size))
    {
        throw std::range_error("Index is out of bounds");
    }
    return _data[index];
}
```
Note that we explicitly check if the index is out of bounds and if it is we throw a range error. The user should not be able to access the part of the storage array that is not filled.

## Testing `append` and `get`

We should now verify that the `append` and `get` methods are working as expected. We will do this by implementing a test function called `test_append_and_get` in `test_array_list.cpp` which could look as follows:
```C++

void test_append_and_get()
{
    ArrayList a{};
    a.append(42);
    a.append(43);
    assert(a.length() == 2);
    assert(a.get(0) == 42);
    assert(a.get(1) == 43);
}
```
Running this from the main function should result in no output (you are of course welcomed to print some message to the console saying that the test passed).

## Printing the array

It would be convenient to add method that prints the element of the array. We can do so by implementing a `print` method as follows
```C++
void print()
{
    std::cout << "ArrayList([";
    for (int i = 0; i < _size - 1; i++)
    {
        std::cout << _data[i] << ", ";
    }
    std::cout << _data[_size - 1] << "])\n";
}
```
Remember that we also need to add the line
```c++
#include <iostream>
```
at the top of the file.

## Adding a new constructor

Instead of having to append all the elements to an empty array, we can instead overload the constructor to take in some initial data if desired:
```C++
ArrayList(std::vector<int> values)
{
    if (_capacity < values.size())
    {
        _capacity = values.size();
    }
    _data = new int[_capacity];
    for (int value : values)
    {
        append(value);
    }
}
```
Note that we also check that if the size of the input array is larger than the capacity, then we increase the capacity to be of the same size as the input array. Remember to also add the line
```c++
#include <vector>
```
at the top of the file.

We should also create new test that make sure that the new constructor is working as expected. For example the following test function
```C++
void test_vector_constructor()
{
    ArrayList a{{1, 2}};
    assert(a.length() == 2);
    assert(a.get(0) == 1);
    assert(a.get(1) == 2);
}
```

(array-list-indexing)=
## Indexing

While our `get` method works well for getting out the specific elements, we would like to be able to index specific elements in the same way as in a python, i.e we would like to do the following to read a variable
```c++
ArrayList a{{1, 2}};
std::cout << "a[0] = " << a[0] << "\n"; // a[0] = 1
```
and we would also like to be able to update the array using the same notation, i.e
```c++
a[0] = 42;
std::cout << "a[0] = " << a[0] << "\n"; // a[0] = 42
```
This we can implement by overloading the `[]` operator. This is like a Python special method, by using a specific name, we can redefine the behavior of square bracket indexing.
```C++
int &operator[](int index)
{
    if ((index < 0) || (index >= _size))
    {
        throw std::range_error("Index is out of bounds");
    }
    return _data[index];
}
```
Note that, unlike `get`, we now return a reference variable (`int&`), which means that we should be able to use this method to both read and write to the array. Lets us also add the following test to `test_array_list.cpp`

```c++
void test_indexing_operator()
{
    ArrayList a{{1, 2}};
    assert(a[0] == 1);
    assert(a[1] == 2);
    a[0] = 42;
    assert(a[0] == 42);
}
```

## Capacity Issues

We have so far created a class that from the outside acts much like a `vector<int>` object, in that we can append new integers to it, and interact with it using indexing. It also remembers its own size which we can read out through the `length` function. However, our implementation has some issues, namely the fixed capacity.

The number 1000 was completely arbitrary, and can create issues in either direction. Say we want to create a list with several million elements, this would not work. On the other hand, say we want to create thousands of lists of only a handful of elements, this would be horribly inefficient, as every single list would take up a large chunk of unused memory.

## Dynamic resizing

To get around these issues, we need to be able to *adjust the capacity* as needed. Let us start of with a smaller capacity, say 1:
```C++
class ArrayList
{
  private:
    int *_data;
    int _capacity = 1;
    int _size = 0;

  public:
    ArrayList()
    {
        _data = new int[_capacity];
    }
    ...
};
```
Now we will hit our max capacity much sooner, but when this happens, instead of throwing an error, we will *resize* our capacity.
```C++
void append(int n)
{
    if (_size >= _capacity)
        resize();
    _data[_size] = n;
    _size++;
}
```
But how can this `resize` method work? After all, we are not allowed to change the size of the underlying storage array. What we can do however, is create a brand new storage array of larger capacity, and copy all the stored values over to the new array. Let us double the capacity every time we resize:
```C++
void resize()
{
    _capacity *= 2;
    int *new_data = new int[_capacity];
    for (int i = 0; i < _size; i++)
    {
        new_data[i] = _data[i];
    }
    delete[] _data;
    _data = new_data;
}
```
Here we first create a new storage array with a new the capacity that is twice as large as the original one, called `new_data`. The choice of doubling the capacity is arbitrary, and you could imaging having a different *growth factor* than 2.

Next we copy over all the stored values to the new array. Then we delete the old storage array, to free the memory, as it was dynamically allocated. Lastly, we point the `_data` pointer to the new storage array.

The resizing fixes both of our problems with our original implementation. As our initial capacity is so small it takes next to no space, we can make many short lists without issue. And if we want to make a very long list, the list will resize automatically, behind the scenes, without our user having to think about it whatsoever.

Also note that the `resize` method is not something user should need to care about, and therefore we can add this as a private method.

```{admonition} Click to see the full source code
:class: dropdown

```c++
// array_list.cpp
#include <iostream>
#include <stdexcept>
#include <vector>

class ArrayList
{
  private:
    // Array containing the actual data in the list
    int *_data;
    // Capacity of the array
    int _capacity = 1;
    // Size of the array
    int _size = 0;

    /**
     * @brief Resize array with a growth factor of 2.
     * Copy all elements of the original array over to
     * the new array and delete the old array.
     *
     */
    void resize()
    {
        _capacity *= 2;
        int *new_data = new int[_capacity];
        for (int i = 0; i < _size; i++)
        {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
    }

  public:
    // Default constructor
    ArrayList()
    {
        _data = new int[_capacity];
    }

    // Constructor for a list of values
    ArrayList(std::vector<int> values)
    {
        if (_capacity < values.size())
        {
            _capacity = values.size();
        }
        _data = new int[_capacity];
        for (int value : values)
        {
            append(value);
        }
    }

    // Destructor
    ~ArrayList()
    {
        delete[] _data;
    }

    // Length of array
    int length()
    {
        return _size;
    }

    /**
     * @brief Append element to the end of the list
     *
     * @param n The value to be appended
     */
    void append(int n)
    {
        if (_size >= _capacity)
        {
            resize();
        }
        _data[_size] = n;
        _size++;
    }

    /**
     * @brief Get value at a given index.
     * Throws a range error in index if out of bounds
     *
     * @param index The index
     * @return int The value at that index
     */
    int get(int index)
    {
        if ((index < 0) || (index >= _size))
        {
            throw std::range_error("Index is out of bounds");
        }
        return _data[index];
    }

    /**
     * @brief Prints the array
     *
     */
    void print()
    {
        std::cout << "ArrayList([";
        for (int i = 0; i < _size - 1; i++)
        {
            std::cout << _data[i] << ", ";
        }
        std::cout << _data[_size - 1] << "])\n";
    }

    /**
     * @brief Get a reference to the value at a given index.
     * Throws a range error in index if out of bounds
     *
     * @param index The index
     * @return int The value at that index
     */
    int &operator[](int index)
    {
        if ((index < 0) || (index >= _size))
        {
            throw std::range_error("Index is out of bounds");
        }
        return _data[index];
    }
};
// test_array_list.cpp
#include <cassert>
#include <iostream>

#include "array_list.cpp"

/**
 * @brief Test that an empty array list has length zero
 *
 */
void test_empty_array_has_length_zero()
{
    ArrayList a{};
    std::cout << "Test that empty array has length zero";
    assert(a.length() == 0);
    std::cout << " - Success!\n";
}

/**
 * @brief Test the append method and the get method
 *
 */
void test_append_and_get()
{
    std::cout << "Test append and get";
    ArrayList a{};
    a.append(42);
    a.append(43);
    assert(a.length() == 2);
    assert(a.get(0) == 42);
    assert(a.get(1) == 43);
    std::cout << " - Success!\n";
}

/**
 * @brief Test that printing works
 *
 */
void test_print()
{
    std::cout << "Test print\n";
    ArrayList a{};
    a.append(42);
    a.append(43);
    a.print();
}

/**
 * @brief Test that we can construct an ArrayList from
 * a vector of integers
 *
 */
void test_vector_constructor()
{
    std::cout << "Test the vector constructor";
    ArrayList a{{1, 2}};
    assert(a.length() == 2);
    assert(a.get(0) == 1);
    assert(a.get(1) == 2);
    std::cout << " - Success!\n";
}

/**
 * @brief Test the indexing operator []
 * to both getting at setting values
 *
 */
void test_indexing_operator()
{
    std::cout << "Test the indexing operator";
    ArrayList a{{1, 2}};
    assert(a[0] == 1);
    assert(a[1] == 2);
    a[0] = 42;
    assert(a[0] == 42);
    std::cout << " - Success!\n";
}

int main()
{
    test_empty_array_has_length_zero();
    test_append_and_get();
    test_print();
    test_vector_constructor();
    test_indexing_operator();
}
```

You can also find the source code at <https://github.uio.no/IN1910/cpp-list>

## Dynamic Arrays, Vector and Python Lists

The `ArrayList` class we have just gone through and described is an example of a *data structure*, which will be topic in the coming two weeks of IN1910. We will go through more of the terminology then. For now, let us take a step back and look at what we have done.

We took arrays, a very low-level and fundamental structure of C++, and used it to implement something that behaves like a list. You might think this was a strange exercise to perform, we already have lists, why would we want to make them from arrays?

The reason we have taken time to cover dynamic arrays, or array lists as we called them, is that this is *precisely how Python lists are implemented*. It is also how the C++ vector class is implemented. They both rely on arrays behind the scenes, which they resize whenever needed.

In both cases, you can go into the documentation or the source code and check this for yourself, but we can also verify it through how the classes behave. For the vector class this is quite easy actually, because the `capacity` variable is public in this class. So we can simply append elements (with the `push_back` method) and see how the capacity grows.

```C++
vector<int> example;

cout << setw(10) << "Nr Elements";
cout << setw(10) << "Capacity" << endl;
cout << setw(10) << example.size();
cout << setw(10) << example.capacity() << endl;

for (int i = 0; i < 1200; i++)
{
    example.push_back(i);
    cout << setw(10) << example.size();
    cout << setw(10) << example.capacity() << endl;
}
```
Which prints the following:
```text
Nr Elements Capacity 0 0
1 1
2 2
3 4
4 4
5 8
6 8
7 8
8 8
9 16
10 16
11 16
12 16
13 16
14 16
15 16
16 16
17 32
......
```
And so on. So we see that the C++ vector class starts of with a capacity of 0. When adding the first element, it goes to a capacity of 1, and from there it doubles every time more space is needed. We state this by saying it has a growth factor of 2, because every time the capacity increases, it doubles.

Note that if you are compiling with Microsoft's Visual C++ instead of gcc or clang, you will most likely get a different result, as Microsoft's implementation of vector uses a growth factor of 1.5, instead of 2.

In Python, it is a bit more tricky to verify, because we cannot directly access the capacity of the list. However, we can use the `sys.getsizeof` function, which returns the size of an object, in number of bytes.

```{code-cell} python
import sys

example = []

print("Nr Elements   Bytes")
print(f"{len(example):11} {sys.getsizeof(example):6}")
for i in range(20):
    example.append(i)
    print(f"{len(example):11} {sys.getsizeof(example):6}")
```

So we see the amount of memory used for the list object does not increase with each append, but instead stays constant, and then makes larger steps. This happens when going for 0 to 1, 4 to 5, 8 to 9, 16 to 17. Which indicates that the capacity of the Python list grows as:

$$0, 4, 8, 16, ...$$

While this might look like growth factor of 2, it turns out that the Python list implementation has a more complicated growth factor that changes as the list grows.

You can read more about dynamical arrays on the [wikipedia page](https://en.wikipedia.org/wiki/Dynamic_array), where there is also a table of common implementation and their growth factors.



## Vector vs List

We have stated that C++ are similar to Python lists, and now you can see why we said this, they are both built on the same underlying data structure, dynamic arrays. There is a different data type in C++ called lists, which you can access through:
```C++
#include <list>
```
But this list implementation does *not* use a dynamic array structure, it instead relies on a different structure, called a *linked list*. Which is the topic of the next lecture.
