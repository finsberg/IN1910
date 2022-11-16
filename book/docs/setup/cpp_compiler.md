# Installing a C++ compiler

## C++ compilers
There are two major open-source compilers for C++
* GNU Compiler Collection (GCC)
* Clang

Both of these compilers can be used on Mac and Linux. macOS uses Clang as the default compiler, while most Linux distributions use GCC.

For Windows users, we recommend running Ubuntu under Windows Subsystem for Linux (WSL) or using MinGW.

## Using Visual Studio Code
A very good alternative that can be used on all platforms is to use Visual Studio Code with the native C/C++ extension. Please consult the [following link](https://code.visualstudio.com/docs/languages/cpp) for more info on how to set this up. Here they will also guide you through how to [install a compiler](https://code.visualstudio.com/docs/languages/cpp#_install-a-compiler)

## Linux
All major Linux distributions offer packages for a C++ compiler. To see if you already have a C++ compiler installed, you can try running the following command from a terminal
```
c++ --version
```

On Ubuntu and Debian Linux, GCC can be installed with
```
sudo apt install g++
```

On Fedora, RHEL, and CentOS, GCC can be installed with
```
sudo dnf install gcc-c++
```

## macOS
Install Xcode Command Line Tools with the following command
```
$ xcode-select --install
```
Afterwards, we can check what version was installed
```
$ c++ --version
Apple clang version 11.0.0 (clang-1100.0.33.17)
Target: x86_64-apple-darwin19.6.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```

`c++` will conventionally point to the system compiler, which is Apple Clang in the case of macOS. By closer inspection we see that `/usr/bin/c++` is indeed a symlink (symbolic link) to `/usr/bin/clang++`.
```
$ which c++
/usr/bin/c++
$ ls -l /usr/bin/c++
lrwxr-xr-x 1 root wheel 7 Dec 23  2019 /usr/bin/c++ -> clang++
```
Note that Xcode Command Line Tools also installs `/usr/bin/g++`, which is just a wrapper around Clang, and not actually GCC.

## Windows
Visual Studio Code has an extension that makes it easy to work with C++ code in an Ubuntu environment running under Windows Subsystem for Linux (WSL). Please refer to the guide at https://code.visualstudio.com/docs/remote/wsl-tutorial

We recommend that you install the app for Ubuntu 20.04.

You can also check out the [following guide](https://code.visualstudio.com/docs/languages/cpp#_example-install-mingwx64) for how to set up MinGW.

## Testing the compiler
In order to test that the compiler, you can put the following program into a file called `hello.cpp`.
```cpp
#include <iostream>

int main()
{
    std::cout << "Hello" << std::endl;
    return 0;
}
```

Then compile the program with
```
$ c++ hello.cpp -o hello
```
In this case, no output means nothing went wrong, so you should see a new file in the directory called `hello`. (The `-o` flag in the previous command specifies the output file)

Now we can run the program, and it should output "Hello".
```
$ ./hello
Hello
```
