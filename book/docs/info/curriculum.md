# Curriculum

The lecture notes and the four mandatory projects are the curriculum of IN1910.

## Curriculum and Teaching Materials

We do not operate with a single book in IN1910, as we are covering many different topics that are not well covered by any existing textbook. The curriculum is therefore defined by what is covered in the lectures. For each lecture, there will be accompanying lecture notes covering that week's material. If you are not attending the lectures, you should read/work through the lecture notes. If you do attend lectures, it might be a good idea to skim through the lecture notes before any given lecture, or go through them at your own pace after a given lesson.

In addition to the lecture notes, we will give references to external teaching materials that you can use to better learn the materials. These are meant as additional information to those who want it, or alternatives to those who might not like the style or tone of the lecture notes. Note that these secondary materials are just recommendations, and you can choose which of them to use or cover yourself. Most of the materials we recommend will be open source materials freely available online.

(info-python-books)=
### Python

As a good reference on Python for scientific programming, we recommend *A Primer on Scientific Programming with Python, Fifth Edition av Hans Petter Langtangen*, which many of you taking the course probably already have already. If you do not, you can also find an electronic version [here (available for UiO students)](https://link.springer.com/book/10.1007%2F978-3-662-49887-3)

```{figure} ../figures/langtangen.jpg
---
width: 150px
name: langtangen
alt: langtangen
---
[A Primer on Scientific Programming with Python](https://link.springer.com/book/10.1007%2F978-3-662-49887-3)
```

IN1900 is using a new book this semester called [*Introduction to Scientific Programming with Python*](https://link.springer.com/book/10.1007%2F978-3-030-50356-7) written by Joakim Sundnes which is a free e-book that can also by used in addition.

```{figure} ../figures/sundnes.jpg
---
width: 150px
name: sundnes
alt: sundnes
---
[Introduction to Scientific Programming with Python](https://link.springer.com/book/10.1007%2F978-3-030-50356-7)
```

Finally the book *Programming for Computations - Python
A Gentle Introduction to Numerical Simulations with Python 3.6* by Svein Linge and Hans Petter Langtangen is another good alternative which is also [freely available as an e-book](https://library.oapen.org/handle/20.500.12657/23103).

```{figure} ../figures/linge.jpg
---
width: 150px
name: linge
alt: linge
---
[Programming for Computations - Python
A Gentle Introduction to Numerical Simulations with Python 3.6](https://library.oapen.org/handle/20.500.12657/23103)
```

### C++

As with python we do not follow any textbook on C++. However, if you want a textbook, then *Modern C++ for Absolute Beginners* by Slobodan Dmitrović is a good choice. This book is also [available for UiO students](https://link.springer.com/book/10.1007/978-1-4842-6047-0)

```{figure} ../figures/modern-c-for-absolute-beginners.jpg
---
width: 150px
name: modern-c-for-absolute-beginners
alt: modern-c-for-absolute-beginners
---
[Modern C++ for Absolute Beginners](https://link.springer.com/book/10.1007/978-1-4842-6047-0)
```

## Accessing Teaching Materials

All teaching materials are shared on a git repository on the UiO Github server. You will need to log in with your UiO username and password. You will soon learn how to use Git repositories.
The teaching material are published using something called GitHub pages which you can access go going to the following link:

* https://pages.github.uio.no/IN1910/IN1910_H22

These lecture notes are generated from Jupyter notebooks which you can find here

* [https://github.uio.no/IN1910/IN1910](https://github.uio.no/IN1910/IN1910).

These notebooks are contain working code examples and we encourage you to try changed the code in order to see how this will alter the output. You can download these notebooks through git to your own machine and run them through Jupyter, or you can use the UiO Jupyterhub server. Here you will also log in with your UiO username and password, and you can then navigate to IN1910. When you run Jupyter notebooks through Jupyterhub, you are running things on a UiO server, so this is a good solution for reading materials if you are on a different computer than your regular computer with everything installed.
* [https://jupyterhub.uio.no/](https://jupyterhub.uio.no/)

## Alternative resources

In addition to the lecture notes and the above mentioned books, there are also a lot of good resources online, for example for python we have

- <https://www.pythonlikeyoumeanit.com>
- <https://realpython.com>
- <https://www.learnpython.org>
- <https://automatetheboringstuff.com>
- <https://jakevdp.github.io/WhirlwindTourOfPython/index.html>
- <https://inventwithpython.com/beyond/>
- <https://object-oriented-python.github.io/index.html>

On YouTube I would also recommend watching a [tutorial series on how to set up a python development environment](https://www.youtube.com/playlist?list=PL-osiE80TeTt66h8cVpmbayBKlMTuS55y), and also the [Python beginner tutorial](https://www.youtube.com/playlist?list=PL-osiE80TeTskrapNbzXhwoFUiLCjGgY7) by the same author.

For C++ some online resources are

- <https://hackingcpp.com/cpp/beginners_guide.html>
- <https://isocpp.org/wiki/faq>
- <https://www.learncpp.com>
- <https://cs.berea.edu//cpp4python/index.html>
- <https://docs.microsoft.com/en-us/cpp/cpp/cpp-language-reference>
- <https://www.cplusplus.com/doc/tutorial/>

### Further material for algorithms and data structures

At UiO, the course [IN2010 – Algorithms and Data Structures](https://www.uio.no/studier/emner/matnat/ifi/IN2010/index-eng.html) (previously INF2220) focuses more in-depth on the topic of data structures and algorithms. The course comes highly recommended for anyone who wants to become a better programmer, and it is essentially a prerequisite if one's goal is to go further into computer science.

There are also hundreds of books on this subject. Not only are there many to choose from, but there are several dedicated to each programming language one might want to use. We recommend the book used in IN2010, [*Algorithm Design and Application* by Goodrich and Tamassia](https://www.wiley.com/en-us/Algorithm+Design+and+Applications-p-9781118335918), as that is probably the best choice if the reader wants to get a dedicated book and might be taking IN2010 in the future.

```{figure} ../figures/goodrich_and_tamissa.jpg
---
width: 175px
name: goodrich-and-tamissa
---
Book used by IN2010, [*Algorithm Design and Application* by Goodrich and Tamassia](https://www.wiley.com/en-us/Algorithm+Design+and+Applications-p-9781118335918).
```

Another excellent resource to use is the teaching materials for the [MIT course 6.006 *Introduction to Algorithms*](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/). The course materials are openly available through Open CourseWare, with recorded video lectures. This course covers the theory behind many data structures and algorithms, so it works well with any programming language but mostly uses Python for code examples. Note that 6.006 goes into many topics we do not cover, but they also have lectures that cover what we do in IN1910.
