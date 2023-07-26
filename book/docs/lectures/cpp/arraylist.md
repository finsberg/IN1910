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

We now turn to something different: we will use what we have learned in C++ so far to implement a data structure.

In Python, we are used to working with lists, but it is useful to understand how they actually work behind the scenes. In C++, we claimed that a *vector* is a similar object to the Python list. Now, we will assume that neither Python lists nor C++ vectors exist, building our own data structure from the bottom up.

To make such "list" objects, we will use a technique called *dynamic arrays*, not to be confused with dynamically allocated arrays, discussed earlier in [Dynamic memory allocation](dynamic_allocation.md). An alternative name for *dynamic arrays* is *array lists*, referring to the fact that we use arrays to create a list class.

## Arrays with variable size

When creating list objects, one of the most important things we want to be able to do is to append new elements to them. However, in C++, arrays are created with a specific and immutable size. So how could we possibly append elements to a given array?

We cannot resize an array but will *fake* it by cleverly implementing encapsulation. When allocating this array, we simply make it significantly bigger than what we want to store. That way, we have extra memory reserved to append additional elements.

Inside the class, we store the actual data array we use (which is static in size) in a pointer variable called `_data`. We also store a private variable `_capacity`, which is a measure of how long the actual array is. Furthermore, there is a `_size` variable denoting how many elements are stored in the array. This variable can be read using the `length` method and represent the array size from the outside.

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
}
```

Note that we will use the familiar Python convention for private variable and method names, in which all private variables and methods have a name starting with an underscore (`_`).

By default, we set the array capacity to a large number (for example 1000), with size 0. These default values directly in the class as follows

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
We now make the constructor where the required memory will be allocated for the Array list using the `new` keyword.
```C++
ArrayList()
{
    _data = new int[_capacity];
}
```
Whenever we write `new` in the code, we need to remember to add the `delete` to avoid a memory leak. The `delete` will be added in the destructor.
```C++
~ArrayList()
{
    delete[] _data;
}
```

### Testing the constructor

Now is a good time to compile the program into an executable and make sure it behaves as expected. We should also make sure that we can create an `ArrayList` and that its initial `length` is zero. We can do so in a separate function that is called from the `main` function.

```C++
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
Here we create a function called `test_empty_array_has_length_zero`, where we first instantiate an empty `ArrayList` named `a` which we assert has length zero.
Note that we have included `cassert` where the `assert` function is defined. See {ref}`cpp-testing` for more information about testing in C++.

Assuming that all the code is written in a single file called `array_list.cpp` it can be compiled into an executable called `array_list` by executing the following command
```
c++ -std=c++14 array_list.cpp -o array_list
```
This will create a new file called `array_list`. The program can then be run by executing the file
```
./array_list
```
In this case, there will be no output, but we can, of course, add some printing to indicate that the test ran successfully, e.g.,
```C++
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
## Adding tests in a separate test file
Before continuing, we will try to better organize the code by putting the class declaration in one file called `array_list.cpp` and the tests in another file called `test_array_list.cpp`.

In {ref}`cpp-header-files`, we discuss how to compile multiple files together. In that section, we also discuss the usage of header files. In this example, however, we will not use header files for the sake of simplicity.

By creating a new file called `test_array_list.cpp` and moving the functions `test_empty_array_has_length_zero` and `main` from `array_list.cpp` to this new file, the file `array_list.cpp` will look as follows

```C++
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

Similarly, `test_array_list.cpp` will look as follows
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
which will import all the content from `array_list.cpp` into `test_array_list.cpp`.

In {ref}`cpp-compilation-linked`, there is more information about compiling multiple files together. When the declarations are contained in a separate header file, it is first necessary to compile the individual files into separate object files and then link them together. However, if the `cpp` file is included directly, like in this example, the individual files need not be compiled separately, and an `array_list` binary can be simply created using the command
```
c++ test_array_list.cpp -std=c++14 -o array_list
```

## Appending
Next, we add a public method for appending a new element to the list. The appended element should go to the first unused location in the storage array, which is `_data[_size]`. Indeed, the indices $0, 1, \ldots, n-1$ are used for actual storage. However, since going over the maximum allocated capacity can be dangerous, we should check this condition explicitly.
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
Here the program will throw a `range_error` exception if the array size exceeds the capacity. Note that to use this, one might also need to include the following line in the file
```C++
#include <stdexcept>
```
Now we can append elements to the list, which will be stored in the underlying array. As long as the initially allocated capacity is not exceeded, everything works well.


## Getting
We will also need to have some way of accessing the stored elements, as they are stored in a private array. For this, we define a getter. This getter takes the index of the requested element and sends a reference to the entry back to change the variable if desired.
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
Note that we explicitly check if the index is out of bounds, throwing a range error if that is the case. The user should therefore not be able to access the part of the storage array that is not filled.

## Testing `append` and `get`

We should now verify that the `append` and `get` methods are working as expected. This will be done by implementing a test function called `test_append_and_get` in `test_array_list.cpp`, as follows
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
Running this from the main function should result in no output, but we can also print some message to the console saying that the test passed.

## Printing the array

It would be convenient to add a method that prints the array's elements, which can be done by implementing a `print` method as follows
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

Instead of having to append all the elements to an empty array, we can overload the constructor to take in some initial data if desired.
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
Note that if the size of the input array is larger than the capacity, we increase the capacity to be of the same size as the input array. Remember to also add the line
```c++
#include <vector>
```
at the top of the file.

We should additionally create a new test that ensures the new constructor is working as expected, such as the following test function
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

While this `get` method works well for getting out specific array elements, imagine we wanted to index elements in the same way as in a Python, i.e., with square brackets as follows
```C++
ArrayList a{{1, 2}};
std::cout << "a[0] = " << a[0] << "\n"; // a[0] = 1
```
Furthermore, we would like to be able to update the array using the same notation, i.e.
```C++
a[0] = 42;
std::cout << "a[0] = " << a[0] << "\n"; // a[0] = 42
```
This can be implemented by overloading the `[]` operator similarly to a Python special method. By using a specific name, we can redefine the behavior of square bracket indexing.
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
Note that, unlike `get`, we now return a reference variable (`int&`), which means that we should be able to use this method to both read and write to the array. Let us also add the following test to `test_array_list.cpp`

```C++
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

We have so far created a class that, from the outside, acts much like a `vector<int>` object. We can append new integers to it and interact with it using indexing. This object also remembers its own size, which we can read through the `length` function. However, our implementation has some issues, namely the fixed capacity.

The number 1000 was completely arbitrary and can create issues in either direction. Clearly, if we want to create a list with several million elements, this implementation would not work. On the other hand, if we want to create thousands of lists of only a handful of elements, our implementation would be horribly inefficient, as every single list would take up a large chunk of unused memory.

## Dynamic resizing

To get around these issues, we need to be able to *adjust the capacity* as needed. Let us start with a smaller capacity of 1.
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
In this case, we will hit our max capacity much sooner, but when this happens, instead of throwing an error, we want to *resize* our capacity.
```C++
void append(int n)
{
    if (_size >= _capacity)
    {
        resize();
    }
    _data[_size] = n;
    _size++;
}
```
But how can this `resize` method work? After all, we are not allowed to change the size of the underlying storage array. What we can do, however, is create a brand new storage array of larger capacity and copy all the stored values over to the new array. In the example below, we will double the capacity every time we resize
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
Here we first create a new storage array, called `new_data`, with a new capacity twice as large as the original one. The choice of doubling the capacity is arbitrary, and one could have a different *growth factor* other than 2. Next, we copy all the stored values over to the new array. Then we delete the old storage array to free the memory, as it was dynamically allocated. Lastly, we reassign the `_data` pointer to the new storage array.

The resizing fixes both of our problems with our original implementation. As the initial capacity is so small it takes next to no space, we can make many short lists without issue. And if we want to make a very long list, the list will resize automatically behind the scenes, without the user having to think about it whatsoever.

Also, note that the `resize` method is not something the user should need to care about; therefore, it can be added as a private method.

```{admonition} Click to see the full source code
:class: dropdown

```C++
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


## Dynamic Arrays, Vectors, and Python Lists

The `ArrayList` class we have just gone through and described is an example of a *data structure*. We will go through more of the *data structure* terminology in future chapters. For now, let us take a step back and look at what we have done.

We took an array, a very low-level and fundamental structure of C++, and used it to implement something that behaves like a list. One might think this was a strange exercise to perform as we already have lists. So why would we want to make them from arrays?

We have taken time to cover dynamic arrays, or array lists, as we called them, because this is *precisely how Python lists are implemented*. It is also how the C++ vector class is implemented. They both rely on arrays behind the scenes, which get resized whenever needed.

In both cases, we invite the reader to go into the documentation or the source code and check this for themselves, but we can also verify it through how the classes behave. For the vector class, this verification is relatively easy because the `capacity` is a public variable. We can, therefore, simply append elements (with the `push_back` method) and see how the capacity grows.

```C++
std::vector<int> example;

std::cout << std::setw(10) << "Nr Elements";
std::cout << std::setw(10) << "Capacity" << std::endl;
std::cout << std::setw(10) << example.size();
std::cout << std::setw(10) << example.capacity() << std::endl;

for (int i = 0; i < 1200; i++)
{
    example.push_back(i);
    std::cout << std::setw(10) << example.size();
    std::cout << std::setw(10) << example.capacity() << std::endl;
}
```
Which prints the following
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
And so on. So we see that the C++ vector class starts with a capacity of 0. When adding the first element, it goes to a capacity of 1, and from there, it doubles every time more space is needed. We state this by saying it has a growth factor of 2.

Note that the above output would be slightly different for someone compiling with Microsoft's Visual C++ instead of gcc or clang. This is because Microsoft's implementation of vectors uses a growth factor of 1.5 instead of 2.

In Python, the capacity of a list cannot be directly accessed, and this behavior is harder to verify. However, we can use the `sys.getsizeof` function, which returns the size of an object in number of bytes.

```{code-cell} python
import sys

example = []

print("Nr Elements   Bytes")
print(f"{len(example):11} {sys.getsizeof(example):6}")

for i in range(20):
    example.append(i)
    print(f"{len(example):11} {sys.getsizeof(example):6}")
```

We see the amount of memory used for the list object does not increase with each append but instead stays constant and then makes larger steps. This happens when going from 0 to 1, 4 to 5, 8 to 9, 16 to 17, indicating that the capacity of the Python list grows as

$$0, 4, 8, 16, ...$$

While this might look like a growth factor of 2, the Python list implementation has a more complicated growth factor that changes as the list grows. To see exactly how the growth factor changes for python, take a look at the proper [implementation](https://github.com/python/cpython/blob/bace59d8b8e38f5c779ff6296ebdc0527f6db14a/Objects/listobject.c#L58).


## Vector vs. List

We have first stated and now shown that C++ vectors are similar to Python lists. They are both built on the same underlying data structure, the dynamic array. There is also a different data type in C++ called list, which can be accessed through
```C++
#include <list>
```
However, this list implementation does *not* use a dynamic array structure. It instead relies on a different structure called a *linked list*, which is the topic of [Linked Lists](linked_lists.md).
