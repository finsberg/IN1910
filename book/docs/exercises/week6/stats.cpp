#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void stats(vector<double> data, double &mean, double &median, vector<double> &data_sorted)
{
    /*Note that "data" has not been called by reference. By skipping "&" we call
    "data" by value, meaning "data" inside this function is just a copy of the
    original. This is important so that we avoid sorting the original vector.
    */
    mean = 0;
    for (int i = 0; i < data.size(); i++)
    {
        mean += data[i];
    }
    mean = mean / data.size();

    sort(data.begin(), data.end()); // Soring copy of data
    data_sorted = data;

    if (data.size() % 2 == 0)
    {
        median = (data_sorted[data.size() / 2 - 1] + data_sorted[data.size() / 2]) / 2;
    }
    else
    {
        median = data_sorted[data.size() / 2];
    }
}

int main()
{
    double mean, median;
    vector<double> data = {1.2, 5.3, 7.1, -2.4, 9.2}, data_sorted;
    stats(data, mean, median, data_sorted);
    cout << "Mean: " << mean << ". Median: " << median << endl;

    cout << "Sorted vector: {";
    for (int i = 0; i < data.size(); i++)
    {
        cout << data_sorted[i] << " ";
    }
    cout << "}" << endl;

    cout << "Unsorted vector: {";
    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i] << " ";
    }
    cout << "}" << endl;

    return 0;
}
