---
jupyter:
  jupytext:
    text_representation:
      extension: .md
      format_name: markdown
      format_version: '1.3'
      jupytext_version: 1.10.3
  kernelspec:
    display_name: Python 3
    language: python
    name: python3
---

# References and pointers in C++

The following exercises will deal more explicitly with references and pointers in C++. To get an overview and remember the material, we refer to the notes at [Arrays, References, Pointers](../../lectures/cpp/arrays_and_pointers.md)

When implementing a function in Python that returns several values, even of different types, it is very common to return all at the same time using a tuple, e.g. `return n, x1, t_array`. C++ does not allow this, as tuples are not a native data structure. Instead, it is popular to retrieve the values resulting from the function by passing variables by reference to the function.

```{exercise-start} Returning several values using *Call by reference*
:label: call_by_reference
```

Write a function `stats()` that among other things takes a vector `data`. The function should calculate the mean and the median of the vector. Before finding the median, you can use the function `std::sort()` from the package `<algorithm>` to sort the vector. Be careful so that the original vector does not get sorted. Use call by references to retrieve the computed mean, median and sorted list. Print the computed values and the sorted vector for `vector<double> data = {1.2, 5.3, 7.1, -2.4, 9.2}`. Also, print the original vector to make sure the function call did not change it.
```{exercise-end}
```

```{solution-start} call_by_reference
:class: dropdown
```

The mean is calculated by iterating through each element of the vector data, summing them up and dividing the sum by the total number of elements in the vector.

```cpp
    // ...
    mean = 0;
    for (int i = 0; i < data.size(); i++)
    {
        mean += data[i];
    }
    mean = mean/data.size();
    // ...
```

The median is calculated by first sorting the vector data using the `std::sort()` function from the `<algorithm>` header. If the size of the vector is odd, the median is the middle value. If the size of the vector is even, the median is the average of the two middle values.
```cpp
    // ...
    sort(data.begin(), data.end()); //Sorting copy of data
    data_sorted = data;

    if (data.size()%2 == 0)
    {
        median = (data_sorted[data.size()/2 - 1] + data_sorted[data.size()/2])/2;
    }
    else
    {
        median = data_sorted[data.size()/2];
    }
    // ...
```

The function `stats()` which will contain these calculations does not modify the original vector data, since it receives a copy of it as an argument. The sorted vector is then stored in the data_sorted vector passed as a reference argument.

In the main function, we create a vector data with the values provided in the problem statement. We then call the stats() function, passing it the vector data, as well as the mean, median and data_sorted variables. After the call to stats(), the calculated mean and median, as well as the data_sorted vector are printed. To ensure that the original data vector was not modified, we also print the original vector after the call to stats().

The complete code solution can be seen below.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

void stats(std::vector<double> data, double &mean, double &median, std::vector<double> &data_sorted)
{
    /*Note that "data" has not been called by reference. By skipping "&" we call
    "data" by value, meaning "data" inside this function is just a copy of the
    original. This is important so that we avoid sorting the original vector.
    */
    mean = 0;
    for (int i = 0; i < data.size(); i++)
    {
        mean += data[i];
    }
    mean = mean/data.size();

    sort(data.begin(), data.end()); //Sorting copy of data
    data_sorted = data;

    if (data.size()%2 == 0)
    {
        median = (data_sorted[data.size()/2 - 1] + data_sorted[data.size()/2])/2;
    }
    else
    {
        median = data_sorted[data.size()/2];
    }
}

int main()
{
    double mean, median;
    std::vector<double> data = {1.2, 5.3, 7.1, -2.4, 9.2}, data_sorted;
    stats(data, mean, median, data_sorted);
    std::cout << "Mean: " << mean << ". Median: " << median << std::endl;

    cout << "Sorted vector: {";
    for (int i = 0; i < data.size(); i++)
    {
      std::cout << data_sorted[i] << " ";
    }
    std::cout << "}" << std::endl;

    std::cout << "Unsorted vector: {";
    for (int i = 0; i < data.size(); i++)
    {
      std::cout << data[i] << " ";
    }
    std::cout << "}" << std::endl;

    return 0;
}
```

```{solution-end}
```

As explained in [Arrays, References, Pointers](../../lectures/cpp/arrays_and_pointers.md), memory management in Python is handled automatically by the interpreter. In contrast, C++ provides direct control over memory allocation and deallocation. C++ uses pointers to refer to memory addresses and manipulate the values stored in them. Understanding pointers and pointer arithmetic is critical for writing efficient and performant C++ code.

```{exercise-start} Pointers and pointer arithmetic
:label: pointers_and_arithmetic
```

In this exercise, we will explore how C++ handles pointers and addresses to locations in the memory.

**a)**

Declare some variables `int a`, `float b`, `double c`. Use the reference operator `&` to get the addresses of the variables and print them.

Note that the meaning of `&` depends on the context. When used in a function call, like `void func(int &x)`, it means "call by reference" like in the previous exercise. In this exercise, however, `&` simply returns the address to where the variable is stored in memory. The addresses are displayed as *hexadecimal* numbers, so you might find that they look a little bit odd.

**b) Printing the address of consecutive elements**

The most primitive way of storing data in C++ is to allocate a chunk of memory and store the address to where this chunk starts. For example, `int data[n]` allocates enough space for `n` integer values and stores the address to the first element in the pointer `data`.

When allocating memory, the resulting array is said to be contiguous, meaning the elements of the array are stored at consecutive addresses in the physical memory. To verify this, make a function `address_of_int(int* data, int n)` that iterates over `data` and prints the address of each element. How far apart are the addresses? Repeat the same procedure for `double data[n]`. Is the spacing of the addresses the same as for `int`? Why/why not?



**c) Pointer arithmetic**

As already stated, the pointer `data` contains the address of the first element of the memory that was allocated. Whereas `&` gets the address where a value is stored, there is an inverse operator `*` that when applied to an address returns the value that lives there. We can thus write `*data` to retrieve the first element that `data` is pointing at, and this is equivalent to writing `data[0]`. `*` is called the dereference operator.

A neat thing about dereferencing an address is that we can manipulate the address before dereferencing to get other values. For example, `*(data + 1)` will increment the address by one and return the next value, i.e. `data[1]`. Likewise, `*(data + 2)` is the same as `data[2]`. This is called pointer arithmetic and is mainly a style choice.


Declare and initialize an array `int numbers[10]` containing the first ten natural numbers. Write a function `pointer_arithmetic(int* numbers, int n)` that iterates over `numbers` using pointer arithmetic rather than indexing and printing the elements. Also, print the incremented addresses and the addresses of `numbers[i]` to verify that pointer arithmetic and indexing are equivalent.
```{exercise-end}
```


```{solution-start} pointers_and_arithmetic
:class: dropdown
```

We start by defining the `int_address` function that takes in a pointer data and an integer n representing the length of the data array. We use a for loop to iterate over the array and print out the address of each element using the `&` operator, which returns the address of the element.

```cpp
void int_address(int* data, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout <<"Address of integer value number " << i <<":" << &data[i] << std::endl;
    }
}
```

Afterward, we can define another function `double_address`  that does the same thing as int_address but for a double data type.
The last function we need to pay close attention to is `pointer_arithmetic`, which takes in an array of integers numbers and an integer n representing the length of the array. We use a for loop to iterate over the array and print out each element using pointer arithmetic.

```cpp
void pointer_arithmetic(int* numbers, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << "Value: " << *(numbers + i) << ". Incremented address "
             << (numbers + i) << ". Address of element: " << &numbers[i]
             << std::endl;
    }
}
```

Note we used the dereference operator `*` to access the value at the memory location and the `+` operator to increment the memory location. We also printed out the address of the element using the `&` operator and the memory location using the `+` operator. The final code in the proper complete structure is displayed below.

```cpp
#include <iostream>

void int_address(int* data, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout <<"Address of integer value number " << i <<":" << &data[i] << std::endl;
    }
}

void double_address(double* data, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout <<"Address of double value number " << i <<":" << &data[i] << std::endl;
    }
}

void pointer_arithmetic(int* numbers, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << "Value: " << *(numbers + i) << ". Incremented address "
             << (numbers + i) << ". Address of element: " << &numbers[i]
             << std::endl;
    }
}

int main()
{
  int a; float b; double c;

  std::cout << &a << " " << &b << " " << &c << std::endl;

  int const n = 10;
  int int_data[n];
  double double_data[n];

  int_address(int_data, n);
  double_address(double_data, n);

  int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  pointer_arithmetic(numbers, 10);

  return 0;
}
```

```{solution-end}
```
