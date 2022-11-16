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
