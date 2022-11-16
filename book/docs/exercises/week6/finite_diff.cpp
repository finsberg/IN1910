#include <iostream>

void solve()
{
    int N = 10001;

    double *t = new double[N];
    double *u = new double[N];

    double a = 4.3;
    double u0 = 15.7;

    double dt = 0.001;
    t[0] = 0;
    u[0] = u0;

    for (int i = 1; i < N; i++)
    {
        t[i] = t[i - 1] + dt;
        u[i] = u[i - 1] + dt * (-a * u[i - 1]);
        if (i % 100 == 0)
        {
            // std::cout << "t=" << t[i] << " u=" << u[i] << std::endl;
            printf("t=%4.1f u=%g\n", t[i], u[i]);
        }
    }

    delete[] t;
    delete[] u;
}

int main()
{
    solve();

    return 0;
}
