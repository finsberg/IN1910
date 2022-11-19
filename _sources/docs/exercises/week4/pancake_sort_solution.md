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

![_](pancake_sort.png)

# The Pancake Problem
This is a specialized sorting problem, where we intentionally limit our sorting capabilities. Imagine a stack of pancakes of varying sizes. We want to sort our stack so that the largest pancake is on the bottom, and that they decrease in size as the stack moves upwards. However, the only operation we can perform, is to insert a spatula between two pancakes in the stack, and then flip *all* pancakes above that one around in one go.

The [Pancake Problem](https://en.wikipedia.org/wiki/Pancake_sorting) is finding a general algorithm for how to sort such a pancake stack in the least amount of flips. It is an unsolved problem, and it is unknown what the optimal solution is.

Here we first create a class `PancakeStack` that extends the built-in `list`-class. We add a `.flip(n)` method that flips the top $n$ pancakes (i.e., the first $n$ pancakes). This method also automatically keeps track of the number of flips that have been used in the `nr_of_flips`-attribute. Finally we also add a boolean property `is_sorted`, that we can use to check if we are finished with sorting.


```python
class PancakeStack(list):
    """A specialized list class, implementing the flip action.

    A pancake stack is represented from top to bottom.
    This class is intended for working on the Pancake Problem.
    Ref: https://en.wikipedia.org/wiki/Pancake_sorting
    """

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.nr_of_flips = 0

    def flip(self, n):
        """Flip the top n pancakes of the stack."""
        if n < 1:
            raise ValueError("Must flip at least one pancake!")
        elif n > len(self):
            raise ValueError(
                f"Asked to flip {n} pancakes, but stack only has {len(self)}"
            )

        self[:n] = reversed(self[:n])
        self.nr_of_flips += 1

    @property
    def is_sorted(self):
        return self == sorted(self)

    def sort(self):
        raise NotImplementedError
```

## Exercise 1a) Implementing the pancake sort itself

Make either a stand-alone function, `pancake_sort`, that takes in a `PancakeStack` object as input **or** extend the `PancakeMethod` with a `PancakeStack.sort` method that sorts the stack.
Either of these should sort the stack in an increasing order. The only way you are allowed to rearrange the stack is using the `PancakeStack.flip` method. You are not allowed to use any external libraries as aid (for example `np.argmax`, but you can define your own utility functions/methods as desired. (Hint: Defining an `argmin` or `argmax` function/method can be very helpful!).

One of the following two test-snippets should work

**As stand-alone function**
***
```python
stack = PancakeStack([2, 1, 0, 3, 5, 4, 6])
pancake_sort(stack)

assert stack.is_sorted
print("Sorted stack:", stack)
print(f"{stack.nr_of_flips} flips were used in total.")
```
***

**As class method**
```python
stack = PancakeStack([2, 1, 0, 3, 5, 4, 6])
stack.sort()

assert stack.is_sorted
print("Sorted stack:", stack)
print(f"{stack.nr_of_flips} flips were used in total.")
```

```python
class PancakeStack(PancakeStack):
    @staticmethod
    def argmax(sequence):
        assert sequence, "empty list"
        max_index = 0
        max_value = sequence[0]
        for i, value in enumerate(sequence[1:]):
            if value > max_value:
                max_value = value
                max_index = i + 1
        return max_index

    def sort(self):
        """Sort the Pancake stack using only flips"""
        unsorted = len(stack)
        while not stack.is_sorted:
            # Find largest pancake in unsorted stack
            biggest_remaining = self.argmax(self[:unsorted])
            # If it is at the bottom already, do nothing
            if biggest_remaining == unsorted - 1:
                pass

            # If it is at the top already, flip whole remaining stack
            if biggest_remaining == 0:
                stack.flip(unsorted)

            # If it is somewhere in the middle, flip to top, then to bottom
            else:
                stack.flip(biggest_remaining + 1)
                stack.flip(unsorted)

            # Unsorted stack is now 1 shorter
            unsorted -= 1
```

Running the test snippet now gives

```python
stack = PancakeStack([2, 1, 0, 3, 5, 4, 6])
stack.sort()

assert stack.is_sorted
print("Sorted stack:", stack)
print(f"{stack.nr_of_flips} flips were used in total.")
```

The code passes our test!


## Exercise 1b) Algorithm analysis

How many flips did it take your function to sort the example stack given?

Analyze your function. What is the best case number of flips for a stack of $n$ pancakes? What is the worst case?



**Example solution:**

* The best case will be a pre-sorted stack. Our code, as we have implemented it, will recognize such a stack, in which case no flips will be performed. The best case is therefore 0 flips.
* The worst case occurs when the maximum number of flips occurs. In our code we sort one and one pancake to the bottom of the remaining stack. We use a maximum of 2 flips per pancake, and thus the worst case will be $2n$ flips. (Actually it will be slightly lower than this, see 1d).


## Exercise 1c) Testing *all permutations* for smaller stacks

We now want to test our estimates from (1b), and our implementation. To do this we simply want to try *all possible stacks* of various sizes (assuming no duplicate pancakes). To produce all possible permutations of a given stack size, we can use the function `itertools.permutations`, which lets us easily loop over all possible permutations (i.e., different possible configurations).

However, do note that the number of possible permutations for a stack of size $n$ is $n!$, which grows very, very rapidly. We therefore limit ourselves to stack sizes up to 7.

Using a loop, find the lowest, the highest and the average number of flips used for stacks of sizes 3, 4, 5, 6, and 7. Plot your results as the three curves in a flip-stack size plot.
Find the worst case, the best case and the average case of all permutations of stacks of different sizes and plot your results as three curves in the same plot.

```python
import itertools
import numpy as np
import matplotlib.pyplot as plt

stack_sizes = range(3, 8)
worst = []
best = []
avg = []

for n in stack_sizes:
    flips = []
    for stack in itertools.permutations(range(n)):
        stack = PancakeStack(stack)
        stack.sort()
        flips.append(stack.nr_of_flips)

    worst.append(max(flips))
    best.append(min(flips))
    avg.append(sum(flips) / len(flips))

plt.plot(stack_sizes, worst, "o-", label="Worst case")
plt.plot(stack_sizes, best, "o-", label="Best case")
plt.plot(stack_sizes, avg, "o-", label="Avg case")
plt.xlabel("Stack size")
plt.ylabel("Number of flips used")
plt.legend()
plt.show()
```

## Exercise 1d) Checking our analysis

Compare your analysis in 1b with your actual results in 1c. Were your best and worst case estimates correct? What is your average case?


**Example Solution**: First we can look at the curve for the best case, which we see is 0 for all stack sizes. This is because when we loop over *all* permutations, we also get the case with the perfectly sorted stack, which will require 0 flips. Our analysis is therefore confirmed, that the best case is 0 flips.

Next, let us look at the best case. The curve does grow linearly with $n$, as we analyzed. However, we stated that it was $2n$, but the curve is actually lower than this. Printing out the actual numbers shows them to be



```python
print(worst)
```

This is because we forgot to compensate for the the fact that the final pancake in the stack never will require any flips, so we go from $2n$ to $2(n-1)$. Likewise, the second-to-last pancake cannot possibly require *two* flips to get to the bottom of the remaining stack, so we have $2(n-1)-1 = 2n -3$. Which is indeed what we found:

```python
print([2 * n - 3 for n in (3, 4, 5, 6, 7)])
```

So we see the actual worst case is $2n-3$. For larger $n$ than we use here, this modification is minor, and for larger stacks our worst case will approach $2n$.

The average case we have not analyzed earlier, but we have found it in our code now

```python
print(avg)
```

Note that it is slightly below the worst case, but does scale linearly with $n$, as the worst case does, but perhaps with an ever so slightly lower incline. We can use linear regression to find a best-fit expression

```python
from scipy.stats import linregress

print(linregress(stack_sizes, y=avg))
```

So the average case is roughly $1.78n -3.6$, or if we ignore the intercept and round it of a bit, we can write it out as simply $\frac{9}{5}n$.


## Exercise 1e) Checking if a few randomly selected larger stacks (i.e., random sampling)

We now want to check some stacks of larger sizes, like 100, 1000 or 10000 pancakes. For such stacks, going through all possible permutations is completely infeasible. However, we can through a few *randomly selected* permutations and check those. Explain why this should give us a good estimate of the average run time, but not the best/worst cases?

Estimate the average number of flips needed to sort stacks of 100, 1000 and 10000 pancakes by sorting respectively 100, 10, and 1 randomly shuffled stacks. You can for example use `random.shuffle` to shuffle the stacks.

```python
from random import shuffle

trials = ((100, 100), (1000, 10), (10000, 1))
avg_flips = []

for size, nr_of_trials in trials:
    flips = []
    for i in range(nr_of_trials):
        stack = PancakeStack(range(size))
        shuffle(stack)
        stack.sort()
        flips.append(stack.nr_of_flips)

    avg_flips.append(sum(flips) / len(flips))

print("Stack size | Avg Flips")
for size, avg in zip([size for size, nr_of_trials in trials], avg_flips):
    print("{:10} | {:10.0f}".format(size, avg))
```

**Example Solution:** From this run, it seems the average number of flips for larger stacks lies closer to $2n$, than the $1.78n$ we found in (1d) i.e., it gets closer to the worst case.

This actually makes a lot of sense if you think about it: The worst case occurs when we *always* use two flips to get the next biggest pancake to the bottom of the remaining stack. We need 2 flips if the biggest pancake isn't already at the bottom or top of the remaining stack. But what is that chance of this occurring in a randomly shuffled stack? The bigger the remaining stack is, the lower the odds of this occurring will be. For large stacks, we will therefore "get lucky" very rarely, and we will need to use 2 flips for the vast majority of pancakes. E.g., the average number of flips for a stack of a 100 pancakes came out at 193, when we know the worst case is $2\cdot 100 - 3 = 197$, i.e., we only avoid a measly 4 flips on average.

This might indicate that our solution might not be the approach for solving larger pancake stacks.

For reference, the *actual* best solution is unknown, but it has been shown that the best possible *worst case* solution to the problem will need somewhere between $\frac{15}{14}n$ and $\frac{18}{11}n$ flips, which is quite a lot lower than our method's $2n$.
