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

# Debugging in python

Bugs are errors or a flaw in your program that makes the program not behave as expected. Debugging is the processes of finding bugs and resolving them.

Being able to quickly resolve bugs if often a skill that differentiate a senior developer from a junior developer. The senior developer has more experience and have a better understanding what might cause a bug, and would therefore know where in the code the bug most likely originates.

While this might be true, it is not always the case that the senior developer knows the codebase where the bug is, and therefore being able to utilize *debugging tricks* that will speed up the process of finding the bugs is often crucial.

In this section we will show you have to use a debugger in python, which is often overseen by junior developers. Learning how to use a debugger will change the way you debug programs.

## Print statements (logging)
The most basic way you can debug your code is to add a bunch of print statements everywhere that will print the state of the program. That way, you are more likely to find the source of the bug more easily.

There are several drawbacks with this. First of all, the amount of information that is printed might be huge, and therefore being able to filter out the relevant information might be tricky.

Another drawback is that if you manage to track down the bug, you will end up with a lot of print statements all over your code which you will need to remove.
However, having the print statements there is also kind of nice in case you encounter a bug in the future.

This is of course a very typical situation, and the way you solve this is be implementing a logger, e.g using the [python built in logging module](https://docs.python.org/3/library/logging.html).

When you have a logger you will create a print statement which also contains a logging level. The logging level will typically be `WARNING` which is stuff you really want to know (for example something unexpected happened in your program), `INFO` which is the normal output that should be printed by default and `DEBUG` which will print detailed information which is relevant when tracking down bugs.

When you run you program you will also specify the logging level which allow you to get more or less information depending on what you want to do. Lets look at a simple example. This first thing we need to do is to import the `logging` module and call the `basicConfig` method. This will make sure that logging is configured

```{code-cell} python
import logging

logging.basicConfig()
```

Now lets create a logger

```{code-cell} python
logger = logging.getLogger(name="My fancy logger")
```

Here we create a logger and give it the name `"My fancy logger"`. Then we assign it to a variable `logger`. To print out a warning message, you can write
```{code-cell} python
logger.warning("This is a warning")
```
and a see that a warning message it printed. We also see that the string that is printed consists of the log level (`"WARNING"`), then name of the logger (`"My fancy logger"`) and the message. Now lets try to print an info message
```{code-cell} python
logger.info("This is an info message")
```
We see that nothing is printed. This is because when a logger is created, the default logging level is set to `WARNING`. To change the log level to `INFO` we call the `setLevel` method on the logger
```{code-cell} python
logger.setLevel(logging.INFO)
logger.info("This is an info message")
```
Now we see that the info message is displayed. The warning message also still prints because warnings have higher priorities than info messages
```{code-cell} python
logger.warning("This is a warning")
```
However, debug message are not printed. To print a debug message you need to use the `debug` method.
```{code-cell} python
logger.debug("This is a debug message")
```
Again, you can change the log level to `logging.DEBUG` to also see debug messages. Here is an example where we create three different loggers with three different log levels

```{code-cell} python
logger1 = logging.getLogger(name="First logger")
# logger1.setLevel(logging.WARNING)
logger1.warning("This is a warning")
logger1.info("This is an info message")
logger1.info("This is an debugging message")

logger2 = logging.getLogger(name="Second logger")
logger2.setLevel(logging.INFO)
logger2.warning("This is a warning")
logger2.info("This is an info message")
logger2.debug("This is an debugging message")

logger3 = logging.getLogger(name="Third logger")
logger3.setLevel(logging.DEBUG)
logger3.warning("This is a warning")
logger3.info("This is an info message")
logger3.debug("This is an debugging message")
```

Finally, logging in python is highly configurable. You can change the way log messages are printed, as well when you want the log message to go (e.g in the terminal or in a file). The fact that the logging module is so configurable also makes it a bit difficult to use correctly. Therefore there other logging packages that tries to simplify logging in python. Some popular libraries are [`struclog`](https://www.structlog.org/en/stable/) and [`loguru`](https://github.com/Delgan/loguru).

## Using a Debugger

Python comes with a built in debugger called `pdb` which stands fro Python DeBugger. Let us see how we can use it. To illustrate the example we will try to debug the following program which we will write in a file called `debugme.py`

```python
# debugme.py


def div(x, y):
    return x / y


def sub(x, n):
    return x - n


def solve(x, y):
    y2 = sub(y, 1)
    return div(x, y2)


def main():
    solve(2, 1)


if __name__ == "__main__":
    main()
```

If you try to run this program you will see the following error message

```
$ python debugme.py
Traceback (most recent call last):
  File "/Users/finsberg/local/src/IN1910/debugme.py", line 19, in <module>
    main()
  File "/Users/finsberg/local/src/IN1910/debugme.py", line 15, in main
    solve(2, 1)
  File "/Users/finsberg/local/src/IN1910/debugme.py", line 11, in solve
    return div(x, y2)
  File "/Users/finsberg/local/src/IN1910/debugme.py", line 2, in div
    return x / y
ZeroDivisionError: division by zero
```

Something is going on here, and we will try to use a debugger to find out.

### Post-mortem debugging

Post-mortem refers to "after death" and post-mortem debugging means that you will start the debugger after the program has crashed.

We can initiate a post-mortem debugging session by running the script as follows

```
$ python -m pdb debugme.py
```

When you execute this command, python will start the debugger (before running your script), and it will throw you into a session that would look something like this

```
> /Users/finsberg/local/src/IN1910/debugme.py(1)<module>()
-> def div(x, y):
(Pdb)
```

You are now inside the debugger. To run the script you can type `c` (or `cont` or `continue`) and you will run the script.


Now you will see something similar to this in your terminal

```
(Pdb) c
Traceback (most recent call last):
  File "/Users/finsberg/.pyenv/versions/3.10.4/lib/python3.10/pdb.py", line 1726, in main
    pdb._runscript(mainpyfile)
  File "/Users/finsberg/.pyenv/versions/3.10.4/lib/python3.10/pdb.py", line 1586, in _runscript
    self.run(statement)
  File "/Users/finsberg/.pyenv/versions/3.10.4/lib/python3.10/bdb.py", line 597, in run
    exec(cmd, globals, locals)
  File "<string>", line 1, in <module>
  File "/Users/finsberg/local/src/IN1910/debugme.py", line 19, in <module>
    main()
  File "/Users/finsberg/local/src/IN1910/debugme.py", line 15, in main
    solve(2, 1)
  File "/Users/finsberg/local/src/IN1910/debugme.py", line 11, in solve
    return div(x, y2)
  File "/Users/finsberg/local/src/IN1910/debugme.py", line 2, in div
    return x / y
ZeroDivisionError: division by zero
Uncaught exception. Entering post mortem debugging
Running 'cont' or 'step' will restart the program
> /Users/finsberg/local/src/IN1910/debugme.py(2)div()
-> return x / y
(Pdb)
```

Again you are inside the debugger. Now, let us ask the debugger where we are in the program by executing the command `where` (or `bt` for backtrace)

```
(Pdb) where
  /Users/finsberg/.pyenv/versions/3.10.4/lib/python3.10/pdb.py(1726)main()
-> pdb._runscript(mainpyfile)
  /Users/finsberg/.pyenv/versions/3.10.4/lib/python3.10/pdb.py(1586)_runscript()
-> self.run(statement)
  /Users/finsberg/.pyenv/versions/3.10.4/lib/python3.10/bdb.py(597)run()
-> exec(cmd, globals, locals)
  <string>(1)<module>()
  /Users/finsberg/local/src/IN1910/debugme.py(19)<module>()
-> main()
  /Users/finsberg/local/src/IN1910/debugme.py(15)main()
-> solve(2, 1)
  /Users/finsberg/local/src/IN1910/debugme.py(11)solve()
-> return div(x, y2)
> /Users/finsberg/local/src/IN1910/debugme.py(2)div()
-> return x / y
(Pdb)
```

So we are at the the line 2 (see the 2 in ` /Users/finsberg/local/src/IN1910/debugme.py(2)div()`) where `div` function returns `x / y`.

To see another view you can type `list`, which will list the code and put an arrow where you are right now

```
(Pdb) list
  1     def div(x, y):
  2  ->     return x / y
  3
  4
  5     def sub(x, n):
  6         return x - n
  7
  8
  9     def solve(x, y):
 10         y2 = sub(y, 1)
 11         return div(x, y2)
(Pdb)
```

What else can we do? Well, we can see what arguments are defined in this scope by executing the command `args`

```
(Pdb) args
x = 2
y = 0
(Pdb)
```
And we see that we have two arguments defined `x` which has the value 2 and `y` which has the value `0`.  You can also explicitly type these variable and the debugger will print out the value

```
(Pdb) x
2
(Pdb) y
0
(Pdb)
```

At this point you probably have an idea on why the program failed. You are trying to divide 2 by 0, which will result in a `ZeroDivisionError`. However where does these values come from? To answer this, we would need to go up one level to the function that called the `div` function. Looking at backtrace

```
(Pdb) bt
  /Users/finsberg/.pyenv/versions/3.10.4/lib/python3.10/pdb.py(1726)main()
-> pdb._runscript(mainpyfile)
  /Users/finsberg/.pyenv/versions/3.10.4/lib/python3.10/pdb.py(1586)_runscript()
-> self.run(statement)
  /Users/finsberg/.pyenv/versions/3.10.4/lib/python3.10/bdb.py(597)run()
-> exec(cmd, globals, locals)
  <string>(1)<module>()
  /Users/finsberg/local/src/IN1910/debugme.py(19)<module>()
-> main()
  /Users/finsberg/local/src/IN1910/debugme.py(15)main()
-> solve(2, 1)
  /Users/finsberg/local/src/IN1910/debugme.py(11)solve()
-> return div(x, y2)
> /Users/finsberg/local/src/IN1910/debugme.py(2)div()
-> return x / y
(Pdb)
```

we see that `div` was called from `solve`. Would it be possible to jump up one level to the `solve` method? Yes! Let us execute the `up` command

```
(Pdb) up
> /Users/finsberg/local/src/IN1910/debugme.py(11)solve()
-> return div(x, y2)
(Pdb)
```

Now, type `list` again

```
(Pdb) list
  6         return x - n
  7
  8
  9     def solve(x, y):
 10         y2 = sub(y, 1)
 11  ->     return div(x, y2)
 12
 13
 14     def main():
 15         solve(2, 1)
 16
(Pdb)
```
and we see that the arrow has now moved to the `solve` method. Let's look at the arguments
```
(Pdb) args
x = 2
y = 1
(Pdb)
```
and we see that `y` is 1. However if we type `y2` we see that it is zero
```
(Pdb) y2
0
```

Anther useful command is `interact`

```
(Pdb) interact
*interactive*
>>>
```
which will start and interactive python session.

Finally to exit the debugger you hit `q`, `quit` or `Ctrl+D`.

This was just a taste of what you can do with a debugger. Executing the command `help` will show you all the commands you have available in the debugger.


### Adding a breakpoint

If you know where in the program you want to start the debugger, you can add something called a breakpoint. For example let us add a breakpoint inside the `sub` method by modifying the code as follows

```python
def sub(x, n):
    breakpoint()
    return x - n
```
Now you can run python in a normal way (i.e without the `-m pdb` flag)

```
$ python debugme.py
> /Users/finsberg/local/src/IN1910/debugme.py(7)sub()
-> return x - n
(Pdb)
```
We see that it started the debugger at the point where we set the breakpoint. Again you move around and print the arguments and variables.

## Using an improved debugger

The built in debugger in python is very basic. Therefore, it might be a good idea to upgrade the debugger to a more developer friendly debugger. My recommendation is to use `pdb++`. If you install this debugger

```
python -m pip install pdbpp
```
python will use this debugger by default. This will add syntax highlighting and tab completion to your debugger which is much nicer to work with. Using `pdb++` in stead of `pdb` would be similar of using `IPython` instead of regular `Python`.
