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

# An introduction to C++

This week we will start to turn to a new programming language, C++. We will use this language, in combination with Python, for the rest of the course. You will learn how to read and write short C++ programs, and how to compile and run them. Our goal is to make you at least somewhat familiar with C-style code, and also to make you aware of the major differences between Python and C++. Note however, that the world of C++ is big, and to get proficient at C++ one has to dedicate a lot of time and effort to it, certainly more than we have time for in IN1910. The goal is therefore to give you a taste of the language and an overview that can come in handy down the road.

C++ is a hard language to learn, and also a hard language to use. There is a joke in the programming world, that everyone should learn C++ as their first language, because after that any other language will seem easy. While that might be an exaggeration, it is definitely a more technical language than Python. The best piece of advice we can give you before we start is simply: *don't panic*. We don't expect you to become experts in this course, and so the goal is more that you can write some cool programs, rather than take away all the fundamentals.

## A Python to C++ transition guide

The book *Object-Oriented Programming in Python*, written by by Michael H. Goldwasser and David Letscher has a supplemental document called *A Transition Guide from Python 2.x to C++*. Both the book and supplement are freely available as pdf-files on the [book's website](http://cs.slu.edu/~goldwamh/oopp/). The supplement is $\~90$ pages, and covers most of what we will use in this course. It can be a good document to work through if you prefer reading on your own above lectures. The supplement is written for Python 2, but the differences are so small, this should be of no big concern.

[Direct link to *A Transition Guide from Python 2.x to C++* by Goldwasser and Letscher](http://cs.slu.edu/~goldwamh/publications/python2cpp.pdf)

Another great resource is [C++ for python programmers guide](https://cs.berea.edu/cpp4python/) which contain interactive code sample and quizzes.

### The definitive C++ book guide and list

If you want a dedicated C++ book, there exist many out there. I would recommend reading through StackOverflow's [Definitive C++ Book Guide and List](https://stackoverflow.com/questions/388242/the-definitive-c-book-guide-and-list) to find one that is worthy of both your time and money.

## Why C++?

So why are we learning C++ as our second language?

C++, like many other languages, is based on C. C is an old language, created in 1972, but still sees wide use today. It is a low-level language that compiles into highly efficient machine code—put simply, C is blazing fast. While C is important historically, it is still one of the most used languages today. A lot of much used software, such as UNIX and the main implementation of Python, is written mainly in C.

C++ is a direct extension of the C programming language, with the motivation of adding classes to the language. The syntax and semantics of the two languages are therefore nearly identical. The major difference is that C++ has larger standard libraries and more support for higher level constructs, such as object-oriented programming. C++ still retains most of the low-level features of C however, and if implemented correctly, will be highly efficient and fast.

Several other popular languages are also, at least partially, based on C, such as C# and Objective-C. Other languages, like Java, borrow most of their syntax from C. While Java is very different "under the hood", and runs quite different from C, the code itself looks quite a bit alike. In short, many, many languages today have a strong "C-flavor" to them, and dedicated programmers are more or less expected to know some C-style language.

So to summarize: We want to learn a C-style language, because it is extremely useful for any programmer to know one of these languages, as it makes learning any of the others a lot easier. We also want to have a highly efficient language, to be capable of making fast and large computations. This requirement means we prefer to choose C or C++ over Java. Lastly, as we are learning object-oriented programming in this course, C++ is the natural choice over C.

Ok. Enough talk, let's get to learning some actual C++!

## How to write, compile and run C++ programs

As our first introduction to the language, let us write a *Hello, World* program. Open your favorite text editor and create a new file called `hello_world.cpp`.

Here, you can already note that `.cpp` is a file extension for C++ source code, i.e., the file we write the code itself. This is only one possible file extension, and other common ones are `.cc`, `.cxx`, or `.c++`. We stick with `.cpp` in this course.

Also note that some people advocate using IDEs for C++ (such as Qt Creator), and for larger projects, this can be very helpful, as we need to link many different files, which an IDE can help with. In this course however, we will stick mainly to single file C++ programs, and so getting a dedicated C++ IDE is not necessary.

## Your first C++ program
Before you start writing any C++ code and try to compile and run it, make sure that you have read through the [C++ installation guide](../../setup/cpp_compiler.md).

In our fresh file, we enter our *Hello world* code. Which will look something like the following:

***
````{tab} C++
```c++
#include <iostream>

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}
```
````
````{tab} Python
```python
if __name__ == "__main__":
    print("Hello world")
```
````
***

Here you can also compare with the `python` *Hello world* example. An `if __name__ == "__main__"` block is included to make the two examples look a bit more similar.

Before we cover how to compile and run this code, let us read through and analyze what is happening in the C++ version.

The program starts out with an `#include` statement, which is like importing files in Python. This statement means we are including a so-called *header file* (more on headers later). Here we include the standard header `iostream` (input-output stream). We need to include this header to be able to output our message.

Next we define a function named `main`. In C++, we have to define a *main function*. Executing the program is the same as calling this function. It has to be specifically named `main`, or you will get an error. You can think of this function as the starting point of our program which will be executed if you run the program directly. In fact this is not too different from python, which does this using an `if __name__ == "__main__"` block instead. The main-block in Python is however far less restrictive.

We write `int main()` because our function *returns an integer* (i.e an exit code see {ref}`python:exit-codes`), is named *main*, and takes no input. The contents of our function go between two curly braces (`{` `}`).


```{figure} ../../figures/function_declaration.png
---
width: 300px
name: function_declaration
alt: function_declaration
---
Declaring the *main* function of a C++ program.
```

Inside our main function, we do two things:
1. we write out our message,
2. we return the integer 0.

When we write out our message we use `std::cout`, this isn't the only way to print in C++, but it is the recommended way. Here, `std::cout` is an *output stream*, and anything we insert into this stream will be written out. We insert things using double angel brackets (`<<`). We then write out our message as a text string, using `"` as delimiters. In Python we use `"` and `'` interchangeably, but in C++ `"` denote string literals, while `'` denote single character literals. We also have to end each statement in C++ with a semicolon (`;`), so we end our output line with a semicolon.

Writing `cout << a << b` just outputs the two things in order, so here we first insert our message, and then `std::endl`. Here *endl* stands for *end line*, and is basically just a newline character. An alternative to inserting `std::endl` would have been to just write in a newline character in our string: `"Hello, world!\n"`. (There is a subtle difference between using `endl` and `\n`, you can read about it on [StackOverflow](https://stackoverflow.com/questions/213907/c-stdendl-vs-n) if you are curious).

We write `std::` because we are using variables that come from the `iostream` header, and this is a *standard* header, and so `std::` means we are accessing something contained in the `std` namespace. If we import from other packages, we would need a different namespace, such as `arma::` (for the [Armadillo libraries](http://arma.sourceforge.net/)) or `boost::` (for the [Boost libraries](https://www.boost.org)). In most of our programs, we won't use that many packages, and we will mostly stick to standard headers, which in turn means we will write a *lot* of `std::`, which is a bit annoying. What we can do to avoid this is to declare `using namespace std;` at the top of our program. This tells the compiler that when we call a function, it will look for the given function in the `std` namespace, and so we can replace `std::cout` with just `cout`, and so on. For our `hello_world.cpp` script, this doesn't help that much on tidiness, but in larger codes, having a single declaration instead of dozens of `std::` can be preferable.

Finally, we return `0` from our main function by writing `return 0;`, the same as in Python except for the fact that we need to end our statement with a semicolon. After returning, we are done with our function declaration, so we include our closing curly brace (`}`). Why do we return 0? Recall that our main function is the function that is called by the system when we want to execute our program. When the program finishes, we should return something to the system so that it knows the program is finished. It is customary to return an integer, and we return 0 if the program terminated successfully. If the program aborted or crashed, we return any other integer. Depending on what caused the erroneous termination, we can return a different number, which would be an *error code*, that can tell the system something about what went wrong. We won't use these much in this course, simply put, we always return 0 at the end of our main function, and if something goes wrong, we will instead throw an exception.


## Compiling and Running C++ programs

We have now written and analyzed our C++ code, but how do we actually run it? Here, things will be quite different from Python, because C++ code first needs to be *compiled* before we can run it.

### Interpreted vs Compiled Languages

One of the major differences between Python and C++ is that Python is an *interpreted* language, while C++ is a *compiled* language. When we write a Python program, our source code, and our program, is one and the same. To run our program we invoke the Python interpreter, which reads our code and executes it as it goes.

For C++ programs however, we write our code to a file, but this file cannot be executed directly. Instead we have to turn our source code into an executable program, and this step is known as *compiling the code*. We compile code by invoking a C++ compiler that reads our code. However, unlike the Python interpreter, the compiler doesn't execute our code, instead it translates it into low-level executable machine code, making sure to specialize our code to the system we are compiling on. What we end up with is an *executable*, a program we can execute to run. This program is now executed directly by our machine, and we don't need to invoke a separate "C++ interpreter", as the code has already been translated to codes the machine can understand.


```{note}
Python does also perform a compilation step where the source code (the text you write in the `.py` file) is compiled to something called bytecode which are files with the suffix `.pyc`. You will see them appear in a folder called `__pycache__`. So in that regard python is also a compiled language, but we typically think of compiled languages as languages that compile the code into machine instructions such as C++. You can read more one this topic if interested [here](https://stackoverflow.com/questions/6889747/is-python-interpreted-or-compiled-or-both).
```

Most editors and IDE's have some functionality to compile (also called building) C++ source code into executables. And learning these could be good for your workflow. However, it is still important to learn how to do it "manually" in the command line as well.


If you are using Linux, then you will most likely use the GNU compiler (called GCC). This is one of the main C++ compilers. On Windows, you can also use GNU (through for example Cygwin), but perhaps more common is to use Visual C++. Many other C++ compilers exist. On MacOS the default compiler is called Clang which is also very popular.

This week's exercises will tell you more about installing a C++ compiler if you do not already have one installed.


### How to compile your program

We will now compile our C++ code by invoking our compiler in the terminal. For our examples, we will be using the GCC compiler, if you are using a different compiler, the commands will change slightly, but it should largely be the same.

If you haven't installed a compiler yet, please checkout the [installation instructions](../../setup/cpp_compiler.md) before moving on.

If you are using GCC or Clang, you invoke the C++ compiler in the terminal by writing `c++`, we must also supply it with what source code that should be compiled, so we write:
```
c++ hello_world.cpp
```


### Executing your program

When we run `c++` to compile our code, the compiler tries to analyze the code and creates an executable. However, we have given no name for our executable, and so it defaults to the filename `a.out`, which is the name of our program.

To run the `a.out` executable, we simply invoke it directly
```
./a.out
```
Running this program, if everything is done correctly, gives us the expected *"Hello world"* output.

Note that you can get errors in both the *compilation* of the program, and in *the execution*. The compiler might protest and abort when compiling the source code, in which case we get no executable. Or the compiler might execute without any issue, but when running the source code, we get some error. This is because the compiler tries to catch errors, and will catch syntax errors and the like. However, some errors are not found by the compiler, and these might sneak into our executable.

### Naming executables

The name `a.out` is generic and not very descriptive. To improve this, we should compile our program into an executable with a specific name. We do this by adding an output-flag: `-o name`, where you can name the executable whatever you want: so for example:
```
c++ hello_world.cpp -o hello
```
Would create an executable called `hello`, which we would run directly in the terminal:
```
./hello
```
Note that we don't give this executable any file ending. This is very common for executables on UNIX machines. On windows, they are often given the ending of `.exe`, short for *executable*.

Note also that the output name can also be put before the source code:
```
c++ -o hello hello_world.cpp
```
The order is just personal preference.

### Other compiler flags

We can also add other flags to the compiler to give it special instructs or extra information, and we will return to this later. A common one to include is `-Wall` (for "Warning all") that tells the compiler to give us warnings if it sees things it is skeptical about. So we would do
```
c++ hello_world.cpp -o hello -Wall
```
Note that *warnings* in this context is not the same as an *error*. An error causes our compilation to terminate, while with warnings, we do get an executable, but the compiler believes we are doing something that is inefficient or error prone. Ironically, `-Wall` doesn't give all possible warnings, so you could add `-Wextra` to get some more warnings (and other `-W` flags, there are quite a variety of options for specific purposes).

If you haven't, this is a good time to go through and make your `hello_world.cpp` source code, compile it into an executable, and then run the executable.

## Static vs Dynamic Typing

One of the major differences in C++ and Python that you will have to learn right away, is that C++ is *statically typed*, while Python is *dynamically typed*.

This means that we have to specifically declare what types our variables are when we define them in C++, and a given variable cannot change it's type. In Python however, we just declare our variables, and let the interpreter figure out implicitly what types the variable is, and a given variable can change types without any problems.

For example

````{tab} C++
```c++
string city = "Oslo";
int year = 2018;
double temp = 42.3;
```
````
````{tab} Python
```python
city = "Oslo"
year = 2018
temp = 42.3
```
````

Note both that we are explicit in our typing in C++. Recall also that we always need semicolons at the end of a statement.

The common primitive data types in C++ are:

| C++ Type        | Description           | Size in memory |
| --------------- | --------------------- | -------------- |
| `bool`          | Boolean               | 1 byte         |
| `short`         | 16-bit integer        | 2 bytes        |
| `int`           | 32-bit integer        | 4 bytes        |
| `long long int` | 64-bit integer        | 8 bytes        |
| `float`         | 32-bit floating-point | 4 bytes        |
| `double`        | 64-bit floating-point | 8 bytes        |
| `char`          | single character      | 1 byte         |
| `string`        | character sequence    | 1 byte         |

Note that these types are different from the ones you are used to in Python. In C++ for example, the type `float` has 32-bits precision, while a `double` has twice that (64-bit). As a consequence a `double` value takes up twice as much memory as a `float` value. Notice that 64 bits is the same as 6 bytes ($2^6 = 64$).

For scientific applications, we want the extra precisions of doubles, and will usually only use doubles, and skip the floats altogether. Note that the `float` type in Python is actually a double, as it has 64-bits precision.

Similarly, the integer type in C++, has a fixed precision of 32 bits, which means it has a built in lower and higher limit to what number it can contain. This is again different from the `int` type in Python, which has no such limit, and can grow larger and larger without any problem.

Note also that the `string` type in C++ has to be imported from the standard library header by the same name:
```C++
#include <string>
using namespace std;
```

Since a single character has size of 1 byte = 8 bits it means that it can hold $2^8 = 256$ different characters. A 32-bit integer can hold $2^32 = 4294967296$ different values, and since we include the negative values as well, the typical range of a 32-bit integer is between -2147483648 and +2147483647 (with zero included). This means that if you want to work with larger integers than this, then you need to use a `long` which has a range of $[-2^{63}, 2^{63})$.

## Functions and Types

It is not just when we are defining variables we need to be explicit in our typing, but also when defining functions. For each function we define, we have to explicitly state what types the input to the function are, and what types the outputs are.

Say for example we are making a Celsius to Fahrenheit conversion function, it could be done as follows:
```C++
double F2C(double F)
{
    return 5 * (F - 32) / 9;
}
```
Here, we write `double F2C(...)` to state that we are creating a function `F2C` that will return a double, and we also specify `(double F)` to state that it takes a double as an argument. The contents of the function itself is put inside curly braces. To return we use the `return` keyword.

Similarly, if we want to create a function `is_prime`, that takes in an integer, and returns true or false, then we would write
```C++
bool is_prime(int n)
{
    ...
}
```
This statement is called the *signature* of the function, and it tells us quite a bit about how the function works. The combination of a good function name and typed input and output should give the reader a good understanding of what the function does.

What do we do if we want to make a function that returns nothing? Then we define it as a `void`, which simply means it doesn't return anything:
```C++
void greet(string name)
{
    cout << "Hello there " << name << "!" << endl;
}
```

***

A full program that defines and uses the `F2C` function can look as follows:
```C++
#include <iostream>

using namespace std;

double F2C(double F)
{
    return 5 * (F - 32) / 9;
}

int main()
{
    double temp = 110.;
    cout << temp << " F" << endl;
    cout << F2C(temp) << " C" << endl;
    return 0;
}
```
Here we first define our `F2C` function, and then define our `main` function.


## Loops and if-tests

Let's turn to how to create loops in C++. The most common loops in Python are the loops using *range*. Let us look at a simple example written out in both languages:

````{tab} C++
```c++
for (int i = 0; i < 10; i++)
{
    cout << i * i << endl;
}
```
````
````{tab} Python
```python
for i in range(10):
    print(i * i)
```
````


In both languages, we use the `for`-keyword to define a for-loop. However, we define the loop itself quite differently. In C++ we first state where the loop should start (`i=0`), how long it should keep going (`i<10`) and how it should increment, the step (`i++`). Note that `i++` means an increment, similar to `i += 1`. With this syntax, the for-loop is defined with the same logic as a while-loop. Note also that we have to explicitly type the counting variable `i`, by writing `int i=0` for our start of the loop.

```{note}
You might see the use of `++i` instead of `i++`. There is a small difference between these two notations that are explained in more details [here](https://stackoverflow.com/questions/24853/what-is-the-difference-between-i-and-i).
```

Like for functions, the contents of the loop itself is put inside curly braces.

### If-tests

If-tests in C++ look exactly like in Python, except for some small differences in what symbols are used:

````{tab} C++
```c++
if (i < 100)
{
    i *= 2;
}
```
````
````{tab} Python
```python
if i < 100:
    i *= 2
```
````

Note that we: (1) add parentheses around the condition itself, and (2) use curly braces to define the contents of the test (the scope), instead of the colon seen in Python. The indentation is similar in both cases, more on this later.

## Boolean Operators in C++

While the if-test themselves are very similar to Python, the conditions themselves might be a bit different. For one, in Python, you are used to using the boolean operators `and`/`or`/`not`, while in C++ it is more common to write `&&`/`||`/`!` for these respectively. However, the keywords are defined in C++, so use the ones you prefer.

However, be careful when combining conditions in C++, in Python we can use nifty shortcuts like `if lower < x < upper`, but in C++, such an expression will be evaluated as `(lower < x) < upper`, with the first condition evaluating to 0 for false and 1 for true, and so for example, you might think the following test would fail:
```C++
if (3 < 10 < 7)
{
    ...
}
```
but it actually passes! Because "(3 < 10) < 7" is the same as "1 < 7", which is true.


### Example: `is_prime`

We now combine a for-loop and an if-test to create the `is_prime` function outlined earlier as online a signature.

```C++
bool is_prime(int n)
{
    if (n == 1)
    {
        return false;
    }

    for (int d = 2; d < n; d++)
    {
        if (n % d == 0)
        {
            return false;
        }
    }
    return true;
}
```
Here, we first check the special case of $n=1$, then we see if any of the numbers in the interval $[2, n)$ cleanly divides the candidate, which we do with the modulo operator. Depending on the input, we return either `true` or `false`. Note that these are specified with all lower capitalization.

To test the function, we make a loop checking the numbers 1 through 11:
```C++
int main()
{
    for (int i = 1; i <= 11; i++)
    {
        if (is_prime(i))
        {
            cout << i << " is prime" << endl;
        }
        else
        {
            cout << i << " is not prime" << endl;
        }
    }
}
```

## A note on bracket style

From Python, you are used to whitespace not mattering much, with the exception of *newline* characters and *leading* whitespace, i.e., indentation. In C++, however, whitespace matters even less, and this includes newline characters and indentation. As we always include semicolons at the end of statements in C++, we don't need to use newlines between different statements, and because we use curly braces to define scopes, we do not need to use indentation.

However, while newlines and indentation are not strictly necessary for the code to function, we should use them to increase structure and help readability. But if newlines and indentation doesn't impact the behavior of code, it means we can choose to do these things in different ways, and so it because a style choice. In C and C++ there are many different style choices of indentation, newlines and bracketing, and there is a large [Wikipedia article on it](https://en.wikipedia.org/wiki/Indentation_style) you can read if you are curious.

Without going to much into detail, one major point of contention is whether to place the *opening* brace of a function definition or a control structure on the same line as the control statement, or on a separate line immediately below it
```C++
int main()
{
    for (int i = 0; i < 10; i++)
    {
        ...
    }
}
```
or
```C++
int main()
{
    for (int i = 0; i < 10; i++)
    {
        ...
    }
}
```
When you are looking at C++ code in books or online, you will see both styles used, it comes down to preference. As always, regardless of what style you want to follow, the most important thing is to be consistent in your style. For example if you prefer the first style, which is called the *"One True Brace Style"* (OTBS/1TBS), then you should stick to that.

```{admonition} Pro tip: Use a formatting tool
:class: tip

To avoid thinking too much about the bracket style (or coding style in general) a good tip is to use a formatting tool. For python we have seen `black` and `autopep8`. A similar tool exist for `C++` and the most popular one is probably `clang-format` which comes already installed with `gcc` as well as `clang`. You can format you file using the command `clang-format hello.cpp -i`, or if you are using VSCode you can make it format on save if you add `"editor.formatOnSave": true` in your settings. You can also read more [here](https://stackoverflow.com/questions/45823734/visual-studio-code-formatting-for) on the different styles.
```


## Single-statement loops and tests

Another important thing to note about braces in C++ is that in a control structure with a single statement, you can opt to skip the braces altogether. For example:
```C++
if (is_prime(i))
{
    cout << i << " is prime" << endl;
}
else
{
    cout << i << " is prime" << endl;
}
```
could just as well be written
```C++
if (is_prime(i))
    cout << i << " is prime" << endl;
else
    cout << i << " is prime" << endl;
```
Some prefer to write the latter, because it looks nicer without the brackets. The OTB style states that this shouldn't be done however, because it can easily lead to errors.

If you always use braces, even for single statements, you can always go back and add more statements later, and things will work just as well. If you omit the braces however, when you add the second statement, it actually goes *outside* the control structure. This means the first style is a lot safer and extendable than the second. We therefore recommend that you *always use your braces*, it will save you from bugs that can potentially cost you a lot of frustration and time down the road.

## While-loops

While-loops in C++ also look a lot like in Python. Just like the if-tests, we put parenthesis around the condition and define the scope using curly braces:

````{tab} C++
```c++
int n = 1;
while (n < 10)
{
    n *= 2;
}
```
````
````{tab} Python
```python
n = 1
while n < 10:
    n *= 2
```
````

As we can see, there is close to no difference.


## Vectors

From Python, you are used to using the list datatype. This datatype is not built into C++, but there is a similar datatype, called a vector, available from one of the standard libraries. You include it using:
```C++
#include <vector>
```
Note that there is also a datatype called a *list* in the C++ standard library, we will return to why we say the vectors are equivalent when we discuss data structures.

One major difference between Python lists and vector objects in C++ is that vector objects must contain elements of the same type. So when we define a vector object, we must not only declare that our variable is of type vector, but we must also define the type of the *elements*. This is done as follows:
```C++
vector<int> primes;
```
Here, we define a variable `primes`, that is of type `vector` with contents of type `int`. The use of `<int>` is called *templating*.

Note that `primes` vector will start out as an empty vector, we do not need to specify it as being empty, this is implied. If however, we wanted to initialize it with given elements, we could do this as follows:
```C++
std::vector<int> primes{2, 3, 5, 7, 11};
```
where you can drop `std::` if you have declared `using namespace std;`.
Note that we do not use any `=` for assignment here, this is a minor detail we will return to later, when we turn to OOP in C++.

### Interacting with C++ vectors

As stated, the C++ vector objects behaves a lot like a Python lists, and so we can access and change specific elements using square bracket indexing. C++ also starts indexing at 0, so `primes[3]` refers to the integer `7` in the list of primes initialized above. However, note that you cannot index with fancy slicing as in Python.

To append elements to a vector, use the method `.push_back(n)`, which adds elements to the end of the list. The name comes from "pushing something to the back". To get the number of elements in the vector, use `.size()`. To see other supported methods, see the [reference](http://www.cplusplus.com/reference/vector/vector/).

```{admonition} Pro tip: Install a C++ extension for you editor
:class: tip

Most modern editors and IDEs comes with extensions that can make it easier to see which methods that are available and provide documentation for those method. Personally I use the [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) extension which provides both intellisense and debugging features.
```


In Python, we can easily loop over elements in a list:

```Python
for p in primes:
    ...
```
A similar syntax is possible with vectors:
```C++
for (int p : primes)
{
    ...
}
```
or alternatively you can simply loop over the indices:
```C++
for (int i = 0; i < primes.size(); i++)
{
    // do something with primes[i]
}
```

### Example: Finding primes

Let us look at an example where we define a function that finds the first $n$ primes. To do this, we will use our `is_prime` function, which we defined earlier in this lecture.

First, we need to define the signature of our function. It should return a vector of integers, and take in the number of primes to find, so we write
```C++
vector<int> find_primes(int nr)
{
    ...
}
```

Now, inside the function, we first need to define an empty vector, where we can push new primes as we find them. We can then use a while-loop to check `primes.size() < nr` until we have found enough primes.

The whole function becomes:
```C++
vector<int> find_primes(int nr)
{
    vector<int> primes;
    int n = 1;

    while (primes.size() < nr)
    {
        if (is_prime(n))
        {
            primes.push_back(n);
        }
        n++;
    }
    return primes;
}
```
To test our function, we add the following to the main function:
```C++
int main()
{
    vector<int> primes = find_primes(100);

    for (int p : primes)
    {
        cout << p << endl;
    }

    return 0;
}
```
Compiling the program and running the executable will now write out the first 100 primes.


## Strings

We now turn to string objects. C has a primitive data type called `char`, that is a single character. Strings are sequences of characters, and so to make strings in C, one creates arrays of characters. We will cover arrays in the next lecture, but for now, let us simply say they are sequences, like a tuple. Thus, C has no primitive string datatype, it instead uses the `char[]` datatype (the square brackets denote an array).

In C++ however, a string datatype has been added in the standard library, and is the recommended way to work with strings. Note that the datatype is called `string`, and not `str` as in Python.


To use strings we must include the header from the standard library
```C++
#include <string>

using namespace std;
```
If we do not declare we are using the std namespace, then we can use strings by writing `std::string`.

See the full reference on strings to see what functionality the string class adds:
* http://www.cplusplus.com/reference/string/string/


## Type inference

Consider the following lines of code

```C++
int x = 1;
int y = x + 1;
```
It is clear that both `x` and `y` are integers, however we can also deduce that `y` has to be an integer because `x` is. Automatic detection of data types is called *type inference* and since `C++11` standard we can instead write

```C++
int x = 1;
auto y = x + 1;
```
When using `auto`, C++ will figure out which type to use. This is very convenient when you are working with complicated types, however it can make your code less readable.
An example where I would recommend using `auto` is places where you don't really care about the type, for example if you are printing out the elements in a vector
```c++
vector<int> v{1, 2, 3};
for (auto x : v)
{
    cout << x << " ";
}
cout << endl;
```

## Comments

Comments are often useful to add in places where you need to provide some extra information. In python we use the `#` in front of the line with comments while in C++ we use `//`.

````{tab} C++
```c++
// Gravity in units m/s^2
double g = 9.81;
```
````
````{tab} Python
```python
# Gravity in units m/s^2
g = 9.81
```
````

In C++ you can also have multiline comments beginning with `/*` and ending with `*/`.
```c++
/* This is a
multiline
comment */
```


## Standard input and output

We have already seen that we can write output to the console using `cout` from the `iostream` library. The `iostream` library enable us to print information to the console as well as handling input from the console using the notion of *streams*. You can think of a stream as a flow of data and the angle brackets `<<` and `>>` as operators acting on that stream. We use the *output operator* (`<<`) with *consol output* (`cout`) and the *input operator* (`>>`) with *consol input* (`cin`). Here is an example using `cin`.
```c++
#include <iostream>
using namespace std;

int main()
{
    int number;
    cout << "Input a number: ";
    cin >> number;
    cout << "You entered " << number << endl;
    return 0;
}
```

### File streams
Working with files is almost the same as working with the console. The following program will write a sequence of the first 10 digits to a file called `output.txt`.
```c++
#include <fstream>
using namespace std;

int main()
{
    ofstream ofs{"output.txt"};
    for (int i = 0; i < 10; i++)
    {
        ofs << i << endl;
    }

    return 0;
}
```
We see that we need to include the `fstream` library which contains the functionality for working with files. In the line `ofstream ofs{"output.txt"};` we create a file stream for writing to a file called `output.txt`. If the file does not exist it will be created, and if it already exist it will be overwritten. Next we use the `ofs` object that we created in a similar manner as we do with `cout`.
A lot of things can go wrong when working with files. It is therefore good practice to check if the file has been open correctly. The following program will throw a runtime error because it tries to write to a file in a folder that does not exist.
```c++

#include <fstream>
using namespace std;

int main()
{
    ofstream ofs{"fake_folder/output.txt"};
    if (!ofs)
    {
        throw runtime_error("Unable to open file");
    }

    for (int i = 0; i < 10; i++)
    {
        ofs << i << endl;
    }

    return 0;
}
```
Similar as with `iostream` it is possible to read from a file using `fstream`. The following program writes to a file and then reads from it and prints the output to the console
```c++

#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    ofstream ofs{"output.txt"};
    if (!ofs)
    {
        throw runtime_error("Unable to open file");
    }

    for (int i = 0; i < 10; i++)
    {
        ofs << i << endl;
    }

    ifstream ifs{"output.txt"};
    int x;
    while (!ifs.eof())
    {
        ifs >> x;
        cout << x << "\n";
    }
    return 0;
}
```
Note that `ifs.eof()` returns `true` when you have reached the end of the file.
