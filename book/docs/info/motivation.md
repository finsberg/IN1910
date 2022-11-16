# The motivation behind IN1910

The paper [*Best Practices for Scientific Computing*](http://journals.plos.org/plosbiology/article?id=10.1371/journal.pbio.1001745) by Wilson, et al, discusses the need for better practices in the field of scientific computing. They quote recent studies that show scientists typically use 30% or more of their time developing software, but that 90% or more are primarily self-taught. As a result, most are not properly trained in the use of good tools and practices.

A movement called [*Software Carpentry*](https://software-carpentry.org/) is trying to remedy the situation by giving workshops and sharing resources for training researchers in computing and programming. As the name implies, the goal is to give researchers a set of useful *tools* and the competence and confidence to use them properly.

```{figure} ../figures/software_carpentry.png
---
width: 200px
name: software_carpentry
alt: software_carpentry
---
```

IN1910 aims to do the same thing. We do not just want to teach you how to code up scientific applications, but we want to give you a set of important tools and practices to program in an efficient manner that leads to more reliable and maintainable code. We will therefore spend time during the course to cover tools such as version control and focus on testing and documenting code.

## Best Practices

The paper by Wilson et al goes through and identifies what they think are the most important aspects of scientific computing. Their best practices are outlined as 8 major points.

1. Write programs for people, not computers
2. Let the computer do the work
3. Make incremental changes
4. Don't repeat yourself (or others)
5. Plan for mistakes
6. Optimize code only after it works correctly
7. Document design and purpose, not mechanics
8. Collaborate

In IN1910, we will return to these practices and try to reflect on how to implement them in our workflow and code.



## Languages in 1910

In 1910 is a continuation of IN1900, and will primarily be using Python. However, we will also be introducing a second language: C++.

Python is a modern, object-oriented programming language. It has a clear, readable syntax, making it easy to learn, and easy to write understandable, maintainable, and shareable code. It also has a good standard library and plenty of extensions for scientific computing. It is also open source. All of this points to Python being a good language for scientific computing. Another popular language for scientific computing that has gain a lot of attraction the recent years is Julia. Julia would definitely also be a suitable language of choice for this course, however we believe Python is more applicable to a larger group of developer especially within the field of data science and machine learning.

We also will dive deeper into object-oriented programming and other concepts in computer science that are not that well covered by Julia. Besides, Python has a syntax fairly similar to Julia, and so learning Python well will equip you to handle Julia at a later point.

Note that we do expect students taking IN1900 to be fairly familiar with Python. If you are not, you should expect to put in more work during the first few weeks of the course. Here, [the book from Langtangen](https://link.springer.com/book/10.1007%2F978-3-662-49887-3) is a good resource to use.

Why do we choose to also include C++, and not just stick to Python? First of all, learning a second language is very helpful on its own. As it helps you generalize programming concepts and not get to attached to a single way of writing code. C++ is a very popular language, and so the chances you will meet or use the language later is high. It is also low-level, compared to Python, which is high-level, and so they have different areas of use. Knowing C++ let's us write more efficient and faster code than Python, with drawbacks we will get back to later. Lastly, C++ is based on C, the most used programming language in the world, and many other languages are inspired heavily on C. Knowing C++ will therefore make using other languages a lot easier (C, Java, C#, objective-C, javascript, etc). Python on the other hand, has a syntax that is quite different from these, and so knowing *only* Python can be restrictive for working with code in other languages.

The magazine IEEE Spectrum publishes an annual list of programming langues ranked by popularity. The top ten programming langues (by popularity) are shown in the figure below


```{figure} ../figures/spectrum_ranking_2021.png
---
width: 400px
name: spectrum_ranking
alt: spectrum_ranking
---
Top programming languages for [2021](https://spectrum.ieee.org/top-programming-languages-2021)
```

The symbols indicate what people often use the langues for, with the globe meaning web, the cellphone mobile, the screen desktop and scientific applications, and the chip embedded applications.

The spectrum ranking is just one of many rankings, and it doesn't necessarily mean that much. The main reason we bring it up is to point out that knowing Python and a bit of C++ will most likely be very useful if you continue doing *any* kind of programming in your future, be it scientific or other.

Another annual review is the [Stack overflow developer survey](https://insights.stackoverflow.com/survey/2021#most-loved-dreaded-and-wanted-language-want) which shows that python is the most wanted language in 2021.
