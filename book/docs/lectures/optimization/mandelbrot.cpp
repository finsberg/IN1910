#include <vector>

int mandelbrot_pixel(double cx, double cy, int maxiter)
{
    double x = cx;
    double y = cy;

    for (int n = 0; n < maxiter; n++)
    {
        double x2 = x * x;
        double y2 = y * y;

        if (x2 + y2 > 4.0)
        {
            return n;
        }

        y = 2 * x * y + cy;
        x = x2 - y2 + cx;
    }
    return 0;
}

std::vector<int> mandelbrot(double xmin, double xmax, double ymin, double ymax, int width, int height, int maxiter)
{
    std::vector<int> output(width * height);
    int i, j;
    double cx, cy;

    double dx = (xmax - xmin) / width;
    double dy = (ymax - ymin) / width;

    for (i = 0; i < width; i++)
    {
        for (j = 0; j < height; j++)
        {
            cx = xmin + i * dx;
            cy = ymin + j * dy;
            output[i * height + j] = mandelbrot_pixel(cx, cy, maxiter);
        }
    }
    return output;
}

void benchmark()
{
    double xmin = -0.74877;
    double xmax = -0.74872;
    double ymin = 0.065053;
    double ymax = 0.065103;
    int width = 1000;
    int height = 1000;
    int maxiter = 2048;

    auto output = mandelbrot(xmin, xmax, ymin, ymax, width, height, maxiter);
}

int main()
{
    benchmark();

    return 0;
}
