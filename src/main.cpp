#include "Matrix.h"
#include <cstdio>
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;

int main(void)
{
    int max = 30;
    vector<vector<int>> v(max, vector<int>(max));

    for (int i = 0; i < max; i++)
    {
        for (int j = 0; j < max; j++)
        {
            v[i][j] = rand() % 2;
        }
    }

    auto m = matrix::Matrix(v);
    std::cout << m;

return 0;

}
