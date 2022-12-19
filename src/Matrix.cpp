#include "Matrix.h"
#include <queue>

// TODO snake_case (mozda i za ime klase)
// TODO vidjet za linter...
// TODO tests
// TODO comments
// TODO enum
// TODO velicine u privatne varijable prilikom konstruktora

// akon te jako veseli onda mozes paralizaciju
// std::thread

bool matrix::Matrix::isValid(int x, int y) const
{
    return (x >= 0 && x < this->data.size() &&
            y >= 0 && y < this->data[0].size());
}

void matrix::Matrix::markAsProcessed(int x, int y)
{
    // variant using special value '2' to mark processed elements
    this->data[x][y] = 2;
}

bool matrix::Matrix::isProcessed(int x, int y) const
{
    // variant using special values
    return this->data[x][y] == 2;
}

void matrix::Matrix::findAllNeighbours(int x, int y)
{ // mozda const
    // uses BFS to find all connected elements (for now)

    // taken 2 by 2, these values cover all neighbouring position offsets
    int offset[] = {0, 1, 0, -1, 0}; // TODO 2 varijable

    std::queue<std::pair<int, int>> searchQueue;
    searchQueue.emplace(x, y);

    this->markAsProcessed(x, y);

    while (!searchQueue.empty())
    {
        int row = searchQueue.front().first;
        int col = searchQueue.front().second;
        searchQueue.pop();

        for (int i = 0; i < 4; ++i)
        { // 4 -> velicina offseta
            int new_x = x + offset[i];
            int new_y = y + offset[i + 1];
            if (isValid(new_x, new_y) && !isProcessed(new_x, new_y))
            {
                markAsProcessed(new_x, new_y);
                searchQueue.emplace(new_x, new_y);
            }
        }
    }
}

int matrix::Matrix::countFigures()
{
    if (this->data.empty())
    {
        return 0;
    }

    int count = 0;
    for (int x = 0; x < this->data.size(); ++x)
    { // i
        for (int y = 0; y < this->data[0].size(); ++y)
        { // j
            if (this->data[x][y] == 1 && !isProcessed(x, y))
            {
                ++count;
                findAllNeighbours(x, y);
            }
        }
    }

    return count;
}
