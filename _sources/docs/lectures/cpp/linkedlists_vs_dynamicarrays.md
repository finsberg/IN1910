---
jupyter:
  jupytext:
    text_representation:
      extension: .md
      format_name: markdown
      format_version: '1.2'
      jupytext_version: 1.7.1
  kernelspec:
    display_name: Python 3
    language: python
    name: python3
---

# Comparing Linked Lists and Dynamic Arrays

In this lecture we will start learning what we briefly covered about algorithm analysis and big Oh notation to two different cases. We will be looking at differences between our linked list data structure, and our dynamic array data structure. And we we look closer at some different sorting algorithms, and how they compare in terms of computational complexity.


## Big Oh

Recall from last time, that we introduced the big Oh notation to classify how much *work* an algorithm has to carry out to solve some problem, given the size of that problem. For sorting a list for example, the size of the list would be the problem size. We often denote the problem size by $n$.

The main thing we are interested in, is understanding how our algorithm *scales* with the problem size, as the problem grows, does the computational cost grow linearly? Quadratically? Exponentially? This is where the big Oh notation comes in.

We find the big Oh of an algorithm, by finding the number of *operations* it has to carry out to solve some problem, but we do not care to find the exact number, we care only about the fastest-growing term. We also disregard any coefficients.

Using big Oh notation, we will end up classifying most algorithms into one of the categories in the list below, which is organized from slowest-growing, to fastest-growing. An algorithm that is $\mathcal{O}(1)$ scales perfectly, we can increase the problem size, and the time to solve it won't change! An algorithm that is $\mathcal{O(n)}$ scales linearly, if we double the problem size, we will roughly double the computation time. An algorithm that is $\mathcal{O}(e^n)$ scales horribly, as the problem size grows, the computation time grows exponentially, for larger inputs, the algorithm will stop working as we run out of computational resources.

| Big Oh                  | Name                  |
| ----------------------- | --------------------- |
| $\mathcal{O}(1)$        | constant              |
| $\mathcal{O}(\log n)$   | logarithmic           |
| $\mathcal{O}(n)$        | linear                |
| $\mathcal{O}(n \log n)$ | loglinear/quasilinear |
| $\mathcal{O}(n^2)$      | Quadratic             |
| $\mathcal{O}(n^3)$      | Cubic                 |
| $\mathcal{O}(n^k)$      | Polynomial            |
| $\mathcal{O}(e^n)$      | Exponential           |
| $\mathcal{O}(n!)$       | Factorial             |


## Computing with Big Oh

Most algorithms consists of many different steps, which we might analyze independently. The total cost of the algorithm is then the sum of the costs of each step. If we've found the big Oh costs of each step, we then need to add big Oh expressions together. For example:

$$\mathcal{O}(n) + \mathcal{O}(n^2).$$

When adding big Oh expressions together, we simply keep the biggest term:

$$\mathcal{O}(n) + \mathcal{O}(n^2) = \mathcal{O}(n^2).$$

If there are multiply of the biggest term, this doesn't really matter, as adding these expressions together would just give a different coefficient, but we are disregarding that coefficient. So for example:

$$\mathcal{O}(1) + \mathcal{n} + \mathcal{n} = \mathcal{O}(n).$$

Similarly, sometimes we need to carry out an operation many times, for example when iterating or looping. This means multiplying a cost by some number. For example

$$10\mathcal{O}(n^2).$$

This would also just be a constant coefficient, and so we would simply discard it:

$$10\mathcal{O}(n^2) = \mathcal{O}(n^2).$$

The exception to this if the number of steps we carry out is itself a function of the problem size $n$. For example iterating a list of size $n$, or performing $n$ multiplications, etc. In that case, we need to multiply in the number of repetitions into the big Oh. Performing $n$ steps that each cost $\mathcal{O}(n)$ for example:

$$n \cdot \mathcal{O}(n) = \mathcal{O}(n^2).$$

Or performing $n$ steps of an algorithm costing $\mathcal{O}(n\log n)$ would give a total cost of:

$$n\cdot \mathcal{O}(n\log n) = \mathcal{O}(n^2 \log n).$$


## The List ADT

In the previous lectures, we have created two different list classes: `ArrayList` and `LinkedList`. And these are also the topic of project 2, where you are getting more experience with them. These two classes both implement the *list* abstract data type (ADT), but with two different data structures as their basis:
* The `ArrayList` is built on top of the dynamic array structure
* The `LinkedList` is built on top of the linked list structure.

We will now look closer at how the different choice for the basis data structure, affects their performance. To do so, we will go through the different operations of the list ADT, that both classes support, such as insertions, removal, and indexing.

We will characterize the costs in terms of the *length* of the list, which we will denote $n$.


### Appending

Let us start with the operation of appending new elements to the end of the list. Both classes support this method, but what is the *cost* of appending?

#### Dynamic Array

For a dynamic array, appending an element is the same as assign that value to the first unused element of the underlying storage array. The cost of this operation is not dependent on the length of the list. It doesn't matter if the list has 100 or 100 million elements, appending a value is simply assigning a value to the next unused space. Thus, the cost of appending an element to our `ArrayList` is $\mathcal{O}(1)$.

However! Sometimes, there *won't* be any free space left in the underlying storage array. In this case we had to do a "resize" operation as we called it. To resize our array, we doubled the size of the underlying array, if the list has $n$ elements, this means we allocate an array of $2n$ elements. Then we copy over the $n$ elements of the array and deallocate the previous storage array. The bigger the list is, the more work it is to do the resizing. The resize operation thus scales as $\mathcal{O}(n)$.

Now, appending to our `ArrayList` only *sometimes* incurs the cost of a resize operation, so how can we include this in our analysis? We will return to this point shortly, for now we simply say that the cost of the `ArrayList.append` method is $\mathcal{O}(1)$ with an occasional $\mathcal{O}(n)$.

#### Linked List

Now we turn to the linked list. Recall that appending an element to the linked list required starting at the head of the list, and iterating through to the end of the list. The method looked something like this:
```C++
void append(int val)
{
    if (head == nullptr)
    {
        head = new Node(val);
        return;
    }

    Node *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = new Node(val);
}
```
Because we are iterating from the head of the list, all the way to the end, we are doing $n$ operations. If the list consists of 100 nodes, the loop needs to run 100 times. Once we get to the end, actually attaching the new node is only a few operations. This means that most of the work of appending to the `LinkedList` is iterating through to the end, but because of this operation, the whole append method costs $\mathcal{O}(n)$.

We see that because we need to iterate from the start, as the list grows, the cost of appending more elements also grow. If the size of the array itself doubles, then the cost of the array will double.

#### Comparing the two:

We have seen that appending costs $\mathcal{O}(1)$ for the `DynamicArray` and $\mathcal{O}(n)$ for the `LinkedList`, this means that while the two might be equally fast for appending a few elements, as the lists grow, appending more elements to the linked list will become slower and slower, while for the `DynamicArray` they will stay the same.

Now, you might be questioning this comparison as unfair, because the dynamic array also needed to resize every now and then, a costly operation. And that is a good point, so let us look a bit closer at that. Instead of referring to a single append operation, which most likely won't but could possibly incur a resize. Let us look at a whole set of appends, which definitely will incur a resize. We can then find the "average" cost of an append. This concept of "average cost" is called the *amortized* cost of an operation.

### Amortized Cost

The *amortized* cost of an operation is the averaged cost of a single operation, if one carries a lot of them. The term itself might be new and cryptic to you, but it comes from the world of finance and economics. A big business might *amortize* their costs by spreading them evenly throughout the year for example. It is simply a way of averaging costs and payments.

Instead of analyzing a single append. Let us say we start with an empty dynamic array, and append $n$ elements to it:
```C++
ArrayList example;

for (int i = 0; i < n; i++)
{
    example.append(i);
}
```
What is the total cost of this operation, in big Oh, as a function $n$? Well, the $n$ appends themselves each cost $\mathcal{O}(1)$, and so $n$ operations of $\mathcal{O}(1)$ will be a total of $\mathcal{O}(n)$.

But what is the total cost of all the resized required to reach $n$? To understand this, it is easiest to start from the end, and work back to the start. The final resize needed was to increase the underlying storage from $n/2$ to $n$, which would cost $n$. The resize before that would need to take it from $n/4$ to $n/2$, which would cost $n/2$. The one before that would need to take it from $n/8$ to $n/4$, which would cost $n/4$ and so on. So the total cost of all the resizes would be:

$$n + \frac{n}{2} + \frac{n}{4} + \frac{n}{8} + \ldots,$$

all the way down to the empty list. The exact number of resize operations will depend on what $n$ is.

This sum is a geometric progression, which sums out to $2n$. The easiest way to see this is simply to draw out the series as a bunch of boxes

```{figure} https://upload.wikimedia.org/wikipedia/commons/thumb/4/4b/Geometric_progression_convergence_diagram.svg/525px-Geometric_progression_convergence_diagram.svg.png
---
width: 400px
name: geo-prog
---
Geometric progression convergence diagram.
```

So while each resize might be costly, we carry out so few of them, that the *total cost* of all the resizes also becomes $\mathcal{O(n)}$


So the total cost of appending $n$ elements to an empty `DynamicArray` is

$$\mbox{(cost of $n$ appends)} = \mathcal{O}(n) + \mathcal{O}(n) = \mathcal{O}(n).$$

But if the cost of doing $n$ appends has a total cost of $\mathcal{O}(n)$, then the average/amortized cost of a single operations must be

$$\mbox{(amortized cost of 1 append)} = \frac{1}{n}\cdot \mbox{(cost of $n$ appends)} = \frac{1}{n}\cdot \mathcal{O}(n) = \mathcal{O}(1).$$

So on *average*, the cost of appending an element to our `ArrayList` is still not dependent on the size of that list, unlike for the linked lists.

### Inserting elements to the front

We have now look at the cost of appending elements to the back of the list, but what about pushing them to the front? For our `LinkedList` we implemented this as a `push_front` method, or alternatively as the `insert` method where we specify the index 0. We did not implement this method for the `ArrayList` in the lecture, but that is part of project 2. While we have not implemented it, we will still try to analyze what it would cost.

#### Dynamic Array

To insert an element at the front of a dynamic array, we would need to first make space for it, by moving every other element in the list one index up. This operation would require the existing $n$ elements, which would cost $\mathcal{O}(n)$. After this is done, adding the new element would be simple, only requiring a single assignment, which would be $\mathcal{O}(1)$. So in total, appending to the front of a dynamic array is

$$\mathcal{O}(n) + \mathcal{O}(1) = \mathcal{O}(n).$$

#### Linked List

For the linked list, we did implement the `push_front` method, and to do so was almost trivial because of the `head` pointer of the class pointing at the first element:
```C++
void push_front(val)
{
    head = new Node(val, head);
}
```
This method is just as simple if there is 0 elements in the list, or 10, or a million. No matter the size of the list it is only a few operations, and so the cost is $\mathcal{O}(1)$.

#### Comparing the two

First we saw that the cost of appending is constant for a dynamic array: $\mathcal{O}(1)$, and scales linearly with the linked list: $\mathcal{O}(n)$. And now we have seen that the reverse is true for adding elements to the front, it is constant for the linked list, and linear for the array list!

### Adding a Tail Pointer to the Linked List

In our analysis of the linked list data structures so far, we have seen that adding an element to the front of the linked list is easier, meaning it costs $\mathcal{O}(1)$, than than adding it to the back, where the cost is $\mathcal{O}(n)$. This is simply because we have the `head` pointer to the first element, but to get to the back of the list, we need to iterate through the whole chain.

However, there is no reason we cannot also add a pointer to the end of the chain, which we can use as a shortcut to get there. This pointer is often called the `tail` pointer, because it points to the tail of the list. If we have a tail pointer in our class, then we can rewrite the append method as
```C++
void append(int val)
{
    if (head == nullptr)
    {
        head = new Node(val);
        tail = head;
    }
    else
    {
        tail->next = new Node(val);
        tail = tail->next;
    }
}
```
Which is practically just as easy as the `push_front` method. By adding the tail pointer, we have thus improved the scaling of our append method to $\mathcal{O}(1)$, the same as for the `DynamicArray`.


### Inserting into the middle

So far we have covered inserting into the back, or to the front, of the list. But what about inserting somewhere in the middle? Here, we do not necessarily mean exactly the middle, but inserting at a given index $i$.


#### Dynamic Array

To insert somewhere in the middle of the list, the situation is slightly better than adding to the front, as we only have to move all the elements with indices above it to make room. However, inserting into the middle of the list would still mean moving something like half the elements of the list, i.e., $n/2$ elements. And so the cost would still increase linearly with $n$, so the cost would still be $\mathcal{O}(n)$.

If we instead want to give the cost as a function of both $n$ and $i$, then the cost would be:

$$\mathcal{O}(n-i),$$

which shows that the further back in the list we want to insert, the bigger the index $i$, and the less the operation costs.

#### Linked List

For a linked list, the insertion of a new node itself is not very costly, we only need to create a new node and hook it into the chain. The insertion itself would only cost $\mathcal{O}(1)$. However, just like appending (before we added the tail pointer), we first need to get to the right nodes to actually carry out this operation, and so this would cost $\mathcal{O}(n)$, as we would need to start at the front of the list and iterate to wherever the node was to be connected.

You might think we can fix this situation by having more reference pointer, just like the tail. But to insert like this at any given index $i$ is not feasible, as we would literally need to make another list to store all those reference pointers.

However, as the cost of inserting itself is $\mathcal{O}(1)$, we might be able to piggyback of other algorithms and methods that happen to be iterating through the list anyway. For a dynamic array, this won't be possible, because regardless of how you find the element, the cost comes from having to move all the other elements to make room.

### Summarizing so far

| Operation        | Dynamic Array      | Linked List      | Linked list (w/ tail ref) |
| ---------------- | ------------------ | ---------------- | ------------------------- |
| Insert at back   | $\mathcal{O}(1)^*$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$          |
| Insert at front  | $\mathcal{O}(n)$   | $\mathcal{O}(1)$ | $\mathcal{O}(1)$          |
| Insert in middle | $\mathcal{O}(n)$   | $\mathcal{O}(n)$ | $\mathcal{O}(n)$          |

\*) This is the amortized cost, i.e., the cost averaged over many operations

To summarize, we see that the cost of inserting elements into the lists are different, depending on what data structure we use. From the table, it might seem that using a linked list with a tail pointer might be the most efficient, and if we were looking at only insertions, this would indeed be the case. But lists are not only used for insertions.

### Indexing

An important characteristic of using lists is that we can use indexing to read and write to elements of the list. We implemented this operation for both our lists by overloading the square-bracket operator. But what is actually the cost of the operation?

#### Dynamic Array

We implemented our indexing operator something like this:
```C++
int &operator[](int index)
{
    return data[index];
}
```
Because our data is actually stored in an underlying storage array (called `data` in this example), indexing our `ArrayList` is actually just an alias for indexing the underlying array.

One of the strengths of arrays is that the data lies contiguously in memory, and as we have seen earlier, indexing an array is actually just fancy memory address operations, so if we for example write `x[10]` to get the 10'th element of some array, then `x` is actually just a pointer/memory address, and the indexing operations means `*(x + 10)`, meaning we do some pointer arithmetic and then look up the value at the right memory address.

Because arrays are contiguous in memory, accessing any element by index is trivial, because C++ will be able to compute its way to the correct memory address and look up the right value. This is true regardless of the size of the array. Therefore, accessing an element by index in an array is $\mathcal{O(1)}$.

Because our `ArrayList` is built on top of arrays, our indexing operation will also be $\mathcal{O}(1)$.

#### Linked Lists

For linked lists, the situation is different. The elements, i.e., nodes of a linked list are *not* stored contiguously in memory. Each node can for all intents and purposes exist somewhere completely different in memory, the important thing is that each node knows where the next one is stored.

However, this means that to get to an element based on its index $i$, we have to start at the front of the list, and iterate all the way to the right element. We implemented this as something like
```C++
int &operator[](int index)
{
    Node *current = head;

    for (int i = 0; i < index; i++)
         
        {
            current = current->next;
        }
    return current;
}
```
So we start at the head, and move $i$ steps, where $i$ is the index. This means accessing an element by index costs $\mathcal{O}(i)$ in terms of the index. Often we do not express costs in terms of indices, so we simply say that this costs $\mathcal{O}(n)$. The bigger the list, the bigger the indices we typically access, the more costly it will be.

Indexing the final element in the list for example, would require us to iterate through the entire list. If we have a tail reference, getting to the last element is easy, but getting to the second-to-last element is still hard, because while we have a tail reference, we have no way to iterate backwards in our linked list. If we had implemented a *doubly* linked list, we could iterate in from either side of the array. This would improve things somewhat, but for most indices, we would still need considerable iterating to get to a given index.


#### Comparing the two

For arrays and dynamic arrays, indexing is a "free" operation. It does not matter what index we want to access either, they are all equal. This is often referred to as *random access*. The name implies that it doesn't matter what order we access the elements of the list in, it might as well be random. A better name for it is *direct access*, we can directly go in and access any element by index. You might be familiar with the term *random access memory* (RAM), which refers to the normal memory on the computer, this is also called random access because accessing any part of it should take roughly the same amount of time.

As we have seen, a linked list is not a direct access data structure. We cannot go into any given index directly, but have to iterate through the sequence from the start. This is known as *sequential access*.

```{figure} https://upload.wikimedia.org/wikipedia/commons/thumb/a/a7/Random_vs_sequential_access.svg/600px-Random_vs_sequential_access.svg.png
---
width: 300px
name: seq-rand-access
---
Sequential versus random access.
```

## Summarizing

Our findings are summarized in the table below. By analyzing the costs of the different operations, we can see how the data structures affect the overlying data type. While both data structures can support the same list ADT, the performance will differ.

| Operation            | Array            | Dynamic Array      | Linked List      | Linked list (w/ tail ref) |
| -------------------- | ---------------- | ------------------ | ---------------- | ------------------------- |
| Insert at back       | -                | $\mathcal{O}(1)^*$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$          |
| Insert at front      | -                | $\mathcal{O}(n)$   | $\mathcal{O}(1)$ | $\mathcal{O}(1)$          |
| Insert in middle     | -                | $\mathcal{O}(n)$   | $\mathcal{O}(n)$ | $\mathcal{O}(n)$          |
| Get element by index | $\mathcal{O}(1)$ | $\mathcal{O}(1)$   | $\mathcal{O}(n)$ | $\mathcal{O}(n)$          |

\*) This is the amortized cost, i.e., the cost averaged over many operations

### What we haven't analyzed

Our analysis hasn't been too extensive, we have simply compared some of the most important operations in term of big Oh. But there are other important differences between the data structures we haven't covered, such as the difference in memory usage of the two. Or other operations such as removing elements. It also turns out that an important difference in practice is that arrays are often fast, because when elements are contiguous in memory, they can be loaded into the CPU cache *faster*. Facts such as these are hard to include into our algorithm analysis.

While our analysis is simplified and theoretical, it is still very useful, and analysis such as the ones we have carried out are an important part for algorithms and data structures.


### Final recommendation

For scientific computing, dynamic arrays usually win out on efficiency, because they are stored contiguously in memory. In practice therefore, you might rarely use, or need to use, linked lists.

However, knowing about linked lists, and how to implement and analyze them is still a valuable skill, as they are an important introductory data structure and something you might be expected to know about if you every move further into computational science.


### Some Analogies

The major differences between a linked list and a array list is how elements are added and removed from the list, and how they are read. This can be a very abstract concept, so many people like to make some analogies to understand and remember the differences.

For example, when it comes to indexing, an example of a linked list would be the alphabet. Most people remember the alphabet as a linked list. You can illustrate this, because few people can answer the question *Which letter is the 17th in the alphabet?* directly, i.e., most people cannot "index" the alphabet. Instead they have to start at the beginning, and count their way to the 17th letter/element. However, ask someone "which letter comes after P in the alphabet" and most people probably wouldn't even have to think before answering.

Indexing an array however, can be thought of like the pages in a book. If someone asks you to open a book to page number 277, you wouldn't have to start on page 1 and flip each page to get to the right spot. Instead, you could simply go directly to the right page.

Similarly, we can talk about adding/removing elements. An analogy for adding elements to a dynamic array could be a stack of books lying on a table. Adding a book to the end of the stack is very easy, you just place it on top, where there is room. However, if you want to insert the book into the bottom or middle of the pile, you would have to do a lot more work. The bigger the stack, the more work.

```{figure} ../../figures/stack_of_books.jpg
---
width: 150px
name: stack-of-books
---
A dynamic array is like a stack of books.
```

Adding or removing elements from a linked list can be though of like modifying a chain, such as the one for your bicycle. If you need to lengthen your bike chain, you simply disconnect two of the "nodes" of the chain, add inn some more, and click them back together. It doesn't matter how long the chain is, adding more chains is just as hard. For our "insert into the middle" we also added the "search time" to get to the right node. This would be like a bike chain with a broken "node", first you would need to find the broken linker, to do this you first "iterate" through the chain, then you pop the broken one out and a fresh one in.


```{figure} ../../figures/bike_chain.jpg
---
width: 3000px
name: bike-chain
---
A linked list is like a bike chain.
```
