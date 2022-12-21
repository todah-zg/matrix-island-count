#include "Matrix.h"
#include <cstdio>
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;

int main(void)
{
    int max = 20;
    srand(time(NULL));
    int size = rand() % max;
    vector<vector<int>> v(size, vector<int>(size));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            v[i][j] = rand() % 2;
        }
    }

    auto matrix = matrix::Matrix(v);
    cout << "Generated " << size << " x " << size << " matrix:\n";
    cout << matrix;
    cout << "\n\nNumber of individual figures: " << matrix.countFigures() << "\n";

return 0;

}
