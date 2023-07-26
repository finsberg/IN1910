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
# More on pointers and arrays and dynamic allocation

In this section, we will continue discussing pointers and how they relate to arrays. We will also use what we have learned about object-oriented programming to design a few classes for making list objects.


## Some repetition

Recall that we can create *pointer* variables, that store the memory address of some data. We can for example create an *integer pointer* as follows
```C++
int a = 12; // integer variable
int *b;     // integer pointer
```
Here, `b` is a pointer, because we use the asterisk (\*) when declaring its type. To make `b` point at `a`, meaning the variable is storing the memory address of `a`, we use the address-of operator
```C++
b = &a; // make b point at a
```
Now `b` points at `a` and we can use it to access and change `a`. However, recall that this cannot be done directly, meaning that if we attempt to output `b`, we do not ger the value of `a` in the following example

```C++
std::cout << b << std::endl;
```

The obtained output is *value* of `b`, which is the memory address, looking something like
```
0x7ffc072c388c
```
To actually get the variable a pointer is pointing to, we use the dereference operator
```C++
std::cout << *b << std::endl;
```

| expression | can be read as   |
| ---------- | ---------------- |
| int i      | integer variable |
| int *p     | pointer variable |
| *x         | pointed to by x  |
| &x         | address of x     |


Also, recall that we can set a pointer to point at "nothing"
```C++
b = nullptr;
```

## Pointers to objects

Suppose we create a struct
```C++
struct GridPoint
{
    int x;
    int y;
    int z;
};
```
We can then create an instance of this struct, and access its members using dot-notation
```C++
GridPoint start{10, 10, 0};
std::cout << start.x << std::endl;
std::cout << start.y << std::endl;
std::cout << start.z << std::endl;
```
We can also make a pointer to the object:
```C++
GridPoint *sp = &start;
```
Now, if we want to access one of the member attributes of the underlying object, we first need to dereference the pointer, and then use dot-notation:
```C++
std::cout << (*sp).x << std::endl;
```
We need the parenthesis to get the right order of operations. This syntax works but is often regarded as cumbersome. Instead of dot syntax, it is common to draw an arrow
```C++
std::cout << sp->x << std::endl;
```
The arrow (`->`) means the member attribute of the object pointed at, and thus is equivalent to writing `(*sp).x`.

| expression | can be read as                     |
| ---------- | ---------------------------------- |
| x.y        | member y of object x               |
| x->y       | member y of object pointed to by x |
| (*x).y     | member y of object pointed to by x |


## Arrays and Pointers

We have briefly shown how arrays can be created, for example
```C++
int x[100];
```
Here, `x` will be an array of 100 ints. We can access these by indexing: `x[0]`, `x[1]`, $\ldots$, `x[99]`.

Earlier, we stated that an array will be *contiguous* in memory, i.e., each element follows the others directly. We can check this statement by writing out the memory addresses
```C++
std::cout << & x[0] << std::endl;
std::cout << &x[1] << std::endl;
std::cout << &x[2] << std::endl;
std::cout << &x[3] << std::endl;
```
Which prints out
```C++
0x7ffed0407920 0x7ffed0407924 0x7ffed0407928 0x7ffed040792c
```
Note that the memory address increases by 4 every step (it goes from 8 to c because it is hexadecimal). This step size is because memory addresses are in terms of bytes (8 bits), and integers are 32-bit variables.

By outputting the array variable itself, we get the memory address of the first element `x[0]`
```C++
std::cout << x << std::endl;
```
Which outputs
```
0x7ffed0407920
```
This indicates that the array variable `x` is almost the same as a pointer to the first variable of the array.

Let us highlight this in another way with the following code snippet
```C++
int x[] = {2, 4, 6, 8, 10, 12};
int *y = &x[2];
```
Here we make an array and an integer pointer that points at the third element of the array, with a value of 6. However, because array variables behave much like pointers to the first element, `y` will behave like an array
```C++
std::cout << y[0] << " ";
std::cout << y[1] << " ";
std::cout << y[2] << " ";
std::cout << y[3] << std::endl;
```
This is because the square bracket indexing in C++ indicates looking at the next elements in memory. `y` will therefore behave just like an array. We could also have accessed the elements using *pointer arithmetic*
```C++
std::cout << *(y) << " ";
std::cout << *(y + 1) << " ";
std::cout << *(y + 2) << " ";
std::cout << *(y + 3) << std::endl;
```
Here, dereferencing `y` itself gives the first element, 6. By computing `y + 1` we go to the next integer in memory, which is element 2, and so on.


In short, a pointer is a variable that stores the memory address of some data type. If these data lie contiguously in memory, then having the address of the first element is all we need to reference the whole set. Therefore, an `int *` pointer can point to a single integer, or to a whole sequence of them. Note that the pointer itself does not know how many elements it points at. Similarly, an array does not know how many elements it contains, which is why indexing out of bounds will not give an `IndexError` (it has an undefined behavior instead, requiring caution).


| expression | can be read as                 |
| ---------- | ------------------------------ |
| x[0]       | first object pointed to by x   |
| x[1]       | second object pointed to by x  |
| x[n]       | (n+1)th object pointed to by x |


## Dynamic Memory Allocation

So far we have seen how to create a pointer object, and how to make it point at something. We have also seen how to point it at "nothing" (null pointer). However, we have only implemented pointers with objects that were already previously created. It is also possible to get a pointer to point at a new object, as in the following example
```C++
int *x;
x = new int;
*x = 5;
```
Here we first create an integer pointer. Then we specify that we want a new integer object to be made, and its address to point to. An interesting consequence is that we have a variable that is *not named* and can only be accessed through the pointer.

Notice that using the `new` keyword is necessary and this use is referred to as *dynamic memory allocation*.

### Lifetime of Variables

In C++, things are automatically destroyed once they go out of scope. If a vector is defined inside a function, for example, that vector ceases to exist once that function's execution is finished. Meanwhile, dynamically allocated memory elements are not terminated, which can be better understood with the following example.

We have discussed how arrays are efficient given their contiguous behavior in memory, but also pointed out that arrays do not know their size. To deal with the latter, we will make an `Array` class that stores both the data array and its size, as a single object. We first define the object as
```C++
class Array
{
  public:
    int *data;
    int size;
};
```
Where `data` is a pointer to the first element of the underlying array, and `size`, the number of elements.

When making the constructor we want to take in, as an integer, the number of desired elements. The constructor should then allocate the memory of the array, set all the elements to zero, and point the `data` pointer to this array. Although the following code seems like a reasonable way to achieve this, **it will not work**.
```C++
Array(int n)
{
    int tmp[n];
    for (int i = 0; i < n; i++)
    {
        tmp[i] = 0;
    }
    data = tmp;
    size = n;
}
```
The reason for the code above not working is that, whenever a function finishes, everything created inside it is automatically destroyed. As the array is created inside the constructor, it is destroyed too. The data pointer is set to point at this array, but if the object pointed at is destroyed, using the pointer is not reasonable.
Trying to run the following code will result in unpredictable outputs which change for each program run.
```C++
Array a(10);
for (int i = 0; i < a.size; i++)
{
    std::cout << a.data[i] << " ";
}
```
For a specific execution, the obtained output was
```
0 1 31872064 1 31872064 1 30535429 1 31872064 1
```

However, when using dynamic memory allocation, the data is not destroyed at the end of the function. To dynamically allocate an array, we do the following
```C++
Array(int n)
{
    data = new int[n];
    size = n;
    for (int i = 0; i < n; i++)
    {
        data[i] = 0;
    }
}
```
Now, the obtained result is as expected, consisting of only zeroes.

(scope-and-lifetime)=
### Scope and lifetime
A scope is a region or section of the code where a variable can be accessed. The scope can be thought of as the innermost curly braces (`{}`) that encapsulate the variable declaration. This could be inside or outside a function. The lifetime of an object is the portion of the program's execution during which its storage is guaranteed to be reserved.

Consider the following code
```C++
int main()
{
    int *p;
    {
        int x = 5;
        p = &x;
    }
    std::cout << *p << std::endl;
    return 0;
}
```
Here, we define an integer pointer `p` and inside a local scope (created using curly braces), we create an integer variable `x` and point `p`. This code, however, has a subtle problem. When the created scope is exited and we print out the value that `p` points to, the variable `x` does not exist anymore. Consequently, `p` points at some address in memory that is no longer owned by the program. Note that the value `5` will most likely still be printed out on the console, but there is no guarantee that the stored value at this memory address will remain `5`. We call this *undefined behavior*, which is the root of some of the trickiest bugs to debug.

## Deallocating Memory and Garbage Collection

In Python, garbage collection is a built-in feature. Garbage collection is a term for automatic processes that collect unused variables and deallocates them from memory, freeing the previously allocated memory addresses. In Python, any variable that no longer has a name referencing it is flagged for garbage collection and is destroyed.

In C++, there is no garbage collection. Instead, data will be destroyed when it goes out of scope. However, as discussed previously, dynamically allocated objects survive in memory even when out of scope, requiring the user to explicitly deallocate variables when careful use of memory resources is necessary.

If one *does not* de-allocate dynamically created memory, it will continue to take space until the program finishes running. Often, and especially with modern computers, this is not a problem. Nonetheless, in certain situations, it can lead to program-crashing bugs.

### Memory Leaks

Earlier, the code below was used to illustrate dynamic allocation of memory
```C++
int *x;
x = new int;
*x = 5;
```
If we now do a new dynamic allocation
```C++
x = new int;
```
Then `x` will point to a new object, while the old one still occupies space in memory. More critically, the other integer has no name, and we no longer have any pointers to it. As a consequence, that piece of memory is locked down until the entire program terminates and we have no way of accessing or using that variable. This is referred to as a memory leak.

A small memory leak is of no issue and not noticeable. However, with large memory leaks, the machine will run out of memory and the program and OS will grind to a halt, most likely requiring the termination of the program or even a full reboot of the system.


Let us create a program that on purpose leaks a lot of memory
```C++
void doomsday()
{
    while (true)
    {
        new int;
    }
}
```
Here we define an infinite loop. For each iteration, we allocate a new integer in memory, which is never deallocated. This means, for each iteration of the loop, the program will use a slightly larger amount of memory (32 bits to be exact).

Compiling the `doomsday.cpp` code will likely not generate any warnings. When trying to run it, however, one will definitely encounter problems. The program will ask for more and more memory from the system, never deallocating any. Moreover, the program never aborts itself or stops, so it is up to the system to recognize that this program is not acting right and terminate it. Whether or not that actually happens depends on your system. In the worst case, all memory will be hogged by the doomsday program, leaving none for the system. The only way to regain control in this scenario is a hard reboot of the machine. Not ideal!

More about how to debug such memory leaks is available in the [debugging section](cpptools.md).

### Memory leaks in Practice

In practice, memory leaks are hard to detect. The leak does not build up as fast as in the above example but does so over hours or days. When testing software, we often opt for small, efficient tests. Often everything will seem correct in these tests until a long simulation gives an issue.

Memory leaks, and other similar bugs, sneak into a surprising amount of professional software, and is a major contributor to [*software aging*](https://www.cs.drexel.edu/~yfcai/CS451/RequiredReadings/SoftwareAging.pdf){cite:p}`parnas1994software`, where a software seem to become unresponsive or stop functioning when running over a longer time, but returns to normal after a reboot.

This [article on memory leaks](https://link.springer.com/content/pdf/10.1007/978-90-481-9112-3_73.pdf) has a good example of how a seemingly "trivial" program for an elevator could contain a memory leak.


### Freeing memory

If dynamically allocated memory has to be freed, we simply use the `delete` keyword as follows
```C++
int *x;
x = new int;

delete x;
```

Note that `delete x` will free the object pointed at by `x`, the pointer will still exist and be usable. If we are freeing an allocated array, we instead use `delete[]`
```C++
int *x;
x = new int[200];

delete[] x;
```

## The Destructor

Returning to the `Array` class example, we defined the following class
```C++
class Array
{
  public:
    int *data;
    int size;

    Array(int n)
    {
        data = new int[n];
        size = n;
        for (int i = 0; i < size; i++)
        {
            data[i] = 0;
        }
    }
};
```
This class works well, and we can now use it inside other functions where we need arrays. As discussed, at the end of those functions, the newly created `Array` object will automatically be destroyed. However, the dynamically allocated memory inside the object will not be!

To ensure that the dynamic memory is deallocated with the object, we need to define a *destructor*, which is called automatically when an object goes out of scope and is destroyed. Whereas the constructor has the same name as the class, the destructor is named the same with a tilde (~) in front.
```C++
~Array()
{
    delete[] data;
}
```
The reader is invited to implement the destructor for the following simple test program
```C++
void create_and_destroy_array()
{
    Array a(100);
}

int main()
{
    while (true)
    {
        create_and_destroy_array();
    }
}
```
If this program is run without implementing the deallocator, its memory usage will be exponential. After implementing the deallocator, every function call properly destroys the object and all the underlying data, which is more appropriate.

## Stack vs. Heap

In C++ and many other programming languages, we refer to two different forms of memory: the stack and the heap. Everything created by code lives in one of these two memory spaces. Normally created variables will live on the stack. Every function has its own stack space, and when the function is finished, the stack is emptied and the variables are destroyed. Meanwhile, dynamically created variables live on the heap, where nothing is automatically deallocated.

We will not talk extensively about stack and heap, but they might appear in other sources, especially in more C++-dedicated courses.

(smart-pointers)=
## Smart Pointers

Knowing how memory is acquired and released is one of the reasons why knowing how to program in a lower-level programming language such as C++ will improve one's programming skills in general.

However, forgetting to delete objects that are allocated on the heap is a huge source of bugs and memory leaks, and therefore C++ programmers try to avoid calling `new` and `delete` as much as possible.

The recommendation from the C++ community is to use a principle known as *Resource Acquisition Is Initialization* (RAII). According to RAII, one should only acquire resources in the constructor and release them in the destructor (just like we did in the `Array` class).

One way to ensure this is to use *smart pointers*. A smart pointer is a pointer that owns the object it points to, making sure that the memory it points to is automatically deallocated once the pointer goes out of scope.

To use smart pointers we need to include the `<memory>` header and compile with the flag `-std=c++14`.

### First example with smart pointers

Let us first have a look at a very simple usage of a smart pointer and compare this with the *raw* pointer version.


````{tab} C++ (raw pointer)
```C++
#include <iostream>

int main()
{
    int *p = new int{42};
    std::cout << *p << "\n";
    delete p;
}
```
````

````{tab} C++ (smart pointer)
```C++
#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<int> p = std::make_unique<int>(42);
    std::cout << *p << "\n";
}
```
````

The first thing we see is that we need to include the `<memory>` header, which is where the declarations for the smart pointers are defined.

Next, instead of `p` being of type `int*` it is now of type `std::unique_ptr<int>`. We say that `p` is a *unique pointer*. A unique pointer is one type of smart pointer. There are also other types of smart pointers, such as *shared pointers*, which we will discuss later.

We also see that we create a unique pointer by using the function `std::make_unique<type>(value)` for some type (here `int`) and some value (here `42`).

### Using smart pointers for custom classes

A more typical use case is to create a smart pointer for a custom `class` or `struct`. Consider the following example

```c++
#include <iostream>
#include <memory>
#include <string>

class Person
{
  private:
    std::string _name;

  public:
    Person(std::string name) : _name(name)
    {
    }
    void say_hello()
    {
        std::cout << "Hello from " << _name << "\n";
    }
    ~Person()
    {
        std::cout << "Goodbye from " << _name << "\n";
    }
};
```
Here we have a `Person` class that takes a name of type `string` in the constructor. It has a method for saying hello, and once the destructor is called, it prints a goodbye message.

#### Allocation on the stack

We can write a simple program that allocates an instance of a Person on the stack as follows:

```C++
int main()
{
    {
        std::cout << "Beginning of scope \n";
        Person person{"Henrik"};
        Person *p = &person;
        p->say_hello();
        std::cout << "End of scope \n";
    }
    std::cout << "End of function main \n";

    return 0;
}
```
Let us carefully walk through this example. The `main` function starts with an open curly brace (`{`) which defines the beginning of a scope. Once the program reaches the closing brace (`}`), i.e., the end of the scope, any variables declared on the stack will be freed automatically, see {ref}`scope-and-lifetime`.

First, we print a message saying `Beginning of scope` to indicate that the scope is beginning. Then, we create an instance of `Person` called `person` with the name `"Henrik"` and create a pointer to this object, which is used to say hello by calling the `say_hello` method. Next, we print a new message saying `End of scope` to indicate that the scope is ending and, finally, before the `main` function is ending, we print a message saying `End of function main`.

If we compile and run this code, it will give the following output
```
Beginning of scope
Hello from Henrik
End of scope
Goodbye from Henrik
End of function main
```
Notice also that the destructor is called at the end of the scope as expected.


#### Allocation on the heap using raw pointers

Now let us rewrite the example by allocating the object to the heap instead. Remember that allocations happening on the stack need to be known at compile time, meaning that in most cases some memory needs to be allocated on the heap to account for user input. As we have seen there are two options when allocating objects on the heap; using raw pointers or smart pointers. Let us first look at the example using a raw pointer.

```C++
int main()
{
    {
        std::cout << "Beginning of scope \n";
        Person *p = new Person{"Henrik"};
        p->say_hello();
        std::cout << "End of scope \n";
        delete p;
    }
    std::cout << "End of function main \n";

    return 0;
}
```
We use the `new` keyword to indicate that the object is allocated on the heap, and we must also remember to use `delete` on the pointer at the end of the scope. The output from this program is the same as the output from the program above, where we allocated the object on the stack.

Despite this being a very simple example, it is easy to imagine a more complicated use case (for example the `Array` class). Having to explicitly call `delete` can potentially be forgotten, especially if the call to `delete` has to happen at a different location in the code than where it was allocated (which is usually the case).

Let us see what happens if we forget to call delete by trying to run the following program
```c++
int main()
{
    {
        std::cout << "Beginning of scope \n";
        Person *p = new Person{"Henrik"};
        p->say_hello();
        std::cout << "End of scope \n";
    }
    std::cout << "End of function main \n";

    return 0;
}
```
The program compiles without any error and the output is
```
Beginning of scope
Hello from Henrik
End of scope
End of function main
```
Notice there is no call to the destructor, indicating we have a memory leak. If this code was part of a long-running program, and this code run repeatedly, the computer could run out of memory and crash.


#### Allocation on the heap using smart pointers
To save us from needing to call delete while ensuring that memory allocated on the heap is freed, we can use a smart pointer. Let us look at the same example using smart pointers (note that the `<memory>` header is included in the part of the code where the `Person` class is defined):

```C++
int main()
{
    {
        std::cout << "Beginning of scope \n";
        std::unique_ptr<Person> p = std::make_unique<Person>("Henrik");
        p->say_hello();
        std::cout << "End of scope \n";
    }
    std::cout << "End of function main \n";
    return 0;
}
```
Instead of using `new` and `delete` we now let `p` be of type `std::unique_ptr<Person>` and create it using `std::make_unique<Person>("Henrik")`. When running this program we get
```
Beginning of scope
Hello from Henrik
End of scope
Goodbye from Henrik
End of function main
```
In other words, the smart pointer makes sure that the destructor is called when the pointer goes out of scope.

### Shared pointers
We have now seen one example of a smart pointer, namely the unique pointer (`unique_ptr`). The unique pointer has one limitation which is that the object pointed to by a unique pointer can not be pointed to by any other pointer.

As a result, the following code is not allowed
```C++
std::unique_ptr<Person> p = std::make_unique<Person>("Henrik");
std::unique_ptr<Person> p1 = p;
```
If one wants several different pointers to point to the same object, *shared pointers* should be used instead of unique pointers.

Consider the following code, where each person object now holds a pointer to some shared object

```C++
#include <iostream>
#include <memory>
#include <string>

struct SharedObject
{
    SharedObject()
    {
        std::cout << "Creating shared object\n";
    }
    ~SharedObject()
    {
        std::cout << "Deleting shared object\n";
    }
};

class Person
{
  private:
    std::string _name;
    std::shared_ptr<SharedObject> _obj;

  public:
    Person(std::string name, std::shared_ptr<SharedObject> obj) : _name(name), _obj(obj)
    {
        std::cout << "Creating Person " << _name << " with shared object " << _obj << " \n";
    }
    ~Person()
    {
        std::cout << "Deleting " << _name << "\n";
    }
};
```
Here we have defined a `struct` called `SharedObject` and each instance of `Person` holds a shared pointer to an instance of `SharedObject` which is named `_obj`. We also print a little message in the constructors and destructors.

Let us write a simple main function that creates one shared object that is used by two different instances of `Person`. To make it all more interesting, let us define the shared object in the scope of the `main` function and let us create the `Person` object within a different scope.

```C++
int main()
{
    std::shared_ptr<SharedObject> shared_object = std::make_shared<SharedObject>();
    std::cout << "Use count: " << shared_object.use_count() << "\n";
    {
        std::cout << "Beginning of outer scope \n";
        Person p1{"Henrik", shared_object};
        std::cout << "Use count: " << shared_object.use_count() << "\n";
        {
            std::cout << "Beginning of inner scope \n";
            Person p2{"John", shared_object};
            std::cout << "Use count: " << shared_object.use_count() << "\n";
            std::cout << "End of inner scope \n";
        }
        std::cout << "End of outer scope \n";
        std::cout << "Use count: " << shared_object.use_count() << "\n";
    }
    std::cout << "Use count: " << shared_object.use_count() << "\n";
    std::cout << "End of function main \n";
    return 0;
}
```
Creating a shared pointer is very similar to creating a unique pointer; simply swap out `unique` with `shared`.
With shared pointers, one can also see how many pointers are pointing to the object at any given time using the `use_count` method.

When executing this code we get the following printed to the console
```
Creating shared object
Use count: 1
Beginning of outer scope
Creating Person Henrik with shared object 0x145e06808
Use count: 2
Beginning of inner scope
Creating Person John with shared object 0x145e06808
Use count: 3
End of inner scope
Deleting John
End of outer scope
Use count: 2
Deleting Henrik
Use count: 1
End of function main
Deleting shared object
```
Notice that the use count goes up every time we create a new person that holds a pointer to the object and that the use count goes down when the person object goes out of scope. Finally, the shared object is deleted when the main function ends.


### When to use `unique_ptr` vs. `shared_ptr` vs. raw pointer

The [C++ core guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-resource) explain very well when to use different types of pointers.

Use raw pointers if the aim is to allocate the object on the stack.

Use smart pointers if the object pointed to is owned by another object. For example, in the shared pointer example, each instance of `Person` owns a reference to the shared object. For the `Array` class, the data array is owned by the `Array` instance. However, in this particular case, we are trying to mimic what is implemented by `std::vector`, and `std::vector` is using raw pointers under the hood. Therefore, it is difficult to avoid using raw pointers at all. To quote the [C++ core guidelines R3](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#r3-a-raw-pointer-a-t-is-non-owning):
> This problem cannot be solved (at scale) by transforming all owning pointers to unique_ptrs and shared_ptrs, partly because we need/use owning “raw pointers” as well as simple pointers in the implementation of our fundamental resource handles.

We will go into more detail about implementing a Dynamic Array in {ref}`arraylist`, and we will indeed use raw pointers to do so. That said, in most real-world scenarios, one would use smart pointers.

When it comes to `unique_ptr` versus `shared_ptr`, a `unique_ptr` is preferable, except when needing multiple pointers to the same object. In that case, it is usual to upgrade the pointer to a shared pointer.

## References

```{bibliography}
:filter: docname in docnames
```
