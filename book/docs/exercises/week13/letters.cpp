#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int count_letters(char *filename, char *letter)
{
    string line;
    int num_letters = 0;
    ifstream myfile(filename);
    getline(myfile, line);

#pragma omp parallel for reduction(+ : num)
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == *letter)
        {
            num_letters++;
        }
    }

    return num_letters;
}

int main()
{
    cout << count_letters("letters.txt", "A") << endl;
    return 0;
}
