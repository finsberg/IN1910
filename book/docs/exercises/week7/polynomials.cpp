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
