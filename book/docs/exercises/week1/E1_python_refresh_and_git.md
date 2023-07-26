---
jupyter:
  jupytext:
    text_representation:
      extension: .md
      format_name: markdown
      format_version: '1.3'
      jupytext_version: 1.13.8
  kernelspec:
    display_name: Python 3
    language: python
    name: python3
---

# Week 1
## Python refresher and Git

The goal of this week's exercises is to get you writing some Python code again and to familiarize yourself with Git. If you have never written Python before, you will probably need to spend more time, doing more exercises, in which case Langtangen could be a good resource.

The first part of the exercises revolves around creating a your first repository on [github.uio.no](https://github.uio.no/). Next you do some short Python exercises, which should then be committed to your repo and pushed to GitHub.

Note that these exercises are not mandatory and will not be handed in or graded. However, programming is primarily learnt by doing, and so we strongly recommend you try to do most of the weekly exercises.

If you want more to do than these exercises, there are plenty of exercises to be found in Langtangen, but also online. Here we would especially recommend [projecteuler.net](https://projecteuler.net/) for fun challenging problems to be solved. These start out fairly easy, but quickly become challenging. After solving a problem, you get access to a forum where you can see how others solved the problems in a broad range of programming languages.


## Part A — Git

Later in the course, you will do mandatory assignments which shall be carried out in git and handed in through git, but there will be more info on this later. For now, you will just create a repository to try out git and get some experience with it. For this we will use the UiO GitHub server
* [github.uio.no](https://github.uio.no/)
On this server you can log in using your UiO username and password. The nice thing about using this server is that it is a bit more private than the public GitHub server. If you prefer using the public server: [https://github.com/](https://github.com/), feel free to do so. If you do this, we recommend you sign up using your UiO email.

Now carry out the following steps. If you are unsure of how to do these steps, they are explained in the lecture notes, you can ask for help, or you can look it up online.

1. Install Git for your OS. See [this](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) for install instructions
1. Clone the [IN1910](https://github.uio.no/IN1910/IN1910) repository down to your machine
1. Create your own repository through the browser
1. Clone your repository down to your own machine
1. Edit the README.md file (or create one) and commit and push your changes
1. Create a `.gitignore` file and use https://gitignore.io to compile its contents (add your editor, OS, Python), and commit and push these changes.
1. Write a simple `hello_world.py` program, and commit and push these changes
1. Go to your repository through your browser and look at your commit history.

If you have done all these steps, you can now either move on to the Python exercises, our download the interactive tutorial [git-it](https://github.com/jlord/git-it-electron), to get a more thorough introduction to git.


## Part B — Python

We now turn to some Python exercises. These are meant to refresh some of your Python knowledge. For each exercise you do, you should stage your changes, commit them and push your commit to Github. Remember to include a descriptive commit message. If you want to implement the exercises directly into this notebook, you need to download it and move it to your own Git repository. To open it, navigate to the location in your terminal and type `jupyter notebook`.

```{exercise-start}  Less than
:label: week1_ex1
```

Write a function `less_than(original, n)` that takes a list of integers (`original`) and a number $n$, and returns a new list of the elements in the original list that were smaller than $n$. Your function should use a *list comprehension* to do this. Write a few simple tests of your function.

```{exercise-end}
```


```{solution-start} week1_ex1
:class: dropdown
```

```python
def less_than(original, n):
    return [num for num in original if num < n]


print(less_than([4, 1, 3, 2, 5, 0, -2], 2))
print(less_than([], 10))
print(less_than(list(range(20)), 5))
```

This function takes in two arguments: the original list original, and the number n. It returns a new list that contains all the elements from the original list that are less than n. We use a list comprehension to create this new list. The comprehension iterates over each element in the original list and checks if it is less than n. If it is, the element is included in the new list; otherwise, it is skipped.

Here are some simple tests to verify that the function works as expected:


```python
# Test 1
original = [1, 2, 3, 4, 5]
n = 3
result = less_than(original, n)
assert result == [1, 2]

# Test 2
original = [10, 20, 30, 40, 50]
n = 35
result = less_than(original, n)
assert result == [10, 20, 30]

# Test 3
original = [-1, 0, 1, 2, 3]
n = 0
result = less_than(original, n)
assert result == [-1]
```

In Test 1, the function correctly returns the list [1, 2], which contains all the elements from original that are less than 3.

In Test 2, the function returns [10, 20, 30], which are the elements less than 35 in the original list.

In Test 3, the function returns [-1], since only the first element in original is less than 0.

```{solution-end}
```


```{exercise-start}   A deck of cards
:label: week1_ex2
```

A normal playing card is identified by its value and its suit. Let a card be represented as a tuple of the value and the suit, where the value should be an integer between 1 and 13, and the suit by a single letter. For example, `(12, 'C')` would represent the queen of clubs.

1. Use nested loops to create a list that contains a normal deck of 52 playing cards.
2. Use `random.shuffle` to shuffle the deck.
3. After shuffling, draw 13 cards from the deck.
4. Sort and print the drawn cards out so that they are separated by suit, and shown in increasing value within each suit.

Hint: To sort a list, you can use the `list.sort()` method. If you are unfamiliar with this, you can read this mini how-to:
* [https://wiki.python.org/moin/HowTo/Sorting](https://wiki.python.org/moin/HowTo/Sorting)

```{exercise-end}
```


```{solution-start} week1_ex2
:class: dropdown
```


We first create the deck

```python
deck = []
for value in range(1, 14):
    for suit in ("H", "S", "D", "C"):
        deck.append((value, suit))

# Or by list comprehension
deck = [(v, s) for v in range(1, 14) for s in ("H", "S", "D", "C")]
```

Next we shuffle it and use `.pop` to draw cards. I prefer `pop` over slicing here, because then the cards are actually removed from the deck. A slice `hand = deck[:13]` would draw 13 cards, but not actually remove them from the deck, meaning we would now have two copies of the draw cards in existence.

```python
import random

random.shuffle(deck)
hand = [deck.pop() for _ in range(13)]
```

Next we want to sort the cards we drew, once by values and once by suits. We want to perform the value sort *first*, because then we can sort by suits and preserve the value sorting.

To sort by the first element of a tuple we simply use the `list.sort()` method. To sort by the second element of the tuple, we need to use the keyword argument `key` of the `.sort`-method. You can either use `operator.itemgetter`:

```python
hand.sort(key=itemgetter(1))
```

or a simple lambda function:

```python
hand.sort()
hand.sort(key=lambda e: e[1])
```

Then we print to verify:

```python
for card in hand:
    print(card)
```

```{solution-end}
```


```{exercise-start} Letter Counts
:label: week1_ex3
```

Write a function `count_chars` that takes a string as input, and counts the number of times each character appears in the string. Case should be ignored, so that both `A` and `a` count as the same letter. The resulting counts should be returned as a dictionary.

* Hint 1: Case can be ignored by converting the input to lowercase before analyzing it.
* Hint 2: You can loop over the characters of a string

Test your function using the following test-block:
```python
example = "Hello, world!"
for char, count in count_chars(example).items():
    print(f"{char:3}{count:10}")
```

Finally, copy this print example in the test-block and change it so that the characters are lister in alphabetical order. Now add an example where they are printed in order of how many times they occur in the text.

```{exercise-end}
```


```{solution-start} week1_ex3
:class: dropdown
```

This exercise can be solved in many ways. First we show perhaps the most intuitive solution, we loop over all the characters, and add them to the dictionary. We use an if-test to add the first occurrence of each character, and incrementing for later occurrences. Note also that we loop over `text.lower()`, so we only get lowercase letters

```python
def count_chars(text):
    count = {}
    for char in text.lower():
        if char not in count:
            count[char] = 1
        else:
            count[char] += 1
    return count
```

We can avoid the if-test in two ways. We can either use a `collections.defaultdict`

```python
from collections import defaultdict


def count_chars_defaultdict(text):
    count = defaultdict(int)
    for char in text.lower():
        count[char] += 1
    return count
```

As the name implies, the `defaultdict` is a dictionary with a "default" value, so we can pretend `count[char]` exists, even from the first occurrence. If it doesn't exist, it just defaults to 0.

The other way to avoid the if-test is to use the `.get()` method, which can also be given a default option. `count.get(char, 0)` will return the value of the element if it is present in the dictionary, and 0 if it is not. This can be used as follows:

```python
def count_chars_get(text):
    count = {}
    for char in text.lower():
        count[char] = count.get(char, 0) + 1
    return count
```

Finally, there are some built-in functionality that does this. We have the option of using the string `.count` method, or the `collections.Counter` object:

```python
example = "Hello, World!"

assert count_chars(example) == count_chars_defaultdict(example)
```

```python
from collections import Counter


def count_chars_str_count(text):
    text = text.lower()
    return {char: text.count(char) for char in set(text)}


def count_chars_counter(text):
    return Counter(text.lower())
```

Finally, to print in sorted order, we simply use `sorted` on the dictionary items when looping:

```python
example = "Hello, world!"
for char, count in count_chars_counter(example).items():
    print(f"{char:3}{count:10}")
```

```python
example = "Hello, World!"
for char, count in sorted(count_chars(example).items()):
    print(f"{char:3}{count:10}")
```

While to sort by number of occurrences we have to specify that it is the second element we sort by. This can either be done by `operator.itemgetter`:
```Python
sorted(count.items(), key=itemgetter(1), reverse=True)
```
or using a simple lambda function
```Python
sorted(count.items(), key=lambda elem: elem[1], reverse=True)
```
In either case, we need to also use the `reverse` keyword, as sorting normally sorts in increasing order.

```{solution-end}
```



```{exercise-start} Factorizing a number
:label: week1_ex4
```


Write a function `factorize` that takes in an integer $n$, and returns the prime-factorization of that number as a list. For example `factorize(18)` should return `[2, 3, 3]` and `factorize(23)` should return `[23]`, because 23 is a prime.

Use this to test your implementation:

```python
def test_factorize():
    assert factorize(412415) == [5, 82483]
    assert factorize(27) == [3, 3, 3]
    assert factorize(31) == [31]
```


```{exercise-end}
```


```{solution-start} week1_ex4
:class: dropdown
```

First we handle the special case of 1, as this is a bit tricky. Next we need to loop from 2 to $n$ to look for divisors. Every time we find a divisor we divide it out and add it to our list of divisors.

```python
def factorize(n):
    if n == 1:
        return [1]

    divisors = []
    while n != 1:
        for d in range(2, n + 1):
            if n % d == 0:
                divisors.append(d)
                n = n // d
                break  # added this H19. More correct?
    return divisors


print(factorize(18))
print(factorize(23))
print(factorize(412415))
```

```{solution-end}
```


```{exercise-start} Name Scores
:label: week1_ex5
```

(This is [Project Euler problem 22](https://projecteuler.net/problem=22), and is used under a [Creative Commons BY-NC-SA 4.0 license](https://creativecommons.org/licenses/by-nc-sa/4.0/))

Using [names.txt](https://projecteuler.net/project/resources/p022_names.txt) (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?

**Hint:** By "alphabetical value" they mean the sum of the characters in the name, if each character is converted into its position in the alphabet, so A=1, B=2, etc.

```{exercise-end}
```


```{solution-start} week1_ex5
:class: dropdown
```

Here we first need to read all the names from the file. The best way to do this is to use a *context guard*, meaning we use the `with` keyword. Then we do not need to remember to close the file manually. How best to read the text and convert it to a list of names depends on the original input. In this case we first remove all `"` characters, and then split in on the commas.

```python
with open("names.txt", "r") as in_file:
    text = in_file.read()
    text = text.replace('"', "")
    names = text.split(",")

# Check if reading went correctly
print(names[:5])
```

Next we need to sort the names in alphabetical order, this can be done using the `.sort()` list method

```python
names.sort()
print(names[:5])
```

Now we need to find the "alphabetical value" of each name. To do this we create a function that converts a letter into its location in the alphabet. We can import the alphabet as a string from the `string` package. To find the position of a character in a string (or an element in a list), we can use the `.find` method, which returns the index of the first occurrence. Since Python starts counting at 0, but we want A to correspond to 1, we add 1 to the result.

```python
import string

ALPHABET = string.ascii_uppercase


def letter_position(letter):
    return ALPHABET.find(letter) + 1
```

Next we define the function that converts each letter in a name independently, then sum the resulting integers. We test the function with the example given, namely that "COLIN" should have a value of 53.

```python
def alphabetical_value(name):
    return sum([letter_position(letter) for letter in name])


print(alphabetical_value("COLIN"))
```

Now we want to go through the whole list of names, find the value of each one and multiply it by its position in the list of names

```python
total = 0
for i, name in enumerate(names):
    total += alphabetical_value(name) * (i + 1)

print(total)
```

Which is our final answer. Writing the whole thing out as a single program can be done as follows:

```python
import string


def letter_position(letter):
    return string.ascii_uppercase.find(letter) + 1


def alphabetical_value(name):
    return sum([letter_position(letter) for letter in name])


def total_value(names):
    total = 0
    for i, name in enumerate(names):
        total += alphabetical_value(name) * (i + 1)
    return total


def read_names(filepath):
    with open(filepath, "r") as in_file:
        text = in_file.read()
        text = text.replace('"', "")
        names = text.split(",")
    return names


if __name__ == "__main__":
    names = read_names("names.txt")
    names.sort()
    print(total_value(names))
```

```{solution-end}
```
