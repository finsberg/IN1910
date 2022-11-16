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

void test_convertion()
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
    test_convertion();
    test_scale();
    test_rotate();

    return 0;
}
