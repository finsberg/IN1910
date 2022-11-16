# Week 7

## Part A - Cartesian and polar coordinates

```c++
#include <cassert>
#include <cmath>
#include <iostream>

#define PI 3.141593

struct CartesianPoint
{
    double x;
    double y;
};

struct PolarPoint
{
    double r;
    double theta;
};

PolarPoint cart2polar(const CartesianPoint &cart)
{
    double r = std::sqrt(std::pow(cart.x, 2) + std::pow(cart.y, 2));
    double theta = std::atan(cart.y / cart.x);
    return {r, theta};
}

CartesianPoint polar2cart(const PolarPoint &polar)
{
    double x = polar.r * std::cos(polar.theta);
    double y = polar.r * std::sin(polar.theta);
    return {x, y};
}

void test_conversion()
{
    CartesianPoint c_point{1, 1};
    PolarPoint p_point{1, PI / 2};

    CartesianPoint actual_c = polar2cart(p_point);
    CartesianPoint expected_c{0, 1};

    double tol = 1e-6;
    assert(std::abs(actual_c.x - expected_c.x) < tol);
    assert(std::abs(actual_c.y - expected_c.y) < tol);

    PolarPoint actual_p = cart2polar(c_point);
    PolarPoint expected_p{std::sqrt(2), PI / 4};

    assert(std::abs(actual_p.r - expected_p.r) < tol);
    assert(std::abs(actual_p.theta - expected_p.theta) < tol);
}

PolarPoint scale(const PolarPoint &point, int s)
{
    return {point.r * s, point.theta};
}

CartesianPoint scale(const CartesianPoint &point, int s)
{
    return {point.x * s, point.y * s};
}

void test_scale()
{
    CartesianPoint c_point{3, 3};

    CartesianPoint actual_c = scale(c_point, 2);
    CartesianPoint expected_c{6, 6};

    double tol = 1e-6;
    assert(std::abs(actual_c.x - expected_c.x) < tol);
    assert(std::abs(actual_c.y - expected_c.y) < tol);

    PolarPoint p_point{3, PI / 2};
    PolarPoint actual_p = scale(p_point, 2);
    PolarPoint expected_p{6, p_point.theta};

    assert(std::abs(actual_p.r - expected_p.r) < tol);
    assert(std::abs(actual_p.theta - expected_p.theta) < tol);
}

PolarPoint rotate(const PolarPoint &point, double w)
{
    return {point.r, point.theta + w};
}

CartesianPoint rotate(const CartesianPoint &point, double w)
{
    double x = std::cos(w) * point.x - std::sin(w) * point.y;
    double y = std::sin(w) * point.x + std::cos(w) * point.y;
    return {x, y};
}

void test_rotate()
{
    CartesianPoint c_point{3, 0};
    CartesianPoint actual_c = rotate(c_point, PI / 2);
    CartesianPoint expected_c{0, 3};

    double tol = 1e-6;
    assert(std::abs(actual_c.x - expected_c.x) < tol);
    assert(std::abs(actual_c.y - expected_c.y) < tol);

    PolarPoint p_point{3, PI / 4};
    PolarPoint actual_p = rotate(p_point, PI / 4);
    PolarPoint expected_p{p_point.r, PI / 2};

    assert(std::abs(actual_p.r - expected_p.r) < tol);
    assert(std::abs(actual_p.theta - expected_p.theta) < tol);
}

int main()
{
    test_conversion();
    test_scale();
    test_rotate();

    return 0;
}
```
## Part B - Affine Transformations
```c++
#include <cassert>
#include <cmath>
#include <iostream>

struct CartesianPoint
{
    double x;
    double y;
};

class AffineTransform
{
  private:
    double _a, _b, _c, _d, _e, _f;

  public:
    inline AffineTransform(double a, double b, double c, double d, double e, double f)
        : _a{a}, _b{b}, _c{c}, _d{d}, _e{e}, _f{f}
    {
    }

    inline AffineTransform(double a, double b, double c, double d) : _a{a}, _b{b}, _c{c}, _d{d}, _e{0}, _f{0}
    {
    }

    // Similar to pythons magic method __call__.
    inline CartesianPoint operator()(double x, double y)
    {
        double f_x = _a * x + _b * y + _e;
        double f_y = _c * x + _d * y + _f;
        return {f_x, f_y};
    }
};

void test_affine()
{
    AffineTransform a{1, 2, 3, 4, 5, 6};

    CartesianPoint actual = a(1, 2);
    CartesianPoint expected{10, 17};

    double tol = 1e-6;
    assert(std::abs(actual.x - expected.x) < tol);
    assert(std::abs(actual.y - expected.y) < tol);
}

int main()
{
    test_affine();
    return 0;
}
```


## Part C - A class for polynomials

```c++
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>

class Polynomial
{
  private:
    std::map<int, double> _coeffs;

  public:
    inline Polynomial(std::map<int, double> coeffs) : _coeffs{coeffs}
    {
    }

    inline double operator()(double x)
    {
        double sum = 0;

        for (std::pair<int, double> pair : _coeffs)
        {
            sum += pair.second * std::pow(x, pair.first);
        }

        return sum;
    }

    void print()
    {
        std::ostringstream stream;
        // A map is default sorted ascending. We therefore
        // traverse the liste backward, hence rbegin and rend, instead
        // of begin and end. We replace std::map<int, double>::reverse_iterator
        // with auto.
        for (auto pair = _coeffs.rbegin(); pair != _coeffs.rend(); ++pair)
        {
            stream << pair->second << "x^" << pair->first << " + ";
        }
        std::string result = stream.str();

        // Fix up uglyness (not important)
        result = std::regex_replace(result, std::regex{" \\+ -"}, " - ");
        result = std::regex_replace(result, std::regex{"1x"}, "x");
        result = std::regex_replace(result, std::regex{"\\^0"}, "");

        // Remove last ' + '
        result = result.substr(0, result.size() - 3);

        std::cout << result << std::endl;
    }
};

void test_poly()
{
    Polynomial p{{{10, 1}, {5, -5}, {0, 1}}};
    p.print();

    double tol = 1e-6;

    auto expected = 1185;
    auto actual = p(-2);
    assert(std::abs(actual - expected) < tol);

    expected = 1;
    actual = p(0);
    assert(std::abs(actual - expected) < tol);

    expected = 865;
    actual = p(2);
    assert(std::abs(actual - expected) < tol);
}

int main()
{
    test_poly();

    return 0;
}
```
