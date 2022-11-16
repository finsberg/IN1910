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

# C++ tips and tricks

While it is certainly possible to write bug-free C++ in a pure text editor without any tool to guide you, most professional developers depend heavily on tools to help them write, compile and debug the code they are writing. In this document we will go through a few tips and tricks that will help you when developing C++ code.

## C++ extension for your editor
Most of the modern editors, or integrated development environments (IDEs) comes the possibility of using extensions. For example in Visual Studio Code you have the [C++ extension](https://code.visualstudio.com/docs/cpp/introvideos-cpp) that will give you tab completion, documentation and much more. Spending some time on learning how to use these extension will definitely pay off in the end.

## Debugging
Very often your editor or compiler will point out mistakes you have made in the code, but sometimes the code compiles fine even though it contains bugs. For example if you get the following cryptic message when you try to run your program, you know there is something wrong.
```
Segmentation fault (core dumped)
```
It is good practice to compile and run your code often so that you have a better feeling on when the bug was introduced. However, sometimes it can be tricky to know what is causing your program to fail, and in this case it might be helpful to use a debugger.

### Debugging with `gdb` or `lldb`
The standard debugger for `GNU` is called `gdb`, while the debugger for `clang` is called `lldb`. The interface of the two are similar and we will therefore show the commands using `gdb`, but if you are working on a Mac and use `clang` then you can try swapping `gdb` with `lldb` and it should work.

Using a debugger is an alternative to putting print statements all over your code. A debugger lets you inspect the code in more detail and help you track down the cause of failure.

Now we will try debugging the following program which we will call `nullptr_deref.cpp`
```c++
#include <iostream>

void my_function()
{
    double *a = nullptr;
    double b = *a;
    std::cout << b << std::endl;
}

int main()
{
    my_function() return 0;
}
```
This code compiles fine using the command
```
c++ nullptr_deref.cpp -o nullptr_deref
```
but when we run it we get the following message
```
$ ./nullptr_deref
Segmentation fault (core dumped)
```
Now we will try to run the program using the debugger. Before using the debugger we should compile our program with debugging information. We can do this by sending in the `-g` flag to the compiler
```
c++ nullptr_deref.cpp -o nullptr_deref -g
```
Now, we can use the debugger by executing the following command `gdb <program>`, where `<program>` is the command to run our program. In our case with would be
```
gbd ./nullptr_deref
```
When you run this it will print a lot of information and throw you into a `gdb` prompt.

```
$ gdb ./nullptr_deref
GNU gdb (GDB) Red Hat Enterprise Linux 8.2-15.el8
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./nullptr_deref...done.
(gdb)
```
You can exit this prompt anytime by hitting `q` and `enter`. To run the debugger, type `run` and hit `enter`. You should then see the following

```
(gdb) run
Starting program: /uio/kant/ifi-ekstern-u00/henrinfi/nullptr_deref
Missing separate debuginfos, use: yum debuginfo-install glibc-2.28-151.el8.x86_64

Program received signal SIGSEGV, Segmentation fault.
0x000000000040081a in my_function () at nullptr_deref.cpp:6
6	  double b = *a;
Missing separate debuginfos, use: yum debuginfo-install libgcc-8.4.1-1.el8.x86_64 libstdc++-8.4.1-1.el8.x86_64
```
The important info that we get from the debugger are the following
```
0x000000000040081a in my_function () at nullptr_deref.cpp:6
6	  double b = *a;
```
It tells us that the error occurred in the function called `my_function`, in the file called `nullptr_deref.cpp` and line 6. An it also displays the relevant line.

You can also print out the values using `p <variable>` where `<variable>` is the variable you want to print. If you want to print out the value of `a`, you could type
```
(gdb) p a
$1 = (double *) 0x0
```
You could also try to print out the value that `a` points to by dereferencing it, but this will print and error message
```
(gdb) p *a
Cannot access memory at address 0x0
```
Another useful command to know is the backtrace command `bt`, which will show you which functions that are called before the error occurred.
```
(gdb) bt
#0  0x000000000040081a in my_function () at nullptr_deref.cpp:6
#1  0x000000000040084b in main () at nullptr_deref.cpp:12
```
In this case we see that the error occurs in line 6 in `nullptr_deref.cpp` in the function `my_function` which is called from the function called `main` at line 12 in the file `nullptr_deref.cpp`.

### Debugging memory leaks with `valgrind`

Memory leaks can be difficult to spot, and often you these bug will go unnoticed until they suddenly become a big problem. Fortunately, there are tools that can help you track down memory leaks. The most popular one is called [`valgrind`](https://valgrind.org). Consider the following program that we call `doomsday.cpp`:
```c++
int main()
{
    for (int i = 0; i < 10; i++)
    {
        int x = i;
        int *y = new int;
    }
    return 0;
}
```
In line 5 we make a heap allocation that is not freed, and thus we have a memory leak. We first compile the program without errors
```
c++ doomsday.cpp -o doomsday -std=c++14
```
Now we can run it through `valgrind` using the following command
```
$ valgrind ./doomsday
```
and it will output the following
```
==2451016== Memcheck, a memory error detector
==2451016== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2451016== Using Valgrind-3.16.0 and LibVEX; rerun with -h for copyright info
==2451016== Command: ./doomsday
==2451016==
==2451016==
==2451016== HEAP SUMMARY:
==2451016==     in use at exit: 40 bytes in 10 blocks
==2451016==   total heap usage: 11 allocs, 1 frees, 72,744 bytes allocated
==2451016==
==2451016== LEAK SUMMARY:
==2451016==    definitely lost: 40 bytes in 10 blocks
==2451016==    indirectly lost: 0 bytes in 0 blocks
==2451016==      possibly lost: 0 bytes in 0 blocks
==2451016==    still reachable: 0 bytes in 0 blocks
==2451016==         suppressed: 0 bytes in 0 blocks
==2451016== Rerun with --leak-check=full to see details of leaked memory
==2451016==
==2451016== For lists of detected and suppressed errors, rerun with: -s
==2451016== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
It tells us that we have 40 bytes in 10 blocks that are definitely lost. In our program, each `int` we create takes up 4 bytes and there are 10 of them (sine the loop runs 10 times) so these are the same bytes that `valgrind` have detected. We can get even more information if we first compile the executable with debugging information (using the `-g` flag)
```
c++ doomsday.cpp -o doomsday -std=c++14 -g
```
Now if we run `valgrind` with the `--leak-check=full` flag
```
$ valgrind --leak-check=full ./doomsday
```
and it will output the following
```
==2452829== Memcheck, a memory error detector
==2452829== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2452829== Using Valgrind-3.16.0 and LibVEX; rerun with -h for copyright info
==2452829== Command: ./doomsday
==2452829==
==2452829==
==2452829== HEAP SUMMARY:
==2452829==     in use at exit: 40 bytes in 10 blocks
==2452829==   total heap usage: 11 allocs, 1 frees, 72,744 bytes allocated
==2452829==
==2452829== 40 bytes in 10 blocks are definitely lost in loss record 1 of 1
==2452829==    at 0x4C35586: operator new(unsigned long) (vg_replace_malloc.c:342)
==2452829==    by 0x40060A: main (doomsday.cpp:5)
==2452829==
==2452829== LEAK SUMMARY:
==2452829==    definitely lost: 40 bytes in 10 blocks
==2452829==    indirectly lost: 0 bytes in 0 blocks
==2452829==      possibly lost: 0 bytes in 0 blocks
==2452829==    still reachable: 0 bytes in 0 blocks
==2452829==         suppressed: 0 bytes in 0 blocks
==2452829==
==2452829== For lists of detected and suppressed errors, rerun with: -s
==2452829== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
and we see that it found the memory leak in `doomsday.cpp:5`, i.e line 5.
If we fix the memory leak, i.e write the following instead
```c++
int main()
{
    for (int i = 0; i < 10; i++)
    {
        int x = i;
        int *y = new int;
        delete y;
    }
    return 0;
}
```
and run it through `valgrind` we now get the following output
```
==2453475== Memcheck, a memory error detector
==2453475== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2453475== Using Valgrind-3.16.0 and LibVEX; rerun with -h for copyright info
==2453475== Command: ./doomsday
==2453475==
==2453475==
==2453475== HEAP SUMMARY:
==2453475==     in use at exit: 0 bytes in 0 blocks
==2453475==   total heap usage: 11 allocs, 11 frees, 72,744 bytes allocated
==2453475==
==2453475== All heap blocks were freed -- no leaks are possible
==2453475==
==2453475== For lists of detected and suppressed errors, rerun with: -s
==2453475== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
(cpp-header-files)=
## Header files and compiling multiple files
So far in the course we have worked only with a single file, but very often you want to structure your code into separate files which makes more sense. For example you might want to separate the code containing the tests from the code containing the actual implementation.

Let us illustrate this with an example.
Say that we have implemented a sorting algorithm in a file called `sort.cpp`, and we wanted to write the tests in a file called `test_sort.cpp`.
Here is an example

```c++
// sort.cpp
#include <vector>
using namespace std;

vector<int> bubble_sort(vector<int> numbers)
{
    int temp;
    bool changed = true;

    while (changed)
    {
        changed = false;
        for (int i = 0; i < numbers.size() - 1; i++)
        {
            if (numbers[i] > numbers[i + 1])
            {
                temp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = temp;
                changed = true;
            }
        }
    }
    return numbers;
}
```
and the testing file:
```c++
// test_sort.cpp
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> original{2, 4, 3, 0, 5, 1};
    vector<int> sorted = bubble_sort(original);
    cout << "Original" << endl;
    for (int e : original)
    {
        cout << e << endl;
    }

    cout << "Sorted" << endl;
    for (int e : sorted)
    {
        cout << e << endl;
    }

    return 0;
}
```
At the moment, this code will not work. The file `test_sort.cpp` does not know about the function called `bubble_sort` so we need to somehow import this into the file.

### Declarations and definitions

In C++, there is a distinction between *declaration* and *definition*. A function declaration specifies the function's signature, i.e its name and the types of its arguments and the return value. The signature of the `bubble_sort` function for example is
```c++
std::vector<int> bubble_sort(std::vector<int>);
```
The return type is `std::vector<int>`, the name is `bubble_sort` and the type of the argument is `std::vector<int>`. Note that we excluded the name of the argument to the function (i.e `numbers`) because it is not important in the signature. This distinction becomes important when working with multiple files.

The definition on the other hand refers to the actual implementation. In order to use function it has to be declared first. We can illustrate this with a single file as well. The following code will not compile
```c++
#include <iostream>
using namespace std;

int main()
{
    print_hello();
}

void print_hello()
{
    cout << "Hello!\n";
}
```
It will instead give you the following error
```
error: use of undeclared identifier 'print_hello'
    print_hello();
    ^
1 error generated.
```
It says that the function `print_hello` is undeclared. We can fix the code by first declaring the function as follows

```c++
#include <iostream>
using namespace std;

void print_hello();

int main()
{
    print_hello();
}

void print_hello()
{
    cout << "Hello!\n";
}
```

### Header files

When working with multiple files we put all the declarations that is needed in something called header files. These files typically ends with `.h` or `.hpp`.

In our case we will create a header file called `sort.hpp` with declaration of `bubble_sort`.
```c++
// sort.hpp
#include <vector>

std::vector<int> bubble_sort(std::vector<int>);
```
Note that we did not add `using namespace std` in the header file. It is considered bad practice to add `using namespace` statements in header files because this will be adopted by all files that include the header files.

We can now include the header file in both `sort.cpp` and `test_sort.cpp` by adding the following line to both files
```c++
#include "sort.hpp"
```
Notice the distinction between including a library from the standard library e.g `iostream` and this file. For the standard library (and any order installed library) you can use the angle brackets e.g `<iostream>`. For files in your working directory like `sort.hpp` you can use quotation marks (`"`) and the relative path to that file. For example if `sort.hpp` where located in a folder called `include`, then you should change your import to
```c++
#include "include/sort.hpp"
```
(cpp-compilation-linked)=
### Compilation and linking

It might be tempting to try to compile `sort.cpp` using the command
```
c++ sort.cpp --std=c++14 -o sort
```
but this will give you an error saying that it is missing a `main` function.

When we compiling multiple files we can still only have one `main` function, and in this case we put this in the file called `test_sort.cpp`.

Before moving along we need to talk about the two steps needed to go from a source file (i.e the code we write in the file ending with a `.cpp`) to an executable file (typically a `.out` file or a `.exe` file). These two steps are called *compilation* and *linking*. Each source file is first compiled to object files and then the object files are linked together to form the executable.


```{figure} ../../figures/compilation_linking.png
---
width: 600px
name: compilation-linking
---
Several source files are compiled individually into object files. These object files are then linked together to form the final executable file.
```

The command
```
c++ sort.cpp --std=c++14 -o sort
```
can actually be split into two step; the compilation step, where we add the `-c` flag and produces an object file called `sort.o` (or `sort.obj` on windows)
```
c++ sort.cpp --std=c++14 -c
```
and the linking step where we create the executable
```
c++ sort.o --std=c++14 -o sort
```
In our case, the compilation step finishes without any errors, but the linking step will throw an error because it cannot find the `main` function, because this is found in `test_sort.cpp`. What we need to do to instead is to compile the `test_sort.cpp` file
```
c++ test_sort.cpp --std=c++14 -c
```
and then link the two files together
```
c++ sort.o test_sort.o --std=c++14 -o sort
```
```{figure} ../../figures/compilation_linking_example.png
---
width: 600px
name: compilation-linking-example
---
Files involved to compile and link our sorting example.
```

Now that we have included `sort.hpp` in `test_sort.cpp` the compiler sees that the function `bubble_sort` function is declared. However, during the compilation step, the compiler does not need to know the definition (or implementation) of `bubble_sort`. It is sufficient that it knows the signature. The definition is needed during the linking step, and since `sort.cpp` also includes `sort.hpp`, the linker will figure out the definition of `bubble_sort` is found in `sort.cpp`.

(makefile)=
## Makefile - managing the compilation and linking

The compilation and linking process can be quite tedious when many files are involved, and typing out all the commands are both time consuming and error prone. Tools like [`GNU make`](https://www.gnu.org/software/make/) can help you automate this process.  `GNU make` is typically already installed if you are using MacOSX or Linux. If you are on Windows, you can consult the [following stack overflow thread](https://stackoverflow.com/questions/32127524/how-to-install-and-use-make-in-windows).

The idea is that you create a file called `Makefile` (with no extension) and inside this you create so called rules which has the following structure
```
target:   dependencies ...
          commands
          ...
```
You can then run each rule by using the command
```
make <target>
```
where `<target>` is the name of the target.

So for example if want to compile `sort.cpp` into an object file (`sort.o`), then the target is `sort.o`, the dependency is `sort.cpp` and the command is `c++ -std=c++14 -c sort.cpp`. Consequently, we can make the following rule
```
sort.o: sort.cpp
	c++ -std=c++14 -c sort.cpp
```
If you add this to your `Makefile`, and save it, you can compile `sort.cpp` into an object file by typing
```
make sort.o
```
Notice also that if your dependencies does not change (in this case `sort.cpp`) then `make` will not run the command. Instead you will see the following message
```
$ make sort.o
make: `sort.o' is up to date.
```

Lets look at a bit more complicated example. Consider the following `Makefile`
```
sort: sort.o test_sort.o
	c++ -std=c++14 sort.o test_sort.o -o sort

sort.o: sort.cpp
	c++ -std=c++14 -c sort.cpp

test_sort.o: test_sort.cpp
	c++ -std=c++14 -c test_sort.cpp

clean:
	rm -f sort *.o
```
Here we have one rule for compiling `sort.cpp` into `sort.o` and one rule for compiling `test_sort.cpp` into `test_sort.o`. We also added a command with the target `clean` which has no dependencies. Running `make clean` will delete all the object files as well as the executable file called `sort`.


```{admonition} Deleting with wildcard *
:class: tip
The syntax `*.o` simply means all files that ends with `.o`. The asterisk (`*`), commonly referred to as the wildcard character, is a placeholder for any text. When executing the command `rm -f *.o` it will therefore delete all files that ends with `.o`. The reason we also provide the `-f` flag here is because the command `rm -f *.o` will raise an error if no files matching the pattern `.o` exists, while if we use the `-f` flag, no error will be shown.
```

The most complicated rule here is the rule on the top with target `sort`. It has two dependencies, `sort.o` and `test_sort.o`. When executing `make sort` it will first run the command for `sort.o` then run the command for `test_sort.o` and finally run the command for `sort`
```
$ make sort
c++ -std=c++14 -c sort.cpp
c++ -std=c++14 -c test_sort.cpp
c++ -std=c++14 sort.o test_sort.o -o sort
```
```{admonition} Running make without a target
:class: tip
If you run `make` without a target, i.e only `make` it will execute the first rule it finds. Since we placed `sort` at the very top, this is the rule that will be run.
```

## CMake - a modern version of Makefile

Even though `Makefile` definitely makes the process of compiling and linking easier, modern C++ projects often contains many files and many dependencies that can be difficult to compile. This leads us to a modern version of `make` called [CMake](https://cmake.org).

CMake allows you to define how to compile your program at a higher abstraction level and therefore it works very well with different compilers and different operating systems. You can install CMake from [cmake.org](https://cmake.org/download/) or [using conda](https://anaconda.org/anaconda/cmake).

Instead of a file called `Makefile` you now write a file called `CMakeLists.txt`. Let us add the following content to it
```
project(sorting_project
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)

add_executable(sort
    sort.cpp
    test_sort.cpp
)
```
First lines provide a name for the project and which programming languages that are used. Next line set the `-std=c++14` flag but at a higher abstraction level. If you are using a compiler which set the C++ standard differently then using the flag `-std=c++14`, CMake will sort that out for us. The final lines specifies the name of the executable and lists the relevant source files.

To build the program using `CMake` it is good practice to first create a folder called build and change directory to it
```
mkdir build
cd build
```
Now we run the `cmake` command and provide the relative path to the location of the file `CMakeLists.txt`. Since this is now one level up, the relative path is `..`
```
$ cmake ..
-- The CXX compiler identification is AppleClang 12.0.0.12000032
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/henriknf/local/src/IN1910_H21/book/docs/lectures/cpp/build
```
We now see that CMake finds the C++ compiler and generates some files for us. You can see this if have a look in the `build` directory
```
$ ls
CMakeCache.txt      CMakeFiles          Makefile            cmake_install.cmake
```
We also see that CMake created a `Makefile`, which we will use to build the project. Executing `make` will create the executable
```
$ make
[ 33%] Building CXX object CMakeFiles/sort.dir/sort.cpp.o
[ 66%] Building CXX object CMakeFiles/sort.dir/test_sort.cpp.o
[100%] Linking CXX executable sort
[100%] Built target sort
```
And we now see the executable appearing in the same directory
```
$ ls
CMakeCache.txt      CMakeFiles          Makefile            cmake_install.cmake sort
```

```{admonition} CMake GUI for larger project
:class: tip
For large project you might want to specify additional settings when configuring cmake, for example where you want to install the project. You can do this using `ccmake` (with an extra `c`) which will open an interactive widows where you can specify additional settings.
```

## Formatting your code with `clang-format`
Just like python has the formatting tool [`black`](https://github.com/psf/black), C++ has a tool called `clang-format`. `clang-format` comes installed with `clang` as well as with `gcc`.

To run `clang-format` you need to point at the file you want to format as add the `-i` to apply the changes to the file. For example

```
clang-format -i sort.cpp
```
or
```
clang-format -i *.cpp
```
to format all source files.
You can also specify which style you want to use by passing the flag `--style`. For example if you want to use the `llvm` style you can do
```
clang-format -i --style=llvm *.cpp
```

As mentioned before, you can choose which style you want. What is important is that you are *consistent*. Using a formatter is a great way to achieve consistency.

```{admonition} Run a formatter when saving
:class: tip
You always want your code to look nice and have a consistent code style. It is therefore a good tip to simply let your editor format your code when saving. In Visual Studio Code you can do this by setting the [`formatOnSave` option to true](https://code.visualstudio.com/updates/v1_6#_format-on-save).
```

## Documentation with Doxygen

(cpp-documentation)=
### Writing documentation
In python we write docstrings in order to document our code. In C++ it is common to write multiline comments right above the function definition.

For example in the `bubble_sort` function we could write something like this
```c++
/**
 * Sort a vector using the bubble sort algorithm
 * Return a new vector with a arguments sorted
 *
 * @param numbers The vector to be sorted
 * @return A sorted vector
 **/
vector<int> bubble_sort(vector<int> numbers)
{
    int temp;
    bool changed = true;

    while (changed)
    {
        changed = false;
        for (int i = 0; i < numbers.size() - 1; i++)
        {
            if (numbers[i] > numbers[i + 1])
            {
                temp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = temp;
                changed = true;
            }
        }
    }
    return numbers;
}
```
Note that we start with `/**` and end with `**/` and at each line in between we add an asterisk, `*`. In the first lines we provide a description of the function, e.g *Sort a vector using the bubble sort algorithm. Return a new vector with a arguments sorted*. Then we specify the input parameters by first using `@param` followed by the name of the parameter name (in this case `numbers`), and then finally a description of than input parameter. If you have more input parameters you will write these one separate lines. Finally we specify what the function returns using the `@return` syntax.

### Generating documentation with Doxygen
[Doxygen](https://www.doxygen.nl/index.html) is a tool to generate documentation that can be distributed to user of the software, either though the web using HTML or in PDF format. It is similar to [Sphinx](https://www.sphinx-doc.org/en/master/) but applies to more programming languages (Sphinx is used for Python documentation).

Once installed you can run the following command in the location where you have your source files
```
$ doxygen -g

Configuration file 'Doxyfile' created.

Now edit the configuration file and enter

  doxygen

to generate the documentation for your project
```
This will create a file called `Doxyfile` that can be used to configure the documentation. There is a lot of options here, and in this example I will change the following default settings:
```
PROJECT_NAME = "Sorting project"
EXTRACT_ALL = YES
HAVE_DOT = YES
OUTPUT_DIRECTORY = docs
```

The `PROJECT_NAME` just specifies the name of the project, which in this case we will name "Sorting project". The `EXTRACT_ALL` configuration will create documentation for all files even though it cannot find any documentation. This is useful if only parts of your code is documented. We also set `HAVE_DOT` to `YES`. When setting this to `YES` doxygen will create a dependency graphs that shows how your files are related. However, it also requires another package called [Graphviz](http://www.graphviz.org/). Finally we set the `OUTPUT_DIRECTORY` to `docs` which means that the files that are generated from doxygen wil be put in a new folder called `docs`.

Now we can run `doxygen` by executing the command
```
doxygen Doxyfile
```
and you will see that it generates two folders inside the `docs` folder
```
docs
├── html
└── latex
```
If you open `docs/html/index.html` you can have look at the generated documentation.

(cpp-testing)=
## Testing

During the beginning of the course we focused a lot on unit testing and test driven development in Python. When moving on the C++, testing is still very important but for the sake of time, we will not spend too much time on this. C++ is a statically typed language, meaning that the compiler will check that the functions we use are called with the correct type, and this is in itself as very good test.

However, for the sake of completeness we will go through how you can write a simple test in C++ using assert statements, similar to how you would do it in Python. Here is a simple example where we implement a method called `add` and writes two tests for it

```c++
#include <cassert>
#include <cmath>
#include <iostream>
using namespace std;

const double tol = 1e-12;

double add(double x, double y)
{
    return x + y;
}

int add(int x, int y)
{
    return x + y;
}

void test_add_double()
{
    auto expected = 0.3;
    auto result = add(0.1, 0.2);
    assert(abs(expected - result) < tol);
}

void test_add_int()
{
    auto expected = 3;
    auto result = add(1, 2);
    assert(expected == result);
}

int main()
{
    test_add_double();
    test_add_int();
    return 0;
}
```
To use the `assert` function we need to include the header file called `cassert`. Here we also include the `cmath` header in order to use the `abs` function.
