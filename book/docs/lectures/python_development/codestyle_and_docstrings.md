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

# Code Style and Documentation

In this lecture we will cover the topics of *code style* and *documentation*. Put simply, these are aspects of writing code that doesn't impact if, or how, the code you write works, but rather how easy it is to read and understand for others. Two weeks ago we discussed how we can write functioning and reliable software, and how we can test our code to verify that it is working as intended. This is another aspect of what we can call *code quality*.


## Code Readability

The fundamental idea for this entire lecture can be summed up in a single sentence, which is

> Write programs for people, not computers

Just like writing prose, there are many choices one can make when writing code. Some choices we can make are
* How to break down and solve a given problem
* How to order the steps we take
* What variables we create (both the number of variables and their data types)
* What names we choose for our variables
* How much *whitespace* we use
* What comments we add to the code
* And many other choices...

Some of these choices will directly impact function or speed of the program, what algorithm we use for example.
However, many of the choices we make will not impact how the final program *functions*. The best examples are variable names, which from "the outside" has no importance whatsoever.

It might be easy to assume that the choices that do not impact function are not important, but this is not the case. If we make poor choices, say pick variable names that are confusing or easy to mix, then our code will become cluttered and hard to understand. Why is this a problem? For one, it will make it harder to work with our code, leading to inefficient work and even to errors. If we want to share our code with others or collaborate, things get even worse - as others might not even understand the code you have written or how it should be used or modified.

This aspect of the code is usually referred to as the *readability* of the code. We should strive to make our code as *readable* as possible. A high quality code should be easy for a new developer to read and understand. When you write code, you should therefore think how that code looks to an external pair of eyes. Is it structured, clear and easy to understand? The sentence we started with should be our mantra - write code for people, not computers. This was put a bit more pointedly by Martin Fowler

> *Any fool can write code that a computer can understand. Good programmers write code that humans can understand* - Martin Fowler


## What is code style, and why is it important?


As there are so many choices we can make when coding that will impact how structured and readable our code becomes, we should strive to make consistent choices and stick to a particular set of "rules" for how code should be written - and such a set of rules is called a *code style*. Code that follows a consistent and good style will be easier to use, troubleshoot, maintain and extend. Code that doesn't follow a consistent style will be more disordered and can be frustrating to work with.

The term *style* comes from traditional writing, where one can also follow a particular *writing style*. For publications to be more consistent, different contributing authors to a given publication will often be asked to follow and use the same *style* and there are many different style manuals which lie out a set of principles or rules to follow.

Like with any writing, there are no hard rules about what constitutes good style, and there are different choices one can make — the important thing is to be consistent in your choices. A piece of code should have the same code style and formatting throughout.


## Style Guides

Most software in the real world is developed collaboratively, this means it is important for different programmers to agree on what code style to follow, otherwise they will end up writing code that looks fragmented and messy. Because of this, most software groups agree on a *style guide*, which guides all the programmers in the project to follow the same style. Because everyone is following the same guidelines, it's easier to collaborate.

Put simply, a style guide is a list of *dos* and *don'ts* that you will be expected to follow. Because style guidelines is about *writing* code, they are often specific to a given programming language. Python is a popular programming language, and so many different style guides exist, the most important one to know about is called the PEP8 style guide.

### The PEP8 Style Guide

PEP stands for *Python Enhancement Proposal*, and these are documents that are proposals for new features or design changes to Python. The PEPs and discussed and reviewed by the community and over time the Python developers incorporate them into the language. One of these, PEP8, is a code style guide for the Python code in Python's standard library should be written. Put simply: PEP8 is how Python's developers are writing python code.
* [Link to the PEP8 style guide](https://www.python.org/dev/peps/pep-0008/)

In IN1910 we want you to use a good and consistent code style in the code you write. We recommend you read the PEP8 style guide and stick with these choices. However, we won't be extremely strict on this point. Python is a popular programming language, and many other style guide exists. Another possible choice is for example [Google's Python style guide](https://github.com/google/styleguide/blob/gh-pages/pyguide.md).

Regardless of exactly what style you want to use for your own projects, reading through the PEP8 style guide and trying to reflect around *why* the rules are as they are is highly recommended and will most likely make you a better programmer.

We will now go through and cover *some* of the rules in PEP8, but we don't cover everything, so reading through the actual style guide is still good. Many of our examples are taken directly from the PEP8 document, while some are taking from other lectures and exercises in IN1910.

## Some general points from PEP8

### Indent by 4 spaces, do not use tabs

In Python, indentation is very important to decide scopes when defining functions and making loops and tests. However, how long an indentation is optional, as long as each line is indented by the same amount of space. The most common is to use 4 spaces.

```{code-cell} python
def is_prime(n):
    if n == 1:
        return False

    for d in range(2, n):
        if n % d == 0:
            return False
    return True
```

In addition, the style guide recommends you use actual *spaces* in the code instead of *tab* characters. This is a minor, but important distinction in code. When indenting a code line one can either place a series of space characters, or a single tab character. Either work in most programming languages, but one should stick to one or the other. This has lead to huge "spaces vs tabs" debates among programmers. Usually, it is a setting in your editor how spaces vs tabs are handled.

Both spaces and tabs also work in Python, but do note that if you mix them inside the same indentation you will get an error
```
TabError: inconsistent use of tabs and spaces in indentation
```
PEP8 recommends sticking to actual spaces.


### When wrapping long lines, use parentheses to keep things together

When a line of code becomes very long, it will reach the end of the screen/editor. In such cases it is better to break the line yourself, instead of letting it simply run long. This is because you can then split the line in a location where it more structured and orderly.

As an example we write out the following line of code
```python
income = (
    gross_wages
    + taxable_interest
    + (dividends - qualified_dividends)
    - ira_deduction
    - student_loan_interest
)
```
Here we have written out one long code line. In Jupyter this code line will wrap to the next line when it reaches the end of the column. If this happens in your editor will depend on your settings.

An issue with word wrap is that others might have different settings to you, and so there is little control where the line break will happen. If it happens at a weird location (such as the middle of a variable), the line becomes hard to read.

Here you should instead split the line yourself. To do so, you can put parenthesis around the entire expression. Python will then automatically see the next line as a continuation from the first
```python
income = (
    gross_wages
    + taxable_interest
    + (dividends - qualified_dividends)
    - ira_deduction
    - student_loan_interest
)
```
The fact that parenthesis let's you split up your code over multiple lines is very useful also when you have very long function calls, here is an example taken from Project 1
```python
import matplotlib.animation as animation

ani = animation.FuncAnimation(
    fig, animate, np.arange(1, len(y)), interval=25, blit=True, init_func=init
)
```
Here the name of the function we import is long enough to begin with, and then we have many arguments and keyword arguments to use. Here you should split the line, which is easy to do since the arguments are all within a pair of parentheses.

### Separate top-level functions and classes by two blank lines

In the same way blank lines are used to structure a text into different chapters, sections or paragraphs, we can use blank lines in code to create some separation between different components of a larger code. This rules simply states that two blank lines should be put between different functions and classes, as these are different entities in your code.

### Class methods should be separated by one blank line

As class methods belong to the same class they often are more interconnected than top-level functions, and these can therefore be separated by a single blank line.

### Use blank lines in functions, sparingly, to indicate logical sections.

Because we use blank lines to separate different functions and methods, we should be a bit wary of using too many blank lines *within* a function or method definition, as this might make it harder to get an overview of where different function definitions start and stop. In some cases however, if a function or method have several clearly distinct logical sections, these can be separated by a line to make it clearer. In our `is_prime` example from earlier, we added a blank line between checking if 1 is a prime (which is a special case) to the more general trial-division loop.
```{code-cell} python
def is_prime(n):
    if n == 1:
        return False

    for d in range(2, n):
        if n % d == 0:
            return False
    return True
```

### Use UTF-8 encoding

This is simply a setting within your editor. Saving your Python-scripts with UTF-8 encoding enables us to use special characters in our Python code, which is nice.

### Put imports on separate lines at the top of the file

We have already discussed how imports should look in a Python-file. For one, you should put them at the top of your file, and you should avoid wildcard imports. In addition, PEP8 says to never import more than one package per line, i.e., don't write
```{code-cell} python
import math, numpy, scipy
```
instead write
```{code-cell} python
import math
import numpy
import scipy
```
When importing specific components from a single package, you can group several imports however, so this is fine:
```{code-cell} python
from math import pi, sqrt, exp
```

## Naming conventions

We now move over from some more general points in PEP8, to the first major topic: naming conventions, i.e., what we should name our variables when we code. The goal with naming conventions is to stick to a specific style, so that whoever is reading or using the code can easily gleam what sort of variable something is, from the name alone.

**Modules**

Modules are what we call Python-files. Module names should be short and written in all lowercase. Underscores are allowed and often used to separate different words. Example from Project 1: `double_pendulum.py` and `test_double_pendulum.py`.

**Functions**

Function names (including methods) should be defined similarly to module names, i.e., all lowercase and with words separated by underscores (`count_words()`, `is_prime()` or `save_file()`).

**Class names**

All classes should normally use the CapWords convention, meaning every word in the name should be capitalized, and no underscores are used (`Sphere`, `BankAccount`, `FunctionIntegrator`, and `DoublePendulum`)

**Variables**

Most variables should be names as we do for functions/modules, i.e., all lowercase and with underscores. As emphasized during our intro to object-oriented programming this convention makes it easy to differentiate classes from instances.
```python
u = Vector3D(4, 2, -2)
```
Note that the built-in data types break the class name convention (`tuple`, `int`, `list`, etc), but those are special cases.


**Constants**

A *constant* is a variable that is not expected to change during the execution of the program, and these should be written in all uppercase, parts separated by underscores (`MAX_WEIGHT`, `GRAVITATIONAL_CONSTANT`). An important exception here can be mathematical constants, which you can write on their typical mathematical form you desire, e.g. `pi` or `g` (for gravitational constant).

**In addition: Never use these single-letter names**

Never use `l` (lowercase L), `O` (uppercase O), or `I` (uppercase i) as single-letter names in your code. These can be easily confused for others character or downright indistinguishable in some fonts. Even if you can easily tell them apart in your editor, when you share your code (or print it out), it might look different.

## White Space

In programming, *white space* refers to the empty space that surrounds the rest of your code. We have already discussed blank lines, which is an example of white space, but space characters within a given code line is also very important for code readability.

People who are new to programming often skip using white space altogether, or they are inconsistent in using it. Try to stick to a consistent use of blank characters, and be a little detail oriented, it has a huge impact on code readability (especially so in mathematical expressions!)

Some examples from PEP8:

**Never a space between a function name and its arguments**

* Yes: `is_prime(21)`
* No: `is_prime (21)`

**A single space between each element in a list or sequence**

* Yes: `primes = [2, 3, 5]`
* No: `primes = [2,3,5]`
* No: `primes = [2 , 3 , 5]`

**Don't use spaces when using indices, and use `key: value` when using dictionaries**

* Yes: `spam(ham[1], {eggs: 2})`
* No:  `spam( ham[ 1 ], { eggs: 2 } )`

**Never put a space before the colon in `if`/`def`/`for`/`loop`**

* Yes: `if x == 4:`
* No: `if x == 4 :`

**Never place a space between a sequence and its indexing**

* Yes: `dct['key'] = lst[index]`
* No:  `dct ['key'] = lst [index]`

**Use a single space around assignments**

* Yes: `i = i + 1`
* No: `i=i+1`

and

* Yes: `x, y = y, x`
* No: `x, y=y, x`

and

* Yes: `submitted += 1`
* No: `submitted +=1`

**Whitespace in mathematical expressions**

As a rule of thumb, you should put on each side of binary `+` and `-`, as this signifies different terms in mathematics, but you shouldn't put spaces on either side of `*` and `/` (or unary `-`) as this is the same term, e.g.
* Yes: `hypotenuse = x*x + y*y`
* No: `hypotenuse = x * x + y * y`

or

* Yes:
```python
def f(x):
    return a * x**2 + b * x + c
```
* No:
```python
def f(x):
    return a * x**2 + b * x + c
```

This rule is actually more about mathematical priority than anything else, so if we add parentheses it can change around. For example

* Yes: `(a+b) * (a-b)`
* No: `(a + b) * (a - b)`

Here $(a+b)$ and $(a-b)$ have higher priority than the multiplication, so we only put spaces on each side of the multiplication.

There are not *strict* rules on how to use spaces when doing math, so use your own best judgment. However, not that you shouldn't add more than 1 space around operators, and always put a space on each side of a binary operator.




In Project 1 we have given you a real tricky mathematical formula to type in, and you should strive to use the correct white space, as it will make it a lot easier for you to avoid mistakes!

## Line Length and breaking lines

PEP8 states that no lines should go beyond 79 characters. This 80-width character limit in code is very common rule in code style guides, across many languages. Historically, some languages simply couldn't go above 80 characters, as they were made to work with [punch cards](https://en.wikipedia.org/wiki/Punched_card), which had limited physical space.

In modern times, there are no physical limits to line lengths, and we could in theory use whatever line lengths we want. However, keeping lines from becoming to long helps with readability, as long lines can be tricky to read. There is a reason newspapers and magazines stick to multiple narrow columns instead of very long lines. Another important point is that we have no control over what tools others use to read or write code. They might be working on a small laptop display, or using multiple columns of code on their screen simultaneously. If we write our code with a 130-character width, and they display it in an 80-character editor, many lines will overflow and break at arbitrary places, leading to messy and hard to read code.

It should be mentioned that the PEP8 guide of 79 characters is a bit on the short side, and many style guides allow for 100 or even 120 characters. The important point is not the specific number of characters, but rather that there should be a (reasonable) maximum line width, and we should manually break the lines when we go over this limit.


If we get lines that become longer than 79 characters, we need to break the line over several lines, the best way to do this is parentheses, as expressions inside parentheses can be split over multiple lines in Python without any other formatting needed. As it's mostly long mathematical expressions or function definitions/calls that get very long, parentheses are often already present.

When splitting a mathematical expression over multiple lines, the natural thing to do is split the lines at the operators, so that different lines contain the different terms.

Let us return to an example from earlier, where we split the line as follows
```python
income = (
    gross_wages
    + taxable_interest
    + (dividends - qualified_dividends)
    - ira_deduction
    - student_loan_interest
)
```
Note that we split the expression cleanly between two terms, also place the operator for the next term on the following line. This is easier to illustrate if we split it up further so we have one term per line as follows:

**Yes**-This code is structured, and it is easy to match operator and operand
```Python
income = (gross_wages
          + taxable_interest
          + (dividends - qualified_dividends)
          - ira_deduction
          - student_loan_interest)
```

**No**—operators sit far away from their operands (what is added and what is subtracted?)
```Python
income = (gross_wages +
          taxable_interest +
          (dividends - qualified_dividends) -
          ira_deduction -
          student_loan_interest)
```

Note also in these examples that we indent the following terms so that they all line up. This is very important for readability.

**No**-Continued lines start have no indent and are confused for code lines
```Python
income = (gross_wages
+ taxable_interest
+ (dividends - qualified_dividends)
- ira_deduction
- student_loan_interest)
```

Similarly, if we have a long function call, we should indent the arguments which we move down to the following line. Just make sure they are indented *further* than the following code line so that they are easier to distinguish!

**Yes** - Args follow from function definition
```Python
def long_function_name(
        long_var_one, long_var_two,
        long_var_three, long_var_four):
    assert long_var_one > 0
    ...
```

**No** - Args are hard to distinguish from function body
```Python
def long_function_name(
    long_var_one, long_var_two,
    long_var_three, long_var_four):
    assert long_var_one > 0
    ...
```

## How to use comments in code

Comments are a good tool that can make your code easier to understand. However, they can also be *overused*, in which case they might clutter your code more than they actually help. PEP8 gives some useful advice to how comments should and shouldn't be used.

### Comments that contradict the code are worse than no comments

Comments are meant to describe and explain the code they are written in. For this to be the case it is important that they are actually correct. Therefore, it is vital that you update comments if you change your code.

### Comments should be complete sentences

It is best for comments to be complete sentences. If a comment is a single word, they are in fact rarely needed.

### Use inline comments sparingly

*Inline* comments are comments that are placed on the same line as actual code, i.e., the comment appears at the end of the line. Such comments often add clutter, and are rarely needed. One case they can be useful is to state physical units when working in science, but comments explaining code is usually better to place on its own separate line.

Also, a comment should not state the obvious, or explain *what* the code is doing. The code itself is already explaining what it is doing, and you can assume your reader knows enough Python to understand that. Instead, a comment should explain *why* you are doing something. For example

Don't do this

```python
# Increment width
width = width + 1
```

But this could be useful

```python
# Compensate for border
width = width + 1
```

As a general comment, if you feel you need to write many comments to explain what your code is doing, it might often be better to simply structure your code differently to make it more easier to understand in the first place. Or as explained by Martin Fowler:

> “When you feel the need to write a comment, first try to refactor the code so that any comment becomes superfluous” - Martin Fowler

*Refactoring* code is the activity of changing it without changing its function. So for example changing variable names, moving code into functions or classes, etc.


## Some if-test conventions

PEP8 also has some recommendations for making easy to understand `if`-tests.

When checking if a variable is or is not `None` (as is very common to do with keyword arguments), do so explicitly with `is`:

* Yes: `if foo is None:`
* Yes: `if foo is not None:`

* No: `if foo == None:`
* No: `if foo != None:`
* No: `if not foo is None:`

Note also that checking if something is `None` is more strict than checking true/false. The following prints only if `foo` is *exactly* `None`:
```python
if foo is not None:
    print("***")
```
The following test however, prints if `foo` is `None`, `False`, 0, `[]`, `''`, etc.:
```python
if foo:
    print("***")
```

If you want to compare two variables using `is`, then these two tests are equivalent

* `if a is not b:`
* `if not a is b:`

Both of these work, but the first is much easier to read and understand, is therefore understandable.

If you are checking a boolean variable, don't compare it directly to `True` or `False`:

* Yes: `if is_prime(n):`
* No: `if is_prime(n) == True:`
* No: `if is_prime(n) is True:`


## Final rule: Avoid Foolish Consistency

As a final note on PEP8, it actually starts of by stating:
> A Foolish Consistency is the Hobgoblin of Little Minds

The goal of a style guide is to improve readability and consistency, but there will always be times were one should break with the rules. This is especially the case when strict adherence to the rule would *limit* readability.

In the end, good code is much more than good style. There is a great talk by Raymond Hettinger from PyCon2015 that goes into this:

* *[Beyond PEP 8 -- Best practices for beautiful intelligible code](https://youtu.be/wf-BqAjZb8M)*

This talk is well worth a watch to understand how to think about writing good and elegant Python code, and points out how focusing too much on code style might make you get lost in unimportant details rather than focus on how to actually design your code in a better way.


## Auto-formatting tools and *linters*

We have now talked a lot about code style, and as you can see there are many details to consider, and in many cases it might be hard to remember all these little details, especially when working on challenging problems where your focus is on other things!

Here software developers often rely on tools called [*linters*](https://en.wikipedia.org/wiki/Lint_(software)). Such tools can automatically look over your source code and find errors in errors, code that looks weird or inefficient or double check that you are sticking to your desired code style.

Some linters will simply tell you if code is breaking your desired style, while others are made to *auto-format* your code for you. Some examples of such tools for Python are
* [black](https://github.com/python/black)
* [flake8](http://flake8.pycqa.org/en/latest/)
* [autopep8](https://github.com/hhatto/autopep8)
* [pylama](https://github.com/klen/pylama)

Take for example *Black*. This is an auto-formatting code tool which you can run on any Python-script, and it will change the code to follow a consistent code style. Black doesn't follow the PEP8 style guide, but its own defined guide (which does resemble PEP8 quite closely).

Black can be run through the command line on a given file, e.g.,
```
~$ black vector.py
reformatted vector.py
All done! ✨ 🍰 ✨
1 file reformatted.
```

But if you want to use a tool like Black, it is more common to configure your chosen code editor so that it is run automatically for you when you save your file for example. Another option is to configure `git` so that it is run automatically every time you commit your code. In some larger teams, auto-formatters in `git` might be a very nice tool, as it ensures everyone commits code into the project code-base with the same, consistent code style.


## The Zen of Python

Another PEP that might be useful to know about, in addition to PEP8 (which is the code style), is PEP20, also known as the "Zen of Python". This is simply a collection of 19 simple "rules" or principles one typically want to follow to write good Python code. You can print the Zen of Python in its entirety by writing `import this`.

```{code-cell} python
import this
```

# Documentation

Software documentation is a guide that describe how a piece of software is structured, how it works, and how to use and maintain it. Good documentation helps people understand a piece of software, and well documented code can therefore easily be picked up by others for use or extending it. Poorly documented code however, is often usable only by its author, and it is hard for others to help develop, maintain or use it.

Poorly documented code is sadly quite common in the scientific field, and its a problem when many people who write and develop software are only in temporary positions. Code developed by master students, PhD's or post-docs will often be used or further developed long after that scientists leaves the group, and so should be well documented. Imagine starting in a lab and being given software consisting of many thousands of lines of code. The person who wrote it is gone, there is no documentation, and you have to figure out how to implement some new feature your advisor. This will lead to frustration and inefficient software development.



## Document Design and Purpose, not mechanics

In a perfect world, we would have time to develop extensive and perfect documentation of all software projects. However, in the real world, there is often not much time to devote to documentation. It is therefore important to spend your documentation time effectively, focus on the parts somebody *needs* to understand, namely the design and purpose of the code, as well as its inputs, outputs and adjustable parameters.

Also remember that people can always read the source code itself. So the documentation doesn't need to cover what is actually happening in the code down to the smallest detail. What they need is the big-picture view of the project, some tips on how the code is used and helpful pointers on what assumptions or restrictions the code might have.

## Have a good README file

The first tip we have for good documentation, is to have a proper README file in your projects code file. If you are using `git` for example, having a `README.md` file in your git repository will fulfill several important roles

* Anyone you share the code with should start by reading your README and get an overview of your code
* Your README can contain information about requirements of the code, how it is installed or run and how to interpret or use the results
* Having a `README.md` file in your repo will also automatically create a nice landing page if you have you repo on GitHub. This means it is easy to set up a nice web page to share your code with others if you need to do so.

A good starting point for writing a README file i <https://readme.so/editor>. This page provides a template README file with several suggested sections.

## Embed documentation within the software itself

When we think of documentation, it might be common to think of a separate user manual, text document or a website explaining the code, such as the README-file just mentioned. However, developing the documentation separate from the code itself is not generally recommended. For one thing, when someone updates the code, it is important the documentation is updated as well. It is more likely that this happens if the two are contained in the same piece of software. This way, we are also guaranteed somebody that gets the code gets the documentation. Because of these points, it is generally better to embed the documentation of the code directly into that code. This might sound a bit weird, but in Python there is a standard way to do this, which we will cover now.


## Documentation Strings

In Python, the most important thing to have good documentation is to write good *docstrings*. Docstrings are string literals you put as the first thing in modules or function definitions. For example:

```{code-cell} python
def factor(n):
    """Return the prime factorization of an integer."""
    if n == 1:
        return [1]

    factors = []
    while n > 1:
        for i in range(2, n + 1):
            if n % i == 0:
                factors.append(i)
                n = int(n / i)
    return factors
```

In this example code, the second line is the *docstring* of the function. It sort of acts like a comment, but note that it is not a comment line, as we do not use the comment symbol (`#`). It is instead a *string* which is written directly into the code (not saved to a variable). Docstrings are always placed where they are relevant, in this case immediately after a function (or method) definition. They are also common to put in the top of a module. When placed like this, they give the reader a good understanding of what the purpose is of a given module, class, function or method.


As mentioned. Docstrings are *not* comments, but strings. They do fulfill the same role as a comment, but they will also be automatically stored as a special attribute on the object called `__doc__`. For example:

```{code-cell} python tags=[]
print(factor.__doc__)
```

Similarly, when we place a docstring at the top of a module (a file), and we then import that module as a package in Python, the string will be stored as a `__doc__` attribute:

```{code-cell} python tags=[]
import vector
print(vector.__doc__)
```

The fact that docstrings can be accessed directly as attributes means it is very easy for editors and other tools to use *code introspection* to give us more information. For example in an iPython shell, we can use `help()` or write `??` immediately behind a function or class method to read that methods docstring. Similarly, in Jupyter you can also call `help`, or press `Shift+Tab` to read the docstring of the variable your cursor is located.

```{code-cell} python
u = vector.Vector3D(0, 4, 4)

help(u.unit)
```

In the same way that there is a `help` function that can be used to access the docstrings of code, there are tools that go through entire codes and compile automatic documentation. We will get back to this at the end of the lecture. For now, let us focus how these docstrings should be written.


### Writing good docstrings

There is a segment in [PEP8](https://www.python.org/dev/peps/pep-0008/) on docstrings, but there is an even more important PEP here:
* [PEP257—Docstring Conventions](https://www.python.org/dev/peps/pep-0257/)

This PEP is very short, and it will take you a few minutes to read. In your project work, we expect you to try to follow PEP8 and PEP257.

We now go through and show some of the important points of good docstring conventions.


#### Docstring Conventions

Always use triple double quotes (`"""This is an example."""`) to define your docstrings, even if they are single lines. This is both to give them a consistent style in your code, but also to make it easy to extend them to multiple lines later.

Docstrings should always be full sentences, starting with a capital letter and ending with a period. For simple functions or obvious cases, docstrings can be kept short and put on a single line.
```Python
def is_prime(n):
    """Check if an integer is a prime number."""
```
We put everything on single line, even the quotes. Don't leave blank lines above or below docstrings, they aren't needed. Also note that the docstring should prescribe the function or method's effect as a command ("Do this", "Calculate the gradient", "Return the ..."). Not as a description; e.g. don't write "Returns the pathname", "Computes the derivative...", and so on.

For simpler functions or methods, a single line docstring is great. For more complicated cases, we might want to write a longer docstring. As the string literal is already marked in triple quotes, you can easily split the string over multiple lines. Here, the convention is that you should still have the single sentence describing the function at the top - after this you put a blank line, then you can have a more extensive description spanning multiple lines. This longer comment can describe more in detail how the function works, and you can also write in what arguments and optional arguments the function takes.

Here is an example taken and considerably simplified from `numpy.gradient`
```Python
def gradient(f):
    """Return the gradient of an N-dimensional array.

    The gradient is computed using second order accurate central differences
    in the interior points and either first or second order accurate one-sides
    (forward or backwards) differences at the boundaries.
    The returned gradient hence has the same shape as the input array.
    """
```
Note that if the docstring spans multiple lines, we put the opening quotes on the same line as the summarizing sentence, but the ending quotes are put on a separate line.

Useful information for a docstring to contain
* summarize behavior of a function or method
* what argument it takes
* what output(s) it returns
* side effects
* what exceptions might be raised
* any restrictions on when it can be called
* optional keyword arguments should be indicated and explained

Just like for code style, there exists different *docstring styles*, you can find some examples [here](https://sphinxcontrib-napoleon.readthedocs.io/en/latest/). Personally I like the [Numpy style](https://numpydoc.readthedocs.io/en/latest/format.html), but there are also many other good ones. In IN1910 we don't expect you to follow a specific style like this to the letter, but reading [PEP257](https://www.python.org/dev/peps/pep-0257/) is a very good idea.


## Building automatic stand-alone documentation through code introspection

One very nice detail about defining good docstrings is that there are plenty of tools that will parse complete codebases and compile the docstrings into nice-looking, indexable and searchable documentation in the form of a PDF, a website or similar.

One of the most popular tools for doing this in Python is [Sphinx](http://www.sphinx-doc.org/en/master/), which was originally made to be used on Python's own documentation, and is thus used by all packages in the standard library and the scipy stack. So if you are looking up documentation of `numpy`, `matplotlib` or `scipy`, you are actually reading automatically compiled documentation based on the actual source code of these packages. In C++ there is an alternative tool that is possible to do the same as Sphinx, called Doxygen.

Setting up [Sphinx](http://www.sphinx-doc.org/en/master/) takes a little work, and makes the most sense for larger projects, so we do not expect you to do this in IN1910, but it can be a very nice little project to test out for yourself.

To get an understanding of how powerful such automatic documentation is, take a look at the numpy reference pages, for example the reference for [numpy.gradient](https://docs.scipy.org/doc/numpy/reference/generated/numpy.gradient.html). This is an example of good reference documentation. It shows what the function does, lists what inputs and optional inputs it takes, lists references and shows example. All of this documentation is automatically generated by Sphinx based on the the function's docstring, you can check this yourself by clicking the "Source" button in the top right, which gives you the source code of `numpy.gradient` where you can see directly the docstring. Note that in this case, the documentation is very extensive, because `numpy` is a standard library that is very well documented. When you make docstrings, they rarely have to be this extensive.

As with other tools, we can also integrate Sphinx with our Git repository. One example of this is the website [readthedocs.org](https://readthedocs.org/). You can create a user on this site, and set up so that it automatically pulls from your Git repository every time you make changes, and readthedocs then re-compiles the autogenerated documentation through Sphinx and hosts it. This way anyone who wants to use the code you share through git can find up-to-date documentation in a searchable, indexable manner. But you don't have to do anything other than write good docstrings to update this documentation.
