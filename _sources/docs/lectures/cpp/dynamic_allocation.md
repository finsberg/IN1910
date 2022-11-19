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

In this lecture we will continue looking a bit more at pointers and how they relate to arrays. We will also use what we have learned about object oriented programming to design a few classes for making list objects.


## Some repetition

Recall that we can create *pointer* variables, that store the memory address of some data. We can for example create an *integer pointer* as follows:
```C++
int a = 12; // integer variable
int *b;     // integer pointer
```
Here, `b` will be a pointer, because we use the asterisk (\*) when declaring it's type. To make `b` point at `a`, meaning the variable is storing the memory address of `a`, we use the address-of operator:
```C++
b = &a; // make b point at a
```
Now `b` points at `a` and we can use it to access and change `a`, however, recall that we cannot do so directly, if we for example attempt to print it out:
```C++
cout << b << endl;
```
We do not get the value of `a` (which is 12), but instead the *value* of `b`, which is the memory address, which will look something like:
```
0x7ffc072c388c
```
To actually get the variable a pointer is pointing to, we use the dereference operator:
```C++
cout << *b << endl;
```

| expression | can be read as   |
| ---------- | ---------------- |
| int i      | integer variable |
| int *p     | pointer variable |
| *x         | pointed to by x  |
| &x         | address of x     |


Also recall that we can set a pointer to point at "nothing":
```C++
b = nullptr;
```

## Pointers to objects

Let's say we create a struct
```C++
struct GridPoint
{
    int x;
    int y;
    int z;
};
```
We can then create an instance of this struct, and access its members using dot-notation:
```C++
GridPoint start{10, 10, 0};
cout << start.x << endl;
cout << start.y << endl;
cout << start.z << endl;
```
We can also make a pointer to the object:
```C++
GridPoint *sp = &start;
```
Now, if we want to access one of the member attributes of the underlying object, we first need to dereference the pointer, and then use dot-notation:
```C++
cout << (*sp).x << endl;
```
We need the parenthesis to get the right order of operations. This syntax works, but is often regarded cumbersome. Instead of dot syntax, it is common to draw an arrow:
```C++
cout << sp->x << endl;
```
The arrow (`->`) means the member attribute of the object pointed at, and thus is equivalent to writing `(*sp).x`.

| expression | can be read as                     |
| ---------- | ---------------------------------- |
| x.y        | member y of object x               |
| x->y       | member y of object pointed to by x |
| (*x).y     | member y of object pointed to by x |


## Arrays and Pointers

We have briefly shown how arrays can be created, for example:
```C++
int x[100];
```
Here, `x` will be an array of 100 ints. We can access these by indexing: `x[0]`, `x[1]`, $\ldots$, `x[99]`.

Earlier, we stated that an array will be *contiguous* in memory, i.e., each element follows each other directly. We can check this statement by writing out the memory addresses:
```C++
cout << & x[0] << endl;
cout << &x[1] << endl;
cout << &x[2] << endl;
cout << &x[3] << endl;
```
Which prints out:
```C++
0x7ffed0407920 0x7ffed0407924 0x7ffed0407928 0x7ffed040792c
```
Note that the memory address increases by 4 every step (it goes 8->c because it is hexadecimal), this is because memory addresses are in terms of byte (8 bits), and integers are 32-bit variables.

If we write out the array variable itself:
```C++
cout << x << endl;
```
we get the memory address of the first element `x[0]`:
```
0x7ffed0407920
```
This indicates that the array variable `x`, is almost the same as a pointer to the first variable of the array.

Let us highlight this in another way. Look at the following code snippet:
```C++
int x[] = {2, 4, 6, 8, 10, 12};
int *y = &x[2];
```
Here we make an array, and then make an integer pointer and set it to point at the third element, with a value of 6. However, because array variables behave much like pointers to the first element, the reverse is also true. Now `y` will behave like an array:
```C++
cout << y[0] << " ";
cout << y[1] << " ";
cout << y[2] << " ";
cout << y[3] << endl;
```
This is because the square bracket indexing in C++ indicates looking at the next elements in memory. `y` will therefore behave just like an array. We could also have accessed the elements using *pointer arithmetic*:
```C++
cout << *(y) << " ";
cout << *(y + 1) << " ";
cout << *(y + 2) << " ";
cout << *(y + 3) << endl;
```
Here, dereferencing `y` itself gives the first element, by computing `y + 1` we go the the next integer in memory, which would be element 2, and so on.


In short, a pointer is variable that stores the memory address of some data type. If these data lie contiguously in memory, then having the address of the first element is all we need to reference the whole set. Therefore, an `int *` pointer, can point to a single integer, or to a whole sequence of them. Note that the pointer itself does not know how many elements it points at. An array does not know how many elements it contains, which is why you won't get an `IndexError` if you go out of bounds, you get undefined behavior. Be careful!


| expression | can be read as                 |
| ---------- | ------------------------------ |
| x[0]       | first object pointed to by x   |
| x[1]       | second object pointed to by x  |
| x[n]       | (n+1)th object pointed to by x |


## Dynamic Memory Allocation

So far we have seen how to create a pointer object, and how to make it point at something. We have also seen how to point it at "nothing" (aka null). However, we have only pointed it at things that already exist. However, it is possible to get a pointer to point at something brand new. Take a look at the following example:
```C++
int *x;
x = new int;
*x = 5;
```
Here we first create an integer pointer. Then we say we want a new integer object to be made, and its address to point to it. An interesting consequence of this is that we have a variable that *is not named*. We can only access it through our pointer.

Using the `new` keyword in this way is referred to as *dynamic memory allocation*.

### Lifetime of Variables

In C++, things are automatically destroyed once they go out of scope. If you for example define a vector inside a function, then that vector simply ceases to exist once that function finished. Any dynamically allocated memory however, sticks around. Let us look at an example.

We have discussed how arrays are so efficient because they are contiguous in memory, but pointed out that the arrays do not know their size. We therefore decide we want to make a class called `Array` that stores both the data array and the size of it as a single object. We first define the object as
```C++
class Array
{
  public:
    int *data;
    int size;
};
```
Where `data` is a pointer to the first element of the underlying array, and `size` the number of elements.

Next we turn to making the constructor. When we make the constructor we want to take in the number of elements we want as an integer. The constructor should then allocate the memory of the array, set all the elements to zero, and point the `data` pointer to this array. You might try to do the following, but **it will not work:**
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
While this looks reasonable, there is a big problem. Whenever a function finishes, everything created inside that function is automatically destroyed. As the array is created inside the constructor, it is destroyed too. Our pointer is set to point at this array, but if the thing pointed at is destroyed, the pointer won't be much good.
If we try to run the following code
```C++
Array a(10);
for (int i = 0; i < a.size; i++)
{
    cout << a.data[i] << " ";
}
```
it produces the output
```
0 1 31872064 1 31872064 1 30535429 1 31872064 1
```
and this output will change every time you run the program.

However, when using dynamic memory allocation, the data is not destroyed at the end of the function. To dynamically allocate an array, we do the following:
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
Now we see that we get the expected results.

(scope-and-lifetime)=
### Scope and lifetime
A scope is a the region or section where a variable can be accessed and you can think of the scope as the inner most curly braces (`{}`) that encapsulates the variable declaration. This could be in a function, but you can also simple create a scoped variable inside a function. The lifetime of an object is the portion of the program execution during which store is guaranteed to be reserved for it.

Consider the following code
```c++
int main()
{
    int *p;
    {
        int x = 5;
        p = &x;
    }
    cout << *p << "\n";
    return 0;
}
```
Here we define an integer pointer `p` and then inside a local scope (which we just create using curly braces) we create an integer variable `x` and points `p` at it. The problem with this code is that when we exit the scope and prints out the value that `p` points to, `x` does not exist anymore, and so `p` points at some address in memory that is not owned by the program anymore. Note that, you will probably still see `5` printed out on the console, but there is no guarantee that the value stored at this memory address will remain `5`. We call this *undefined behavior* and this is the root of some of the most tricksiest bugs to debug.

## Deallocating Memory and Garbage Collection

In Python, you are used to having built-in garbage collection. Garbage collection is a term for automatic processes that collects unused variables and destroys them for us, freeing the underlying memory. In Python, any variable that no longer has a name referencing it, is flagged for garbage collection and is destroyed.

In C++, there is no garbage collection. Instead, data will be destroyed when it goes out of scope. However, as we just showed you, dynamic memory allocation survives even when it goes out of scope. This means dynamically allocated objects will continue to take memory until we ourselves destroy the objects.

If we *do not* de-allocate memory we have created dynamically, it will continue to take space until our program finished. Often, this isn't a problem, but in certain situations, it can actually lead to program-crashing bugs.

### Memory Leaks

Earlier, we showed this snippet:
```C++
int *x;
x = new int;
*x = 5;
```
If we now do a new dynamic allocation:
```C++
x = new int;
```
Then `x` will point to a new object, but the old one is never freed. The other integer has no name, and we no longer have any pointer to it. We have reached a point where a piece of memory is locked down until the entire program terminates and we have no way of accessing or using that variable. This is referred to as a memory leak.

A small memory leak is of no issue and not noticeable. However, if you get a large memory leak, the machine will run out of memory and the program and OS will grind to a halt, most likely requiring termination of the program or even a full reboot of the system.


Let us create a program that on purpose leaks a lot of memory:
```C++
void doomsday()
{
    while (true)
    {
        new int;
    }
}
```
Here we define an infinite loop. For each iteration we allocate a new integer in memory, but they are never deallocated. This means, for each iteration of the loop, our program will use a bit more memory (32 bits to be exact).

If we compile our `doomsday.cpp` code, you probably won't get any warnings. But if you now run it, you definitely will get some problems. The program will ask for more and more memory from the system, and never give any back. The program never aborts itself or stops, so it is up to the system to recognize that this program is not acting right and terminate it. Wether or not that actually happens depends on your system. In the worst case, all memory will be hogged by the doomsday program, leaving non for the system. The only way to regain control in this scenario is now a hard reboot of the machine. Not ideal!

If you want to know how to debug such memory leaks, please consult the [debugging section](cpptools.md).

### Memory leaks in Practice

In practice, memory leaks are hard to detect. The leak doesn't build up as fast as here, but does so over hours or days. When testing software, we often opt for small, efficient tests. And so often everything will seem fine, until we start a long simulation and we get an issue.

Memory leaks, and other similar bugs, sneak into a surprising amount of professional software, and is a major contributor to [*software aging*](https://en.wikipedia.org/wiki/Software_aging), where things seem to become unresponsive or stop functioning when running over a longer time, but return to normal after a reboot.

The wikipedia article on memory leaks has a [good example](https://en.wikipedia.org/wiki/Memory_leak#An_example_of_memory_leak) for how a seemingly "trivial" program for an elevator could contain a memory leak.


### Freeing memory

So if dynamically allocated memory has to be freed, how do we do so? It is quite simple, we use the `delete` keyword:
```C++
int *x;
x = new int;

delete x;
```

Note that `delete x` will free the thing pointed at by `x`, the pointer will still exist and be usable. If we are freeing an allocated array, we instead use `delete[]`:
```C++
int *x;
x = new int[200];

delete[] x;
```

## The Destructor

Returning to our `Array` class example. We defined the following class:
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
This class works well, and we can now use it inside other functions where we need arrays, however, at the end of those functions, our newly created `Array` object will automatically be destroyed. However, the dynamically allocated memory inside the object won't be!

To ensure that the dynamic memory is deallocated with the object, we need to define a *destructor*, which is called automatically when an object goes out of scope and is destroyed. Where as the constructor is named the same as the class, the destructor is named the same with a tilde (~) in front:
```C++
~Array()
{
    delete[] data;
}
```
You could try this yourself with the simple test program:
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
If you run this program without implementing the deallocator, the memory usage of the program will skyrocket. If you do implement the deallocator, then everything is fine, as every function call properly destroys the object and all the underlying data.

## Stack vs Heap

In C++, and many other programming languages, we refer to two different forms of memory: the stack and the heap. Everything you create lives in one of these two memory spaces. Variables you create normally will live on the stack. Every function has its own stack space, and when the function finished, the stack is emptied and the variables destroyed. When you declare variables dynamically, you create them on the heap instead, where nothing is automatically deallocated.

We won't talk much about stack and heap, but you might run across it in other sources, or if you ever learn more about C++ in more dedicated courses.

(smart-pointers)=
## Smart Pointers

Knowing about how memory is acquired and released will improve the way you program. This is also one reason why knowing how to program in a lower level programming language such as C++ will improve your programming skills in general.

However, forgetting to delete objects that are allocated on the heap is a huge source for bugs and memory leaks, and therefore C++ programmers try to avoid called `new` and `delete` as much as possible.

The recommendation from the C++ community is to use a principle known as *Resource Acquisition Is Initialization* (RAII). According to RAII, you should only acquire resources in the constructor and release them in the destructor (just like we did in the `Array` class).

On way to ensure this is to use *smart pointers*. A smart pointer is a pointer that owns the object it points to, and make sure that the memory it points to is automatically deallocated once the pointer goes out of scope.

To use smart pointer we need to include the `<memory>` header and compile with the flag `-std=c++14`.

### First example with smart pointers

Let us first have a look at a very simple usage of a smart pointer and compare this with the *raw* pointer version.


````{tab} C++ (raw pointer)
```c++
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
```c++
#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<int> p = std::make_unique<int>(42);
    std::cout << *p << "\n";
}
```
````

First thing we see is that we need to include the `<memory>` header, which is where the declarations for the smart pointers are defined.

Next, instead of `p` being of type `int*` it is now of type `std::unique_ptr<int>`. We say that `p` is a *unique pointer*. A unique pointer is one type of smart pointers. There are also other types of smart pointers, for example *shared pointer*. We will see shared pointer later.

We also se that that way we create a unique pointer is by using the function `std::make_unique<type>(value)` for some type (here `int`) and some value (here `42`).

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
Here we have a `Person` class that takes a name of type `string` in the constructor. It has a method for saying hello, and once the destructor is called, it print a goodbye message.

#### Allocation on the stack

We can write a simple program that allocates an instance of a Person on the stack as follows:

```c++
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
Let us carefully walk through this example. The `main` function starts with an open curly brace (`{`) which defines the beginning of a scope. Once the program reaches the closing brace (`}`), i.e the end of the scope, any variables declared on the stack will be freed automatically, see {ref}`scope-and-lifetime`.

First we print a message saying `Beginning of scope` to indicate that the scope is beginning. Then we create an instance of `Person` called `person` with the name `"Henrik"`. Next we create a pointer to this object and use the pointer to say hello by calling the `say_hello` method. Next we print a new message saying `End of scope` to indicate that the scope is ending and finally, before the `main` function is ending we print a message saying `End of function main`.

If we compile and run this code, it will give the following output
```
Beginning of scope
Hello from Henrik
End of scope
Goodbye from Henrik
End of function main
```
And we see that also the destructor is called at the end of the scope as expected.


#### Allocation on the heap using raw pointers

Now let us rewrite the example by allocating the object on the heap instead. Remember, that allocations happening on the stack need to be known at compile time, meaning that in most cases you need to allocate some memory on the heap to account for user input. As we have seen there are two options when allocating objects on the heap; using raw pointer or smart pointer. Let first look at the example using a raw pointer:

```c++
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
We use the `new` keyword to indicate the the object is allocated on the heap, and we must also remember to use `delete` on the pointer at the end of the scope. The output from this program is the same as the output from the program above the allocated the object on the stack, i.e
```
Beginning of scope
Hello from Henrik
End of scope
Goodbye from Henrik
End of function main
```
Now, this is a very simple example, but it is easy to imaging a more complicated use case (for example the `Array` class). Having to explicitly call `delete` can potentially be forgotten, especially if the call to `delete` has to happen at a different location in the code than where it was allocated (which is usually the case).

Lets see what happens if we forget to call delete, i.e lets try to run the following program
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
The program compiles without any error and output is
```
Beginning of scope
Hello from Henrik
End of scope
End of function main
```
We can see that there is no call to the destructor. We have a memory leak. If this code was part of a long running program, and this code run repeatedly then we might end up in a situation when the computer runs out of memory and crashes.


#### Allocation on the heap using smart pointers
To save us from needing to call delete while ensuring that memory allocated on the heap is freed, we can use smart pointer. Lets look at the same example using smart pointers (note that the `<memory>` header is included in the part of the code where the `Person` class is defined):

```c++
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
```c++
std::unique_ptr<Person> p = std::make_unique<Person>("Henrik");
std::unique_ptr<Person> p1 = p;
```
If you want several different pointers to point to the same object we need to use *shared pointers* instead of unique pointers.

Consider the following code, where each person object now holds a pointer to some shared object

```c++
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
Here we have defined a `struct` called `SharedObject` and each instance of `Person` holds a shared pointer to an in instance of `SharedObject` which is named `_obj`. We also print a little message in the constructors and destructors.

Let us write a simple main function that creates one shared object that is used by two different instances of `Person`. To make it all a bit more interesting, let us define the shared object in the scope of the `main` function and let us create the to `Person` object within different scopes.

```c++

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
Creating a shared pointer is very similar to creating a unique pointer; simple swap out `unique` with `shared`.
With shared pointers we can also see how many pointer are pointing to the object at any given time using the `use_count` method.

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
We notice that the use count goes up every time we create a new person that holds a pointer to the object, and that the use count goes down when the person object goes out of scope. Finally the shared object is deleted when the main function ends.


### When to use `unique_ptr` vs `shared_ptr` vs raw pointer

The [C++ core guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-resource) explains very well when to use different types for pointers.

Use raw pointers if you want to allocate the object on the stack.

Use smart pointers if the object pointed to is owned by another object. For example in the shared pointer example, each instances of `Person` owns a references to the shared object. For the `Array` class the data array is owned by the `Array` instance. However, in this particular case we are trying to mimic what is indeed implemented by `std::vector`, and `std::vector` is using raw pointers under the hood. Therefore, it is difficult to avoid using raw pointers at all. To quote the [C++ core guidelines R3](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#r3-a-raw-pointer-a-t-is-non-owning):
> This problem cannot be solved (at scale) by transforming all owning pointers to unique_ptrs and shared_ptrs, partly because we need/use owning “raw pointers” as well as simple pointers in the implementation of our fundamental resource handles.

We will go into more details about implementing a Dynamic Array in {ref}`arraylist`, and we will indeed use raw pointers to do so. Thats said, in most real world scenarios you would smart pointers.

When it comes to `unique_ptr` vs `shared_ptr` you should prefer `unique_ptr`, but if you need more pointers to the same object then you can upgrade the pointer to a shared pointer.
