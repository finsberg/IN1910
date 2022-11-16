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
# Your code here
```

## Exercise 1b) Algorithm analysis

How many flips did it take your function to sort the example stack given?

Analyze your function. What is the best case number of flips for a stack of $n$ pancakes? What is the worst case?



## Exercise 1c) Testing *all permutations* for smaller stacks

We now want to test our estimates from (1b), and our implementation. To do this we simply want to try *all possible stacks* of various sizes (assuming no duplicate pancakes). To produce all possible permutations of a given stack size, we can use the function `itertools.permutations`, which lets us easily loop over all possible permutations (i.e., different possible configurations).

However, do note that the number of possible permutations for a stack of size $n$ is $n!$, which grows very, very rapidly. We therefore limit ourselves to stack sizes up to 7.

Using a loop, find the lowest, the highest and the average number of flips used for stacks of sizes 3, 4, 5, 6, and 7. Plot your results as the three curves in a flip-stack size plot.
Find the worst case, the best case and the average case of all permutations of stacks of different sizes and plot your results as three curves in the same plot.

```python
# Your code here
```

## Exercise 1d) Checking our analysis

Compare your analysis in 1b with your actual results in 1c. Were your best and worst case estimates correct? What is your average case?


## Exercise 1e) Checking if a few randomly selected larger stacks (i.e., random sampling)

We now want to check some stacks of larger sizes, like 100, 1000 or 10000 pancakes. For such stacks, going through all possible permutations is completely infeasible. However, we can through a few *randomly selected* permutations and check those. Explain why this should give us a good estimate of the average run time, but not the best/worst cases?

Estimate the average number of flips needed to sort stacks of 100, 1000 and 10000 pancakes by sorting respectively 100, 10, and 1 randomly shuffled stacks. You can for example use `random.shuffle` to shuffle the stacks.

```python
# Your code here
```
