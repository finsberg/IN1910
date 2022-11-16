#include <cmath>
#include <iostream>

double yolk(double To, double Tw, double M)
{
    double rho = 1.038;
    double c = 3.7;
    double K = 5.4 * std::pow(10, -3.0);
    double pi = 3.14;

    double Ty = 70;

    double t;

    double temp =
        // Remember that c++ does integer division when numbers are integers.
        // So remember to say 2.0/3.0, not 2/3
        t = (std::pow(M, 2.0 / 3.0) * c * std::pow(rho, 1.0 / 3.0)) /
            (K * pi * pi * std::pow((4 * pi / 3.0), 2.0 / 3.0)) * std::log(0.76 * (To - Tw) / (Ty - Tw));

    return t;
}

int main()
{
    double small_M{47.0};
    double big_M{67.0};

    double Tw = 100.0;
    double To = 4.0;

    double t;

    t = yolk(To, Tw, small_M);

    std::cout << "Time for cooking egg is " << t << " seconds"
              << "\n";
}
