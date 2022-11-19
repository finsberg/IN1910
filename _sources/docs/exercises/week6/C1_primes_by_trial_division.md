---
jupyter:
  jupytext:
    text_representation:
      extension: .md
      format_name: markdown
      format_version: '1.3'
      jupytext_version: 1.10.3
  kernelspec:
    display_name: Python 3
    language: python
    name: python3
---

# Challenge 1

## Checking Primality by Trial Division

Integers have many different mathematical properties that could be of interest, in this exercise we will look at [*prime numbers*](https://en.wikipedia.org/wiki/Prime_number). The wikipedia definition of a prime number is as follows:
> A prime number (or a prime) is a natural number greater than 1 that has no positive divisors other than 1 and itself. A natural number greater than 1 that is not a prime number is called a composite number. As an example, 5 is prime because 1 and 5 are its only positive integer factors, whereas 6 is composite because it has the divisors 2 and 3 (in addition to 1 and 6).

The goal of this exercise is to write a function `is_prime(n)` that takes an integer and checks if it is prime. We will start of with the *naive solution* and then make it more effective.

### Checking divisibility

We first have to check if an integer is divisible by another integer. For any two integers, $a$ and $b$, we can write $a/b$ as

$$\frac{a}{b} = N + \frac{r}{b},$$

where $N$ is an integer denoting how many times $a$ evenly divides into $b$, and $r$ is a non-negative integer smaller than $b$, so that $r/b$ is a decimal number in the interval $[0, 1)$.

For example, if $a$ is 7 and $b$ is 3 we get
$$\frac{7}{3} = 2 + \frac{1}{3}.$$

So $N=3$ and $r=1$. We call $r$ the *remainder* of the division. We say that $a$ is *divisible* by $b$ if there is no remainder, i.e., $r = 0$.

We can find $N$ by integer division, and $r$ by using the modulo operator.


#### Exercise (a)

The *naive solution* to checking whether a number is a prime is to follow the definition of prime numbers and simply check every integer from 2 up to (but not including) the number itself.

Define a function `is_prime` that checks if a positive integer $n$ is a prime using the naive solution. Use it to find the first ten prime numbers.

Hints:
1. You can handle the edge cases of n equal to 1, 2 and 3 by simply testing
2. Be careful not to test divisibility by 1 or $n$ itself, as all numbers are divisible by 1 and themselves
3. If you find a number that evenly divides $n$, you can immediately return `false` as the number is not a prime, no need to check all the numbers in this case.


### Optimization

If implemented correctly, `is_prime` can now check the primality of any positive integer $n$, but as we have to loop over *all* numbers from 1 to n (exclusive), it will be very slow for large $n$. If we for example want to find all primes below 1 billion, we would have to loop over *a lot* of numbers. In the following exercises you will improve your algorithm to make it a bit more efficient.

#### Exercise (b)

Our naive solution might be very basic and slow, but we are fairly sure it works precisely *because* of its simplicity, and we tested it by finding the first 10 primes. As we now go through and optimize our code, we must make sure we don't break our functionality. Write a test block or function that you can use after each change you make to ensure that while our function is getting faster, we aren't changing its functionality.


#### Exercise (c)

The first thing we can ask, is if we really need to check all numbers in the range $[2, n)$? Let us look at an example, 100 is a composite number and can be written out as the following products:
1. $2×50$
2. $4×25$
3. $5×20$
4. $10×10$
5. $20×5$
6. $25×4$
7. $50×2$

Note that we find 7 ways to create 100 by multiplying 2 integers. However, the final three version are just the first three ones flipped around. This will be the case for any number. In this case the turning point is $\sqrt{N}$ because $100$ is a square number, but from this we see that for any number $n$ that can be written as a product of two divisors, at least one of them will be smaller or equal to $\sqrt{n}$. Thus we can reduce our range of numbers to check from $[2, \sqrt{n}]$. For large numbers, such as $10^6$, this is a huge reduction.

Update your `is_prime` function so that you only check the range [2, √n], and verify that your function still handles your test block/function from exercise (c).


#### Exercise (d)

We just narrowed down the range of number we check considerably, but do we have to check *every single* number in the range $[2, \sqrt{n}]$. You have probably noticed that all primes, except for 2, are odd numbers (as opposed to being even). Why is this? It happens because all even numbers are evenly divisible by 2, and so are not prime. This means we only have to check odd numbers. But even better, this also means we only have to check *odd-valued divisors* to check primality (why? Try to convince yourself why this is, or discuss it with a classmate).

Update your function so that you check if $n$ is even *before* you start looping over your divisor candidates. And then update your loop so that it skips all even numbers in the range $[3, \sqrt{n}]$. And then verify that your function still handles your test block/function from exercise (c).


#### Exercise (e)

By checking if a number was even, we could effectively skip checking *half* of the possible divisors, which is a very nice reduction. We can go one step further by also considering the number 3. No numbers that are divisible by $3$ can be prime (other than 3 itself).

To implement this, note that any integer $n$ kan be written on exactly one of the six following forms:
* $n = 6k - 2$
* $n = 6k - 1$
* $n = 6k$
* $n = 6k + 1$
* $n = 6k + 2$
* $n = 6k + 3$

where $k$ is an integer. As $n$ grows, so does $k$. Now, note that the first, third and fifth possibilities are instantly discardable because they are even. This leaves us with the fact that all primes can be written as:
* $n = 6k - 1$
* $n = 6k + 1$
* $n = 6k + 3$

Of these remaining three, note that the last option is divisible by 3 for all $k$, so we can disregard them as well. This means all primes can be written as the two possibilities:
* $n = 6k - 1$
* $n = 6k + 1$

The also means all possible candidate divisors are on one of these two forms (as all divisors are prime).

Update your `is_prime` function so that when looping over candidate divisors, you only check the candidates on the form $6k\pm1$. Run your test block/function to verify your code.


### Project Euler Prime Number Problems

You have now implemented a fairly optimized function for checking if a number is prime by trial division. Let us use your work to solve some [Project Euler problems](https://projecteuler.net/).

#### Exercise (f)

(This is the [7th problem of Project Euler](https://projecteuler.net/problem=7).)

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

**What is the 10001st prime number?**

#### Exercise (g)

(This is the [10th problem of Project Euler](https://projecteuler.net/problem=10).)

The sum of all primes below 10 is 2 + 3 + 5 + 7 = 17.

**Find the sum of all the primes below two million.**
