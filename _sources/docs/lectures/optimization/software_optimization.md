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

# Software Optimization

We are now getting to the end of IN1910. In fact, there are only four lectures left. We are now starting on our last new topic in IN1910: Optimization.

The four remaining lectures will be organized as follows:

| Lecture | Topics                     |
| ------- | -------------------------- |
| L21     | Benchmarking and Profiling |
| L22     | Mixed programming          |
| L23     | Parallel programming       |
| L24     | Summary of IN1910          |


## What is Software Optimization?

The word optimization gets thrown around, bet let us try to narrow down what we actually mean by it. The word *"optimize"* itself literally means to
* *optimize* — Make the best or most effective use of (a situation or resource).

To optimize software therefore means to make the software more effective. The word itself comes from the word "optimal", however, it is important to stress that making an "optimal" program is as good as impossible, as there is no single "optimal" program. The goal is therefore to make a program *better*, not to make it *the best*.

It is also important to clearly distinguish software optimization with [*mathematical optimization*](https://en.wikipedia.org/wiki/Mathematical_optimization). Mathematical optimization is, put simply, what input arguments or parameters minimize or maximize some mathematical function. This kind of optimization is also a very important topic, and is often related to numerical methods such as *Newton's method*. When simply using the term *optimization*, even when talking about programming, it is not always clear whether one refers to optimizing the code itself, or if one is solving an optimization problem. Here it is important to be clear.

In IN1910, we are looking at *software optimization*, not mathematical optimization. Our goal is to create more efficient programs.

### Efficient Programs

What do we mean by making more efficient programs? The main goal is often to make programs *faster*. Optimization is talking about *speed*. Optimizing a program is often about simply making it run faster. However, sometimes, optimizing might mean becoming efficient with other resources. One can for example optimize with respect to memory usage of the program, or with respect to broadband usage. For mobile programming, battery usage can be an important thing to optimize with respect to, or simply the the size of the program itself.

Optimizing with respect to different resources can often be a trade-of. For a given problem we might be able to make it run faster, but to do so, we need to also use more memory. Then we need to weigh the pros and cons and choose which to focus on.

For scientific programming, *speed* is usually what we care most about, and it is what we will mostly think about in IN1910.


## When to optimize?

The first question we want to look at, is *when* to optimize code. Ideally we would of course simply write efficient and optimal code from the get go, however, that is not realistic. When facing a new problem and coding, we already have our plate full simply trying to find a solution to the problem, if we at the same time was trying to optimize our code at every step, the whole process would take much longer and we would get stuck more easily.

Because of this concept, most proficient programmers recommend to postpone optimizing to *after* having developed code that works. This statement was formulated by Kent Beck as:
1. Make it Work
2. Make it Right
3. Make it Fast

I prefer to paraphrase Beck as
1. First make it work
2. Then make it elegant
3. Lastly, make it fast

Let us look at each step separately

### 1. First make it work

When you start solving a brand new problem or implement a new feature, you cannot possibly focus on everything at once. A major goal in programming is as always to work *incrementally*. Therefore, when you sit down with a new problem, you should *ignore optimization*, and instead focus on the basics. Simply: *How do I solve this problem?*

As you are breaking down the problem and implementing, and getting close to a working solution, you also need to *verify* that it works through verification and validation. This is done through rigorous testing, as we have covered earlier in the course. Writing an extensive test-suite of test cases, unit tests and integration tests can make us confident that we have a working solution.


### 2. Then make it elegant

After you have managed to break down your problem and created a solution that seems to work, the next step is to make it "elegant". Others refer to it as making the code "pretty", or as Beck calls it, making it "right".

The step of making the code elegant does not refer to the actual functionality of the code, but everything else. The major part of this step is referred to as [*refactoring*](https://en.wikipedia.org/wiki/Code_refactoring) code. Refactoring code means rewriting it, not to change its function, but to improve it in other ways.

Refactoring can include changing the overall structure of the code, for example splitting things into functions, classes or modules in different ways. But it can also mean rewrite single lines, or changing variable names. The goals are simple: making the code more structured and readable. The benefits is that the code is easier to read, easier to understand and easier to maintain and develop further.

> By continuously improving the design of code, we make it easier and easier to work with. This is in sharp contrast to what typically happens: little refactoring and a great deal of attention paid to expediently adding new features. If you get into the hygienic habit of refactoring continuously, you'll find that it is easier to extend and maintain code.
— Joshua Kerievsky, Refactoring to Patterns

When refactoring code, you should also look closely at your code style. When working fast at prototyping and solving new problems, you are most likely not strictly adhering to a given style guide, but before you put your code into production (handing it in, publishing it online, sharing it with colleagues, etc), you should go back through and make sure your style is consistent and solid.

Another important part of making code elegant, is to build in good documentation. In Python, this is about writing good docstrings. This step can wait until you have both developed working code, and then have refactored it. This is because if you write your docstrings *before* the code, then you might change things around so your documentation is no longer describing the actual code. And recall, wrong documentation is worse than no documentation.

After making the code more elegant through refactoring and rewriting, you should rerun all the tests you made in step (1). This is because in the process of changing things around and rewriting it, you might have accidentally broken your code. By rerunning the tests, you can verify that the behavior of the program itself is unchanged. This also emphasizes how important it is to implement good and extensive tests.


### 3.  Lastly, Make it Fast

And now we are finally at the optimization step. The important point is that it is placed *after* developing a working code, and making that code elegant. Only after you have done these steps can you start looking at how to make this code faster.

*How* to make the code faster is the topic we will turn to shortly. However, it is also important to emphasize that if we make changes to our code to make it more effective and faster, we should rerun tests and verify that our changed solution still solves the problem and that we have not broken it in our strive for speed.


## Should you Optimize?

The third step above was formulated as "Make it Fast", however, before you start doing this, you should also ask yourself *Should you even optimize?*  Optimizing code is a tricky task, and in the process of making your code faster, you are paradoxically spending time. If the goal of optimizing the code is to *save time*, you need to save more time with the optimized code than it takes to actually perform the changes.

The XKCD comic below illustrates this point by showing how much time you can invest into optimizing your code and still save time. As the comic illustrates, how much time you save by optimizing depends on *how many times you run your code*.

```{figure} ../../figures/xkcd1205.png
---
width: 700px
name: xkcd1205
alt: xkcd1205
---
**Source:** [XKCD #1205](https://xkcd.com/1205/)
```

It is important to stress that if the goal is to produce code that is to be shared with others or sold, making the code more efficient makes a *better* product, and so the goal is itself not to save your own time, but save others time. The table above is more from the point of view of writing and using your own code. In addition, sometimes optimization is done as a learning exercise, in which case the time used in the optimization isn't "wasted time". In other cases it is about showing of, earning epic bragging rights or winning programming competitions.

```{figure} ../../figures/xkcd974.png
---
width: 700px
name: xkcd974
alt: xkcd974
---
**Source:** [XKCD #974](https://xkcd.com/974/)
```

```{figure} ../../figures/xkcd1319.png
---
width: 700px
name: xkcd1319
alt: xkcd1319
---
**Source:** [XKCD #1319](https://xkcd.com/1319/)
```


## Benefits of optimization

Making programs run faster is not only about *saving time*. In scientific programming, if we are able to make a program or experiment run faster, it not only saves us time, but it also enables us to carry out experiments at a larger scale, better precision or simply to run more experiments. Optimizing for speed is therefore important in that it not only enables us to do things faster, but it enables us to do *more things*.


### Drawbacks of optimization

While *optimizing* and making more efficient code sounds great, it is important to remember that there are *drawbacks* to optimizing code as well.

The first drawback is, as already mentioned, that it simply takes a lot of development time. This development time could have instead been invested into making code that was more general, contained more features, was better tested and so on. For scientific programming, time spent optimizing code could instead have been invested into exploring the problems in other ways, or analyzing results, writing papers and so on.

Another aspect of optimization is that optimized code is also often less readable than less optimized, but more intuitive code. In the process of making the code faster, we are actually making it harder to read and understand. In effect, this also means that our code is also harder to maintain and further develop.

In addition to these drawbacks, it is also easy to introduce errors to our code when optimizing, and if we are not careful we get erroneous results.

There are therefore both benefits and drawbacks to optimizing code. You should therefore give some though to wether or not you even *want* to invest the time needed to properly optimize code, or wether you have code that is good enough for your current use cases.


## How to Optimize

If you have decided that you *want* to optimize your code, it's important to do so in a structured and organized manner, to ensure that we optimize things in an efficient manner. To do this, we will introduce some important techniques:
* Algorithm analysis to figure what the theoretical difference between different approaches is
* Timing and benchmarking to figure out *how fast is the code actually*?
* Profiling to understand *what parts of the code needs to be optimized*

We have already talked about algorithm analysis in this course, and here a big part of optimizing a program lies. By choosing a different algorithm or data structure to solve a specific problem, we can make our program a *lot* faster and scalable.

```{figure} ../../figures/writing_it_down.jpg
---
width: 700px
name: writing_it_down
alt: writing_it_down
---
```

## Timing and Benchmarking

Timing code is a good way to explore wether the steps we take to optimize our code is *actually* making things faster. There are many tools available for timing code, in Python, the built-in `timeit` package is a good choice. In Jupyter and iPython there are additional tools for using `timeit` to explore code fast.


Let us look at an example. In [this StackOverflow post](https://stackoverflow.com/questions/327002/which-is-faster-in-python-x-5-or-math-sqrtx) a user is wondering which is faster, using `math.sqrt(x)`, or simply writing `x**0.5` to compute the square root, or perhaps alternatively `pow(x, 0.5)`.

Now, this user was wondering which was fastest, and so simply asked. In fact, in addition to asking on StackOverflow, he also emailed the question to Guido van Rossum, the original creator of Python.

The email To Guide:
>There are at least 3 ways to do a square root in Python: math.sqrt, the '**' operator and pow(x,.5). I'm just curious as to the differences in the implementation of each of these. When it comes to efficiency which is better?

Guido actually responded to this mail with the following answer
> pow and ** are equivalent; math.sqrt doesn't work for complex numbers, and links to the C sqrt() function. As to which one is faster, I have no idea...

The interesting point here is that even Guido, Python's creator, doesn't immediately know which is faster. So if we don't know which option is fastest, and asking one of the top experts doesn't help. How can we check?

Timeit can be used to simply *check* through experimentation.


```{code-cell} python
import numpy as np
import math

x = 23145
```

```{code-cell} python tags=[]
%timeit math.sqrt(x)
```

```{code-cell} python tags=[]
%timeit x**0.5
```

```{code-cell} python tags=[]
%timeit math.pow(x, 0.5)
```

```{code-cell} python tags=[]
%timeit np.sqrt(x)
```

When we use `timeit`, the computer performs a numerical experiment. Simply repeating the call many times, and taking the average. The reason it repeats the code many times it that a single timing will be affected by *noise*. Timeit will itself decide how many calls to perform, depending on how long a single call takes. We can also force it to take a specific amount of loops, but this is often not necessary unless we want more fine control.

In our example, we only tried taking the square root of a single number, but let us instead try a large number of different numbers:

```{code-cell} python
def sqrt_numbers_math():
    for x in range(20000):
        math.sqrt(x)

def sqrt_numbers_exp():
    for x in range(20000):
        x**0.5

def sqrt_numbers_pow():
    for x in range(20000):
        math.pow(x, 0.5)

def sqrt_numbers_np():
    for x in range(20000):
        np.sqrt(x)
```

We can also store the time from a call to `%timeit` in jupyter, if we append the `-o` flag:

```{code-cell} python tags=[]
time_math = %timeit -o sqrt_numbers_math()
```

```{code-cell} python tags=[]
time_exp = %timeit -o sqrt_numbers_exp()
```

```{code-cell} python tags=[]
time_pow = %timeit -o sqrt_numbers_pow()
```

```{code-cell} python tags=[]
time_np = %timeit -o sqrt_numbers_np()
```

By carrying out timing experiments, we get an explicit control of how long different approaches to the same problem takes. Here for example, we learn that `np.sqrt()` is significantly slower than the other options. This is because `np.sqrt()` is made for also taking the square root of large arrays, and so it is not the best option for taking the roots of single numbers.

Now, while `np.sqrt()` is significantly slower, it is still *fast*, so for a program that computes a square root less than a thousand times for example, using `np.sqrt()` instead of `math.sqrt` won't make a noticeable difference. But if we are computing millions upon millions of roots, then the speedup might be noticeable.


Performing your own timing experiments rather than googling "which is faster, x or y" is a good habit. For one thing is that the info you find might be outdated, or belong to a different setup. Perhaps you find results for Python 2, but you are using Python 3? Or something changed in the newer numpy version, which you are using? If you use timing experiments on your own machine, you get empirical evidence of your own situation,.


### Timing lines, functions and modules

The `timeit` package can be used to test single statements, functions, or entire programs/modules. Which it makes sense to focus on depends on the specific problem, and where in the optimization process you are.


## Benchmarking

A [*benchmark*](https://en.wikipedia.org/wiki/Benchmark_%28computing%29) is a specific test case one can use to test different solutions to a problem, or different codes. You can create your own benchmark test before you start optimizing, so you have something specific to work up against. The important thing is to test the different versions of the code against the *same benchmark*. If you keep changing your benchmark along with your code, then you cannot have a proper handle on how the different versions of your code performs.

Benchmarks are also often formulated and then shared openly, as sort of a challenge to different people in the community. To have a publicly formulated benchmark makes it easier for different people to compare their solutions to a given problem against each other. This is especially true in computer hardware, where different CPU's and GPU's for example, are tested against different benchmarks to *rate* them against specific sources.


## Profiling

There is a rule of thumb in programming, called the 90-10 rule, which states that a program usually spends more than 90% of its time in less than 10% of the code. This has important consequences for how we should optimize a program. If you want to make a program more efficient, you should just open up the code, and go through it line by line looking for places to improve the speed. Because most of the code is not where the program spends a majority of its time, we are simply inefficient in where we use our time to optimize.

Instead, we should identify the portions of the program that hogs the majority of the execution time of our program. These are normally called the *bottlenecks* of a program. Before you even start to think about optimizing code, you should identify the bottlenecks. Now, you can make guesses of where these are, they will for example often be inside loops, because the contents of loops gets repeated many times.

However, research shows that most programmers, even very experienced programmers, are quite terrible at guessing at what parts of a program are the most inefficient. Except for the simplest cases, we cannot simply look at a code and say where the bottlenecks are. Therefore we turn to an important tool: Profiling.

A Profile is much like a timing experiment carried out on a function or a module. However, in addition to timing the total run-time, it keeps track of *where* in the code the different time is spent. This gives us information about the bottle necks.


### Example: The Drunkard's Walk

The following code models a random walker that takes random steps until it reaches some predefined position called "home". This problem is often known as the *Drunkards walk*, as it models a drunk person rambling until they get home and pass out.

We implement it in an object oriented manner.


```{code-cell} python
import numpy as np
import matplotlib.pyplot as plt

class DrunkardsWalk:
    def __init__(self, home):
        self.x = 0
        self.home = home
        self.history = [0]

    @property
    def position(self):
        return self.x

    @property
    def steps(self):
        return len(self.history)

    def is_at_home(self):
        return self.position == self.home

    def step(self):
        self.x += 2*np.random.randint(2) - 1
        self.history.append(self.x)

    def walk_home(self):
        while not self.is_at_home():
            self.step()
        return self.steps

    def plot(self):
        plt.plot(range(self.steps), self.history, alpha=0.7)
```

```{code-cell} python tags=[]
drunkard = DrunkardsWalk(100)
steps = drunkard.walk_home()
drunkard.plot()
plt.show()
print(drunkard.steps)
```

```{code-cell} python
for walker in range(5):
    drunkard = DrunkardsWalk(100)
    drunkard.walk_home()
    drunkard.plot()

plt.show()
```

Let us profile this code. In Python, a standard package for profiling is `cProfile`, which should come pre-packaged with your python installation.

```{code-cell} python tags=[]
import cProfile
np.random.seed(100122)
cProfile.run('DrunkardsWalk(100).walk_home()')
```

The output from cProfile shows the time used by the different functions of the program. For each function, a row is printed. The name of the function is shown on the right-most side. The other columns show different information
* **ncalls**: The number of times the function is called
* **tottime**: Time spent inside the function without sub-functions it calls
* **cumtime**: Time spent inside the function *and* inside functions it calls
* **per call**: The time divided by number of calls



To understand which parts of the code are the slowest, we need to look down the `tottime` column and find the biggest number. Here the three biggest are:
* `randint()` with 1.091 seconds
* `step()` with 0.446 seconds
* `walk_home()` with 0.282 seconds

At the top it says the total time of execution as 2.139 seconds, and so `randint()` uses about half of our programs execution time.

Note also that there are some rows to functions that are technical, such as `method 'disable' of '_lsprof.Profiler' objects`, which you can simply ignore.


### More on cProfile

The `cProfile` package is a good tool for performing *function profiling* in Python. This means it explores how much time different functions spend. To get more control on how to analyze the outputs of `cProfile`, instead of just writing out a big table, we can use the `pstats` package ("profiling stats"). You can read more about `cProfile` and `pstats` on the official [Python documentation here](https://docs.python.org/3/library/profile.html).


## Line Profiling

An alternative to *function profiling* with cProfile, is to *line profile*. This means it divides the time use of your program into each separate line. The benefit of line profiling is that it doesn't just tell you which function is slow, but exactly where inside a function which is slow.

To do line profiling in Python, you can use the `line_profiler` package. This needs to be installed. If you are using an anaconda installation, install it by writing:
- Anaconda Python: `conda install line_profiler`

Otherwise, install it using pip:
- Other Pythons: `pip3 install line_profiler`


To use `line_profiler` inside a notebook, we need to load it as an external tool

```{code-cell} python
%load_ext line_profiler
```

```{code-cell} python
lpres = %lprun -r -f DrunkardsWalk.step -f DrunkardsWalk.walk_home DrunkardsWalk(100).walk_home()
```

Here we are telling `line_profile` to run the statement `DrunkardWalk(100).walk_home()` and analyze the performance of the two explicitly mentioned functions. The output pop up in a separate window:
```
Timer unit: 1e-06 s

Total time: 3.18336 s
File: <ipython-input-75-b157087bcb36>
Function: step at line 21

Line #      Hits         Time  Per Hit   % Time  Line Contents
==============================================================
    21                                               def step(self):
    22   1366246    2600136.0      1.9     81.7          self.x += 2*np.random.randint(2) - 1
    23   1366246     583225.0      0.4     18.3          self.history.append(self.x)

Total time: 5.77839 s
File: <ipython-input-75-b157087bcb36>
Function: walk_home at line 25

Line #      Hits         Time  Per Hit   % Time  Line Contents
==============================================================
    25                                               def walk_home(self):
    26   1366247    1015881.0      0.7     17.6          while not self.is_at_home():
    27   1366246    4762509.0      3.5     82.4              self.step()
    28         1          3.0      3.0      0.0          return self.steps
```
So we can see that line 22, increment the position itself, takes up 81.7% of the time it takes to use the `step()` method. Perhaps we can improve this by vectorizing with numpy? Appending the elements to the history takes 20% of the time, which is also a considerable amount. Perhaps it would be better to initialize an empty array and then just update the elements?

(software-optimization:memory-optimization)=
## Memory optimization
One of the main optimizations that was added to the python language in the transition from python 2 to python 3 was that


## Taking a step back: The Rules of Optimization

We are now out of time for this lecture. And we will return to a specific example of optimization in the next lecture. For now, let us take a step back and focus on the big picture again.

We have taken time to discuss that if one wants to optimize, one should do so after getting the code to work properly, and making it elegant. Even then, we should take time to weigh the pros and cons and see if we actually want to optimize our code before starting.

If we start optimizing, we should also first get a proper handle of the bottlenecks of the program and focus on those, leaving the rest of the code alone.

This is summarized by what is called the [*rules of optimization*](http://wiki.c2.com/?RulesOfOptimization)
1. The first rule of optimization: Don't do it.
2. The second rule of optimization: Don't do it... yet.
3. The third rule of optimization: Profile before optimizing!



### The root of all evil

A famous quote in programming is called *the root of all evil*, and was made by Donald Knuth:
> Programmers waste enormous amounts of time thinking about, or worrying about, the speed of noncritical parts of their programs, and these attempts at efficiency actually have a strong negative impact when debugging and maintenance are considered. We should forget about small efficiencies, say about 97% of the time: premature optimization is the root of all evil. Yet we should not pass up our opportunities in that critical 3%."

Knuth is remarking on rule *3*, that one should not try to optimize one's entire program, but just the critical 3%. The quote is often shortened to simply *"premature optimization is the root of all evil*, which also neatly summarized the fact that rule we started with: First make it work, then make it elegant, lastly make it fast. If you start optimizing while solving the problem for the first time, you are *prematurely optimizing*.

```{figure} ../../figures/xkcd1691.png
---
width: 700px
name: xkcd1691
alt: xkcd1691
---
**Source:** [XKCD #1691](https://xkcd.com/1691/)
```


As an ending thought: We might seem overly harsh on optimizing code in this lecture. However, we **do** think optimization is important and that it **should be done**. We are simply trying to point out that there is a *time* and a *place* for optimization. In addition it should be done in a structured, systematic manner.

Some take quotes like *"premature optimization is the root of all evil"* too much to heart and forgo optimization altogether, however, this is also far from ideal, which the full quote actually addresses! However, some people think the quote is used to justify laziness and bad practices, leading some to claim that:
> “Premature optimization is the root of all evil” is the root of evil. [Source](https://medium.com/@okaleniuk/premature-optimization-is-the-root-of-all-evil-is-the-root-of-evil-a8ab8056c6b)
