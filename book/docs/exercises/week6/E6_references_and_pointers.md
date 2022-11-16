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

# Week 6, Part 2
## References and pointers in C++



### Exercise 1) Returning several values using *Call by reference*

When implementing a function in python that returns several values, even of different types, it is very common to return all at the same time using a tuple, e.g. `return n, x1, t_array`. C++ does not allow this, as tuples are not a native data structure. Instead, it is popular to retrieve the values resulting from the function by passing variables by reference to the function.

Write a function `stats()` that among other things takes a vector `data`. The function should calculate the mean and the median of the vector. Before finding the median, you can use the function `std::sort()` from the package `<algorithm>` to sort the vector. Be careful so that the original vector does not get sorted. Use call by references to retrieve the computed mean, median and sorted list. Print the computed values and the sorted vector for `vector<double> data = {1.2, 5.3, 7.1, -2.4, 9.2}`. Also print the original vector to make sure the function call did not change it.


### Exercise 2) Pointers and pointer arithmetic

In this exercise, we will explore how C++ handles pointers and addresses to locations in the memory.

#### Exercise 2a)
Declare some variables `int a`, `float b`, `double c`. Use the reference operator `&` to get the addresses of the variables and print them.

Note that the meaning of `&` depends on the context. When used in a function call, like `void func(int &x)`, it means "call by reference" like in the previous exercise. In this exercise however, `&` simply returns the address to where the variable is stored in memory. The addresses are displayed as *hexadecimal* numbers, so you might find that they look a little bit odd.

#### Exercise 2b) Printing the address of consecutive elements
The most primitive way of storing data in C++ is to allocate a chunk of memory and store the address to where this chunk starts. For example `int data[n]` allocates enough space for `n` integer values and stores the address to the first element in the pointer `data`.

When allocating memory, the resulting array is said to be contiguous, meaning the elements of the array are stored at consecutive addresses in the physical memory. To verify this, make a function `address_of_int(int* data, int n)` that iterates over `data` and prints the address of each element. How far apart are the addresses? Repeat the same procedure for `double data[n]`. Is the spacing of the addresses the same as for `int`? Why/why not?

#### Exercise 2c) Pointer arithmetic
As already stated, the pointer `data` contains the address of the first element of the memory that was allocated. Whereas `&` gets the address where a value is stored, there is an inverse operator `*` that when applied to an address returns the value that lives there. We can thus write `*data` to retrieve the first element that `data` is pointing at, and this is equivalent to writing `data[0]`. `*` is called the dereference operator.

A neat thing about dereferencing an address is that we can manipulate the address before dereferencing to get other values. For example, `*(data + 1)` will increment the address by one and return the next value, i.e. `data[1]`. Likewise, `*(data + 2)` is the same as `data[2]`. This is called pointer arithmetic, and is mainly a style choice.

Declare and initialize an array `int numbers[10]` containing the first ten natural numbers. Write a function `pointer_arithmetic(int* numbers, int n)` that iterates over `numbers` using pointer arithmetic rather than indexing and print the elements. Also print the incremented addresses and the addresses of `numbers[i]` to verify that pointer arithmetic and indexing are equivalent.
