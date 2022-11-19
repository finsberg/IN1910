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

# Linked Lists

This lecture marks the start of a new topic in IN1910, namely the Algorithms and Data Structures part of the course, which we will spend the next two weeks on. We have spent the *previous* two weeks of IN1910 learning some C++. As mentioned, the main goal of learning C++ was to familiarize you with C-style programming syntax. We are through covering new material in C++, but will spend the next two weeks using it for our exploration of data structures, so you will get further possibility to learn to use the language more.

## Data Structures and Algorithms

A data structure is how data is organized and managed. More precisely, it is about how a collection of data items are stored collectively, how they relate to each other, and what operations we can perform on them. Understanding data structures is important when trying to make efficient programs, because different problems and implementations calls for different data structures.

Algorithms are tightly connected to data structures, because to implement a data structure, we need to understand the algorithms needed to get that data structure to work. But also because implementing an algorithm to solve some problem will rely on what data structure you choose to work with, different underlying structures call for different algorithms.

Data structures and Algorithms is one of the fundamental topics of computer programming. This is reflected in the fact that there are numerous books and university classes called precisely "Data Structures and Algorithms", or alternatively: "Algorithms and Data Structures". We only have a few weeks dedicated to this topic, so it is obvious that we cannot give you a proper introduction into the topic. However, we aim to give you a small taste, and an understanding of what a data structure actually is and why it is important.

## External Resources

At UiO, the course [IN2010 – Algorithms and Data Structures](https://www.uio.no/studier/emner/matnat/ifi/IN2010/index-eng.html) (previously INF2220) focuses more in-depth on the topic. The course comes highly recommended for anyone who wants to become a better programmer, and it's pretty much a prerequisite course to take if you want to go further into computer science.

As mentioned, there are also hundreds of books on this subject, some probably better than others. Not only are there many to choose from, there are probably several to choose from dedicated for each programming language you might want to use. We will recommend the book used by IN2010, [*Algorithm Design and Application* by Goodrich and Tamassia](https://www.wiley.com/en-us/Algorithm+Design+and+Applications-p-9781118335918) as that is probably the best choice if you want to get a dedicated book and might be taking IN2010 in the future.

```{figure} ../../figures/goodrich_and_tamissa.jpg
---
width: 175px
name: goodrich-and-tamissa
---
Book used by IN2010, [*Algorithm Design and Application* by Goodrich and Tamassia](https://www.wiley.com/en-us/Algorithm+Design+and+Applications-p-9781118335918).
```

Another excellent resource to use are the teaching materials for the [MIT course 6.006 *Introduction to Algorithms*](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/). The course materials are openly available through Open CourseWare, with recorded video lectures. This course covers the theory behind many data structures and algorithms, and so works well with any programming language, but mostly uses Python for example code. Note that 6.006 goes into many topics we won't cover, but they also have lectures that cover what we do in IN1910.


## Data Structures vs Abstract Data Types

In the previous lecture, we covered [Dynamic Arrays](https://en.wikipedia.org/wiki/Dynamic_array), also known as Array Lists. And this is an example of a data structure, as it is a specification on how data values are to be stored, and interacted with. In that lecture, we implemented a class, and then had to continuously swap to think between how things worked "inside the class", and how they looked from "outside the class", i.e., how the class is actually used.

We now want to formalize these concepts a bit. The term *data structure* refers to the specific and concrete implementation of how data is represented and stored. It is a low-level construct, that we mostly have to think about when *implementing* something.

When using the class however, we instead talk about the *data type*, or even the [*abstract data type*](https://en.wikipedia.org/wiki/Abstract_data_type) (ADT). An abstract data type is, as the name implies, a more abstract definition and is a mathematical model for the behavior of the construct from the *users* perspective. Specifically it is the collection of possible values to be stored in the construct, the possible operations on that data, and the behavior of those operations.

A data structure is the low-level construct from the perspective of the implementer, while the abstract data type is the high-level construct, built on top of the data structure, which is what the user actually interacts with.

An example of an abstract data type is the [list ADT](https://en.wikipedia.org/wiki/List_(abstract_data_type)). This is a specification that a *list* is something which can store a sequence of elements, has methods to find the number of elements stored, methods for inserting or appending new elements, etc. You should be familiar with this ADT, because Python lists for example, would be a specific implementation of this list ADT. Another example of an ADT is the [associative array](https://en.wikipedia.org/wiki/Associative_array), while the name might be unfamiliar to you, you have probably used this ADT, because python dictionaries are associative arrays.

Note that if we want to implement to specific ADT, say for example a list, there will often be many different underlying data structures we can choose when we implement it. In the case of the list, dynamic arrays would be a natural choice, as we have already seen. Another option would be *linked lists*, a data structure we will cover in this lecture.

```{figure} ../../figures/data_structure_vs_adt.png
---
width: 400px
name: data-structure-vs-adt
---
An abstract data type is the interface the user has to interact with, it defines the possible operations on the data and how they behave. The underlying data structure is more specific to how data is represented and stored in memory, it is mostly the implementer who has to think about the data structure. As shown, different data structures can be used to implement a given ADT, lists can for example be made with dynamic arrays *or* with linked list. This will be different from the perspective of the implementer. But when using the class, we won't really need to think about the underlying data structure, as the same operations will be supported.
```



## Linked Lists

We now turn to look at linked lists, which is an alternative data structure to dynamic arrays for implementing lists. Unlike dynamic arrays, linked lists do not rely on storing data in arrays, but instead store each element of the list in an individual structure called a *node*.

A node object stores the value of the element itself, but it also contains a pointer to another node. We can use this pointer to *link* different nodes to each other and create a *linked list*. In this lecture we will only consider lists that store *integers*. However, the value field of the nodes could simply be changed to store any kind of object. In C++, it would be best to use *templating* to define a single list class that can contain any type of data, but we disregard this here to keep things as simple as possible.


```{figure} ../../figures/single_node.png
---
width: 175px
name: single-node
---
A single node object.
```

When link a series of nodes, they form a linked list. We let the list end by having the final node point at a nullptr. In Figure 3, we have a chain of linked nodes, which would correspond to a list `[47, 3, 12, 99, 23]`.


```{figure} ../../figures/node_chain.png
---
width: 800px
name: node-chain
---
A chain of node objects.
```

To simplify our drawings of the linked list, we change to drawing our nodes as simple circles, writing their value inside, and the pointer as an arrow.


```{figure} ../../figures/simplified_node_chain.png
---
width: 800px
name: simplified-node-chain
---
A simplified drawing of a linked list.
```

This structure defines a clear sequence of integer values. We can also iterate over this list, if we have a reference to the first value, we can do something to this value, for example print it, and then use the `next` pointer to move to the next element in the list, and thus iterate our way through it.


### Making the Nodes

Implementing the node itself is very simple, we can do it as a simple struct:
```C++
struct Node
{
    int value;
    Node *next = nullptr;
};
```
Note especially the asterisk, making `next` a node *pointer*. We will give this pointer a default value of `nullptr` which means that if we do not provide a value of this to the constructor then it will be set to `nullptr`.

### Linking Nodes

With the `Node` struct defined, we can try to create a few nodes and link them as follows:
```C++
Node a{12};
Node b{57};
Node c{36};

a.next = &b;
b.next = &c;
```
However, this is *not* how we want to use our linked list, instead we want to build a list class based on the nodes. So let us define a `LinkedList` class.


### Creating a list class based on linked list

To interact with our linked list, we need to have a reference to the first node of our linked list. This node is often referred to as the *head* of the list. If our list is empty, the head of the list must not point at anything. We can then set up the class as follows:
```C++
class LinkedList
{
  private:
    Node *head = nullptr;

  public:
    LinkedList()
    {
    }
};
```


### Appending to LinkedList

Now, let us try to make an `append` method, for adding an element at the end of the list. Let us first consider how to do this for a completely empty list.

For an empty list, the `head` pointer, is pointing at `nullptr`. We want it to instead point to a new node. To do this, we need to use the `new` keyword to dynamically allocate memory for a new node. So for an empty list, we would do:

```C++
void append(int val)
{
    if (head == nullptr)
    {
        head = new Node{val};
    }
}
```
However, what do we do if there already are some elements in the list? In this case we *shouldn't* change the `head` pointer, because appending should add the new element to the end of the list, the front of the list should be unchanged.

What we want to do, is get the `next` pointer of the final node in the list to point to the new list, so first need to get access to this final node. We can do this by iterating through all nodes in the list, using `next` on each node to move on step down the list. How do we know we have reached the end? The first node to point at a nullptr must be the end. So we can use a while-loop:
```C++
void append(int val)
{
    Node *new_node = new Node{val};
    if (head == nullptr)
    {
        head = new_node;
        return;
    }

    Node *current = head;
    // Move node until we are at the last element
    while (current->next != nullptr)
        current = current->next;

    current->next = new_node;
}
```
Take a minute to go through this code. Especially verify that it works if the list has 0 elements before appending, if it has exactly 1 before appending, and if it has more than 1 element before appending. We will add a test briefly to ensure that our program is working as expected, but first we need to also add a method to retrieve elements. Before doing that let us discuss one way we can make this method more efficient. At the moment we need to go through the entire list to find the last node in order to append an element. If we already had a pointer to the last element we could append the element directly. It is common to add a pointer called *tail*, which is similar to *head* only that it points to the last element instead of the first one.

### Implementing the indexing operator
We will now implement an indexing operator in order to retrieve elements at specific indices in the list similar to what we did for {ref}`ArrayList <array-list-indexing>`.
One possible version could be the following
```c++
int &operator[](int index)
{
    Node *current = head;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current->value;
}
```
Here we make a `Node` pointer that starts at `head`, and the we move the pointer to the next pointer the same number as the index provided. Looks simple, right? Let's add a little test for this called `test_append_and_get` which look as follows
```c++
void test_append_and_get()
{
    LinkedList ll{};
    ll.append(0);
    ll.append(1);
    assert(ll[0] == 0);
    assert(ll[1] == 1);
}
```
Compiling and running this works fine, but can you see any problems with the implementation? What happens if you try to access an element outside the bounds of the list, e.g
```c++

int main()
{
    LinkedList ll{};
    std::cout << ll[0] << "\n";
    return 0;
}
```
Compiling an running this gives the following output
```
$ ./linked_list
[1]    23683 segmentation fault  ./linked_list
```
We would like to add a bit better error message in this case, telling that the user is trying to access an element outside the bounds of the list. We can modify the `operator[]` method as follows
```c++
int &operator[](int index)
{
    if ((index < 0) || (index >= length()))
        throw std::range_error("Index out of bounds") Node *current = head;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current->value;
}
```
In the first line of this function we now check wether the index is negative or larger than the length of the list, and if it is then we throw an error. Note that we need to also need to add the following line at the top of the file
```c++
#include <stdexcept>
```

Now we just need to implement the `length()` function. For our implementation, we could define a method that finds the number of elements through iterating through them:
```C++
int length()
{
    Node *current = head;
    int _size = 0;

    while (current != nullptr)
    {
        _size++;
        current = current->next;
    }
    return _size;
}
```
This would work nicely, but it is not very efficient to have to iterate through the entire list every time we want to know the number of elements we have. To improve this, and make the `length` method more efficient, we could simply add a `_size` field to the class itself, initializing it to 0 (for an empty list) and be sure to update it manually every time an element is added or removed. Say we define a private attribute `int _size;`, then we can make our length method as:
```C++
int length()
{
    return _size;
}
```
Compiling and running the program again now gives us the following output
```
$ ./linked_list
libc++abi: terminating with uncaught exception of type std::range_error: Index out of bounds
[1]    23951 abort      ./linked_list
```
Let us also add a test that make sure that a `range_error` is thrown when we try to access an element outside of it's bounds. This could be implemented as follows
```c++
void test_access_element_out_of_bounds_throw_range_error()
{
    LinkedList ll{};

    bool throwed_range_error = false;
    try
    {
        int x = ll[0];
    }
    catch (const std::range_error &e)
    {
        throwed_range_error = true;
    }
    assert(throwed_range_error);
}
```
Here we first make an empty list named `ll`. Then we create a `bool` variable called `throwed_range_error` which is set to `false`. Next we try to access the first element in the empty list. This should throw a `range_error`, and if it does we turn the variable `throwed_range_error` into a `true` value. Finally we assert that the value is `true`.

```{admonition} Click to see the full source code
:class: dropdown

```c++
#include <cassert>
#include <iostream>
#include <stdexcept>

struct Node
{
    int value;
    Node *next = nullptr;
};

class LinkedList
{
  private:
    Node *head = nullptr;
    int _size = 0;

  public:
    LinkedList()
    {
    }

    void append(int val)
    {
        Node *new_node = new Node{val};
        _size++;
        if (head == nullptr)
        {
            head = new_node;
            return;
        }

        Node *current = head;
        // Move node until we are at the last element
        while (current->next != nullptr)
            current = current->next;

        current->next = new_node;
    }

    int length()
    {
        return _size;
    }

    int &operator[](int index)
    {
        if ((index < 0) || (index >= length()))
            throw std::range_error("Index out of bounds");
        Node *current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current->value;
    }
};

void test_append_and_get()
{
    LinkedList ll{};
    ll.append(0);
    ll.append(1);
    assert(ll[0] == 0);
    assert(ll[1] == 1);
}

void test_access_element_out_of_bounds_throw_range_error()
{
    LinkedList ll{};

    bool throwed_range_error = false;
    try
    {
        int x = ll[0];
    }
    catch (const std::range_error &e)
    {
        throwed_range_error = true;
    }
    assert(throwed_range_error);
}

int main()
{
    test_append_and_get();
    test_access_element_out_of_bounds_throw_range_error();
    return 0;
}
```

(linked-list-organize)=
### Organizing the code into `linked_list.cpp` and `test_linked_list.cpp`
Similar to what we did with `ArrayList` we would like to keep the test code separate from the implementation of the `LinkedList` (see {ref}`array-list-two-files`). To do so we will implement the class `LinkedList` in a file called `linked_list.cpp` and the tests together with the `main` function in the file `test_linked_list.cpp`. To do so we simply move the function `main`, `test_append_and_get` and `test_access_element_out_of_bounds_throw_range_error` to the file `test_linked_list.cpp` such that `linked_list.cpp` looks as follows
```c++
// linked_list.cpp
#include <stdexcept>

struct Node
{
    int value;
    Node *next = nullptr;
};

class LinkedList
{
  private:
    Node *head = nullptr;
    int _size = 0;

  public:
    LinkedList()
    {
    }

    void append(int val)
    {
        Node *new_node = new Node{val};
        _size++;
        if (head == nullptr)
        {
            head = new_node;
            return;
        }

        Node *current = head;
        // Move node until we are at the last element
        while (current->next != nullptr)
            current = current->next;

        current->next = new_node;
    }

    int length()
    {
        return _size;
    }

    int &operator[](int index)
    {
        if ((index < 0) || (index >= length()))
            throw std::range_error("Index out of bounds");
        Node *current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current->value;
    }
};
```
and `test_linked_list.cpp` looks as follows
```c++
#include <cassert>
#include <iostream>

#include "linked_list.cpp"

void test_append_and_get()
{
    LinkedList ll{};
    ll.append(0);
    ll.append(1);
    assert(ll[0] == 0);
    assert(ll[1] == 1);
}

void test_access_element_out_of_bounds_throw_range_error()
{
    LinkedList ll{};

    bool throwed_range_error = false;
    try
    {
        int x = ll[0];
    }
    catch (const std::range_error &e)
    {
        throwed_range_error = true;
    }
    assert(throwed_range_error);
}

int main()
{
    test_append_and_get();
    test_access_element_out_of_bounds_throw_range_error();
    return 0;
}
```
Note that we also need to include `linked_list.cpp` inside the `test_linked_list.cpp` file.

To compile the binary executable you should be able to simply compile the file `test_linked_list.cpp`
```
c++ -std=c++14 test_linked_list.cpp -o linked_list
```

### Refactoring the indexing operator

When accessing an element at an index we first check whether the index provided is out of bounds, then we need to find the relevant node and finally we return the value stored at that node. We can imaging that both checking whether an index is out of bounds and finding a pointer to a node at a given index might be useful in other methods as well. Moreover we should strive to make methods that do only one thing, while the current methods is now doing three things. We will make two new private methods; one for checking the bounds, and one for getting a node at a given index. These could be implemented as follows
```c++
void check_index_out_of_bounds(int index)
{
    if ((index < 0) || (index >= length()))
        throw std::range_error("Index out of bounds");
}

Node *find_node_at_index(int index)
{
    Node *current = head;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current;
}
```
and then we can update `int operator[]` as follows
```c++
int &operator[](int index)
{
    check_index_out_of_bounds(index);
    Node *current = find_node_at_index(index);
    return current->value;
}
```
You should now recompile and make sure that your tests are still passing.


### Destroying the list

As we are dynamically allocating the nodes with the `new` keyword, we should also deallocate the nodes when they are no longer useful. Before implementing the destructor, let us first verify that we indeed have a memory leak. One method is to use a simple tool to check the memory use on execution, one such tool is *valgrind* (see also [debugging section](cpptools.md)). This tool is available on Unix systems, for Windows, you will need to look somewhere else, for example the Visual Leak detector made for Visual C++. It is also available on th IFI machines.

After installing valgrind, you can run
```C++
valgrind-- tool = memcheck<your executable>
```
To run an executable and see if it seems reasonable. Running the tests for the `linked_list` using `valgrind` now gives us the following output
```
$ valgrind --tool=memcheck ./linked_list
==1993315== Memcheck, a memory error detector
==1993315== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1993315== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==1993315== Command: ./linked_list
==1993315==
==1993315==
==1993315== HEAP SUMMARY:
==1993315==     in use at exit: 32 bytes in 2 blocks
==1993315==   total heap usage: 5 allocs, 3 frees, 72,924 bytes allocated
==1993315==
==1993315== LEAK SUMMARY:
==1993315==    definitely lost: 16 bytes in 1 blocks
==1993315==    indirectly lost: 16 bytes in 1 blocks
==1993315==      possibly lost: 0 bytes in 0 blocks
==1993315==    still reachable: 0 bytes in 0 blocks
==1993315==         suppressed: 0 bytes in 0 blocks
==1993315== Rerun with --leak-check=full to see details of leaked memory
==1993315==
==1993315== For lists of detected and suppressed errors, rerun with: -s
==1993315== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
In this case we get information that some memory is leaked.


This is because when the program is finished and wrapping up, it starts deallocating and destroying variables. When the `primes` list is deleted, the dynamically allocated nodes are *not* (because we ran this before implementing the destructor method). So we see that we have "16 bytes in 1 blocks" marked as "definitely lost", this is our `head` node. In addition we have "indirectly lost" 16 bytes in 1 blocks, which is the other node in the append test. This other node aren't directly lost, but lost because we needed our `head` pointer to get to it.

Let us add a destructor method to our class. This method should go through the list, deallocating each node, one by one. When we destroy a node, we also loose access to its `.next` attribute, so we should copy this reference over to a temporary object, before we delete the node itself.
```C++
~LinkedList()
{
    Node *current = head;
    Node *next = nullptr;

    while (current != nullptr)
    {
        next = current->next;
        delete current;
        current = next;
    }
}
```

This seems reasonable, we have used one `new` for each node in the list, and this while-loop should have a `delete` for each node, meaning no memory should be leaked. But, as is always smart in programming, we should plan for mistakes and human error. So how can we verify we are not leaking any memory?

After implementing the destructor `~LinkedList` method, we rerun the analysis and get:
```
$ valgrind --tool=memcheck ./linked_list
==1993385== Memcheck, a memory error detector
==1993385== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1993385== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==1993385== Command: ./linked_list
==1993385==
==1993385==
==1993385== HEAP SUMMARY:
==1993385==     in use at exit: 0 bytes in 0 blocks
==1993385==   total heap usage: 5 allocs, 5 frees, 72,924 bytes allocated
==1993385==
==1993385== All heap blocks were freed -- no leaks are possible
==1993385==
==1993385== For lists of detected and suppressed errors, rerun with: -s
==1993385== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
Which tells us that all memory which was used was also freed at the end of execution, as desired. And thus no leaks exist in our simple test case. Note that this not guarantee that no leaks are possible in other use cases of the list, but it is a simple test that have supported our implementation.



### Overloading the constructor to take a list of elements
Let us now implement a new constructor that can take a list of elements through a `vector<int>` and that uses the append method to add elements to the list

```c++
LinkedList(std::vector<int> values)
{
    for (int v : values)
        append(v);
}
```
Note that you also need to add the line
```c++
#include <vector>
```
at the top of the file. Let us also add a test to make sure that the constructor is working as expected.
```c++
void test_vector_constructor()
{
    LinkedList ll{{0, 1}};
    assert(ll[0] == 0);
    assert(ll[1] == 1);
}
```


### Printing a linked list

Now, let's add a `print`-method to print out the contents of the list. To do this we need to iterate through the list, printing out the value of each node. We keep going until we reach the end of the list:
```C++
void print()
{
    std::cout << "[";
    if (head != nullptr)
    {
        Node *current = head;
        while (current->next != nullptr)
        {
            std::cout << current->value;
            std::cout << ", ";
            current = current->next;
        }
        std::cout << current->value;
    }
    std::cout << "]\n";
}
```
Let us also add a test to make sure that we can print an empty list as well as a list with one element
```c++
void test_print()
{
    LinkedList ll{};
    ll.print();
    ll.append(0);
    ll.print();
}
```
The output when running this test should be
```
$ ./linked_list
[]
[0]
```


### Iterating over the Linked List

So far, we have iterated over the linked list a few times using the `next` of each node to take the next step, inside a while-loop:
```C++
Node *current = head;
while (current != nullptr)
{
    current = current->next;
}
```

Outside the loop however, we cannot iterate in the same way, because we have set `head` to private. And for good reason, we don't want a user of the list to have to think about the structure of the linked list and its implementation details, if they had access to `head` or had to use the nodes directly, it wouldn't be as elegant nor foolproof.

Instead we might think, we just implemented indexing, so we can just do
```C++
for (int i = 0; i < example.size(); i++)
{
    example[i];
}
```
To iterate through some list called `example`. However, if you recall how we implemented the get-operation, this is far from perfect, because to index element $i$, we started at the front of the list and iterated through it to reach $i$. In our for-loop here, we first refer to element 0, then element 1, then element 2. Every time we iterate over a new element, the get-operator will start iterating all the way at the head. This is far from perfect!

To get around this, we would like to implement our class in such a fashion that we could for example write:
```C++
for (int p : primes)
{
    cout << p << endl;
}
```
For a given list `primes`. This is the same syntax we can use on the `vector` class for example. To get this functionality, we have to create a custom *iterator* for our `LinkedList` class, and this *iterator* would keep track of the last visited node, and just use `next` to iterate one element, making the whole process effective.

However, we have not covered *iterators* in IN1910, and making them is finicky enough that we won't take the time to do this here.

### Inserting into front of the list

Sometimes, we might not want to insert elements at the end of the list, i.e., we do not want to "append" elements, instead we want to "pre"pend, or insert at the front. For our linked list, this is actually very simple! We simply need to make the new element our `head` and then point from our new node to the old head.

Because we `Node` can take the value as the first argument and the pointer to the next node as the second arguments, we can actually manage this in a single line:
```C++
void push_front(int val)
{
    head = new Node{val, head};
    _size++;
}
```
Let us add a little test to make sure this is working as expected
```c++
void test_push_front()
{
    LinkedList ll{{1, 2, 3}};
    ll.push_front(42);
    assert(ll.length() == 4);
    assert(ll[0] == 42);
}
```

### Inserting into middle of the list

Now, what if we instead want to insert into the middle of the list, say at index $i$? Well, then we need the node before it, i.e., node $i-1$ to point to the new node, and the new node to point at the node that was previously node $i$.

When performing these steps, we do not want to use `find_node_at_index` more than once, because iterating from 0 to $i$ more than once is really inefficient. So let us do as follows:
```C++
void insert(int val, int index)
{
    Node *prev = find_node_at_index(index - 1);
    Node *next = prev->next;
    prev->next = new Node(val, next);
    _size++;
}
```
Before moving on, we should verify that this also works if we are trying to insert at the last node of the list, as this might be an edge-case we got wrong that might lead to an error at a later time. We leave this as an exercise to the reader.

### Different inserts

If the different insert methods: `append`, `push_front` and `insert` got you confused, that is understandable. Let us compare them a little. First, the `insert` method inserts at any index in the list. If we do insert at index 0, this is the same as using `push_front`, if we do insert at the end of the list, i.e., index $N$ for a list with $N$ elements, we are effectively appending an element.

We draw the three situations below. If you are still confused, we recommend you draw up a linked list, and then try to insert elements by drawing in new nodes and moving pointers around yourself.

```{figure} ../../figures/insert_linked_list.png
---
width: 250px
name: insert-linked-list
---
Different way of inserting elements into the linked list.
```

```{admonition} Click to see the full source code
:class: dropdown

```c++
// linked_list.cpp
#include <iostream>
#include <stdexcept>
#include <vector>

struct Node
{
    // The value at the node
    int value;
    // Pointer to the next node
    Node *next = nullptr;
};

class LinkedList
{
  private:
    // Pointer to the first element in the list
    Node *head = nullptr;
    // Size of the list
    int _size = 0;

    /**
     * @brief Check whether the given index if out of
     * bound and throw a range error if it is
     *
     * @param index The index to be checked
     */
    void check_index_out_of_bounds(int index)
    {
        if ((index < 0) || (index >= length()))
            throw std::range_error("Index out of bounds");
    }

    /**
     * @brief Find the node at the given index
     *
     * @param index The index where you want the node
     * @return Node* A pointer to the node at the index
     */
    Node *find_node_at_index(int index)
    {
        Node *current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current;
    }

  public:
    // Default constructor
    LinkedList()
    {
    }

    // Constructor for a list of values
    LinkedList(std::vector<int> values)
    {
        for (int v : values)
            append(v);
    }

    // Destructor
    ~LinkedList()
    {
        Node *current = head;
        Node *next = nullptr;
        // Move node until we are at the last element
        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
    }

    /**
     * @brief Print values in the list
     *
     */
    void print()
    {
        std::cout << "[";
        if (head != nullptr)
        {
            Node *current = head;
            while (current->next != nullptr)
            {
                std::cout << current->value;
                std::cout << ", ";
                current = current->next;
            }
            std::cout << current->value;
        }
        std::cout << "]\n";
    }

    /**
     * @brief Append element to the end of the list
     *
     * @param val The value to be appended
     */
    void append(int val)
    {
        Node *new_node = new Node{val};
        _size++;
        if (head == nullptr)
        {
            head = new_node;
            return;
        }

        Node *current = head;
        // Move node until we are at the last element
        while (current->next != nullptr)
            current = current->next;

        current->next = new_node;
    }

    /**
     * @brief Return the length of the list
     *
     * @return int The length
     */
    int length()
    {
        return _size;
    }

    /**
     * @brief Get value at a given index
     *
     * @param index The index
     * @return int& Reference to the value at that index
     */
    int &operator[](int index)
    {
        check_index_out_of_bounds(index);
        Node *current = find_node_at_index(index);
        return current->value;
    }

    /**
     * @brief Add element to the beginning of the list
     *
     * @param val The value to be added
     */
    void push_front(int val)
    {
        head = new Node{val, head};
        _size++;
    }
};

// test_linked_list.cpp
#include <cassert>
#include <iostream>

#include "linked_list.cpp"

/**
 * @brief Test the append method and the indexing operator method
 *
 */
void test_append_and_get()
{
    LinkedList ll{};
    ll.append(0);
    ll.append(1);
    assert(ll[0] == 0);
    assert(ll[1] == 1);
}

/**
 * @brief Test that accessing an element outside of the
 * bounds throws a range error.
 *
 */
void test_access_element_out_of_bounds_throw_range_error()
{
    LinkedList ll{};

    bool throwed_range_error = false;
    try
    {
        int x = ll[0];
    }
    catch (const std::range_error &e)
    {
        throwed_range_error = true;
    }
    assert(throwed_range_error);
}

/**
 * @brief Test that we can construct a LinkedList
 * from a vector of integers
 *
 */
void test_vector_constructor()
{
    LinkedList ll{{0, 1}};
    assert(ll[0] == 0);
    assert(ll[1] == 1);
}

/**
 * @brief Test that printing works
 *
 */
void test_print()
{
    LinkedList ll{};
    ll.print();
    ll.append(0);
    ll.print();
}

/**
 * @brief Test that we can insert element at the front
 *
 */
void test_push_front()
{
    LinkedList ll{{1, 2, 3}};
    ll.push_front(42);
    assert(ll.length() == 4);
    assert(ll[0] == 42);
}

int main()
{
    test_append_and_get();
    test_access_element_out_of_bounds_throw_range_error();
    test_vector_constructor();
    test_print();
    test_push_front();
    return 0;
}
```

You can also find the source code at <https://github.uio.no/IN1910/cpp-list>.


### Linked List Variants

The linked list data structure we have created so far is only the very simplest kind of a linked list. We call it a *singly* linked list, because each node connects to the next one with a *single link*. We could for example also make a *doubly linked* list, where each node has a `next` pointer, but also a `previous` pointer, so that we can iterate the list in either direction. Similarly, there are *circularly linked lists*, where we connect the final node to the first node again. For even more examples, take a look at the [Linked List Wikipedia article](https://en.wikipedia.org/wiki/Linked_list).

We will come back to some of these variants, to understand how they differ from our implementation in the next lecture.


## Comparing Dynamic Arrays and Linked List

We have now taken some time to look at linked lists in detail, and in the last lecture, we look at dynamic arrays. As we have seen, both can be used to implement the list abstract data type. Now, we want to take a step back and look at how the choice in the underlying data structure affects the *performance* of the final list object.

However, before we do this, we need to learn a little more about algorithm analysis. We therefore spend the rest of this lecture on algorithm analysis, and return to comparing the data structures in the next lecture.
