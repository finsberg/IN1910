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

# Sorting Algorithms

For the rest of this lecture, we will talk about *sorting algorithms*. Or more specifically, *comparison sorts*. Comparison sorts are sorting algorithms that work by sorting a sequence of items (letters, numbers, objects) in which the order must be worked out by comparing objects. For example, sorting a list of numbers from smallest to biggest is a comparison sort, because to find the bigger of two numbers, we compare them.


## Bubble Sort

One of the simplest sorting algorithms, which we have also covered earlier in this course, is the *bubble sort* algorithm. Let us look at one implementation.


```{figure} https://upload.wikimedia.org/wikipedia/commons/c/c8/Bubble-sort-example-300px.gif
---
width: 400px
name: bubble_sort
alt: bubble_sort
---
A bubble sort gif linked from Wikipedia.
```


First we define a swap-method, to easily swap two elements in the sequence:
```C++
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
```
Recall that this works because we are doing a call by reference, using `&`.

Now we implement the bubble sort like an in-place sorting. If we are sorting in-place, we need to do a call-by-reference.
```C++
void bubble_sort(vector<int> &input)
{
    for (int end = input.size(); end > 0; end--)
    {
        for (int i = 0; i < end - 1; i++)
        {
            if (input[i] > input[i + 1])
            {
                swap(input[i], input[i + 1]);
            }
        }
    }
}
```
Let us analyze the cost of this algorithm. We first iterate through the whole list, then the biggest element will be last, so we can now iterate through the whole list except the last element, and then the whole list except the two last, etc. For each iteration we perform at least one comparison, and perhaps a swap, let us say for each iteration, we do $c$ operations. This we get the sum:

$$
	(n-1)c + (n-2)c + (n-3)c + \ldots + 2c + c.
$$

This is essentially a triangle number, which turns out to give the sum
$\frac{n(n-1)}{2}c$.

As before, the coefficients and everything is unimportant, so we can summarize this as saying bubble sort takes $\mathcal{O}(n^2)$ operations. This means, that if we double the length of the input list, bubble sort will use roughly four times longer to sort the list.

Note that the algorithm is $\mathcal{O}(n^2)$ in the worst-case, and the best-case. Because even if we are not doing any swaps, we are still performing $\mathcal{O}(n^2)$ comparisons. This means that even if we send in an *already sorted list* to bubble sort, it will spend $\mathcal{O}(n^2)$ "sorting" it. That is sort of a waste, but we can improve this.

### An improved bubble sort

To improve our algorithm, we simply abort our algorithm if we have iterated through the whole list without making any swaps. We can do this by adding a boolean flag:
```C++
void bubble_sort(vector<int> &input)
{
    bool swapped;
    for (int end = input.size(); end > 0; end--)
    {
        swapped = false;
        for (int i = 0; i < end - 1; i++)
        {
            if (input[i] > input[i + 1])
            {
                swap(input[i], input[i + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
        {
            return;
        }
    }
}
```

In the worst case scenario, we still need to carry out all the same iterations as before, so the worst-case hasn't gotten any better with our new algorithm. It hasn't gotten any worse either, it simply adds a few constant steps into the algorithm, but that only changes the coefficients, which we don't care about.

The best-case scenario however, has improved. If we now send in a sorted list, the algorithm iterates through it once, doing $(n-1)$ comparisons. No elements are swapped, so the algorithm terminates. I.e., the best case is $\mathcal{O}(n)$.


## Selection Sort

A different sorting algorithm, which we haven't covered in this course, but which is perhaps even simpler than bubble sort, is *selection sort*. The algorithm of selection sort is fairly easy:
* Find the smallest element in the list that hasn't been moved yet
* Put it in into its correct index


```{figure} https://upload.wikimedia.org/wikipedia/commons/b/b0/Selection_sort_animation.gif
---
width: 300px
name: selection_sort
alt: selection_sort
---
A selection sort gif linked from Wikipedia.
```

A possible implementation of selection sort is as follows:

```C++
void selection_sort(vector<int> &input)
{
    int smallest; // stores index, not value

    for (int i = 0; i < input.size(); i++)
    {
        // Find smallest element
        smallest = i;
        for (int j = i + 1; j < input.size(); j++)
        {
            if (input[j] < input[smallest])
            {
                smallest = j;
            }
        }

        // Place into its correct spot
        swap(input[i], input[smallest]);
    }
}
```

### The Cost of Selection sort

This sorting algorithm consists of two loops. The outer loop iterates over each element in the list, and so repeats $n$ times. For each iteration, we loop over the remaining $n-i$ elements of the list, meaning we again get a triangle number sum:

$$
	n + (n-1) + (n-2) + \ldots + 1 = \frac{n(n+1)}{2}.
$$

In cases such as this, doing "$n-i$" can simply be assumed to be $\mathcal{O}(n)$.

So we do to nested loops, the outer of $n$ iterations, and the inner of roughly $n$ iterations, meaning the total cost is $\mathcal{O}(n^2)$.

As for our first bubble sort implementation, this is both the best case and the worst case of the algorithm. However, in this case we cannot simply add the "swap" flag solution, because there is no way to build this into the algorithm. We could of course simply add the step: "Check to see if the list is sorted" first, but this would be to add a step that has nothing to do with the algorithm, which is quite pointless. This is unlike bubble sort case, because in that example we were already comparing all elements to begin with, i.e. the added cost was $\mathcal{O}(1)$, not $\mathcal{O}(n)$.


## Are Bubble Sort and Selection Sort "good" sorting algorithms?

While both of these algorithms are easy to implement, and require little code, they are, as we have both seen, $\mathcal{O}(n^2)$, meaning they scale poorly with the size of the input.

Is it possible to do better? Yes, it is. In fact, we know how much better, because it has been shown that the lower limit for both the average case and the worst case of comparison sorting is $\mathcal{O}(n\log n)$, which is much better than $\mathcal{O}(n^2)$. To see why, remember that $n^2 = n\cdot n$. In comparison, $n \cdot \log n$ is multiplying by $\log n$ instead of $n$, which is much smaller. The growth of a $\mathcal{O}(n \log n)$ is therefore close to linear, which is why we call it *loglinear growth*. The best case has a lower limit of $\mathcal{O}(n)$. Because, to know if a list is sorted, we need to carry out $n-1$ comparisons, which must be $\mathcal{O}(n)$.

Have any practical algorithm reached this theoretical limit? Yes indeed, most sorting algorithms that are used are $\mathcal{O}(n\log n)$ in both the average and the worst case. In fact, there are so many to choose from, that it is a bit staggering. Wikipedia has a nice article on [sorting algorithms](https://en.wikipedia.org/wiki/Sorting_algorithm#Comparison_of_algorithms) that has a summary comparing many of the most well-know algorithms and their computational costs.

We won't go through and show many of these sorting algorithms and how they work now, as we are out of time. But taking the time to look through the table on Wikipedia is a good idea, to familiarize yourself with some of the different options. One of the most popular algorithms, *quicksort*, is actually $\mathcal{O}(n^2)$, but it has been shown that it is $\mathcal{O}(n\log n)$ on most realistic input, and so it's average cost is $\mathcal{O}(n\log n)$ and it will often be the fastest in practice. Other popular choices of good and fast sorting algorithms are *mergesort* and *heapsort*.

At this point, an interesting question might be what sorting algorithm the build in Python `sort` uses. The answer is [Timsort](https://en.wikipedia.org/wiki/Timsort), this is a special sorting algorithm made for Python in 2002. It is a hybrid between *mergesort* and *insertion sort*.


## Visualizing Sorting Algorithms

As there are so many sorting algorithms out there, an interesting way to compare them could be to visualize how they sort their lists. This can be done in many ways, for example like shown in the Youtube video below, which shows of 15 different sorting algorithms on lists of various sizes:

```{code-cell} python
from IPython.display import HTML

HTML(
    '<iframe width="560" height="315" src="https://www.youtube.com/embed/kPRA0W1kECg" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>'
)
```

## Sorting Folk Dances

Or you can be inspired by Sapientia University, which has created and shared a whole list of sorting algorithms explained through traditional folk dances. These are shared through the Youtube-channel [AlgoRythmics](https://www.youtube.com/user/AlgoRythmics/videos), which is well worth a watch.

See for example their video of *insert-sort* below:

```{code-cell} python
from IPython.display import HTML

# Embed Youtube Video
HTML(
    '<iframe width="560" height="315" src="https://www.youtube.com/embed/ROalU379l3U" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>'
)
```
