#include "Matrix.h"
#include <queue>

// TODO tests
// TODO comments
// TODO enum
// TODO velicine u privatne varijable prilikom konstruktora

// akon te jako veseli onda mozes paralizaciju
// std::thread

matrix::Matrix::Matrix(std::vector<std::vector<int>> _elements)
    : elements(_elements),
      rows(_elements.size()),
      cols(_elements[0].size()){};

matrix::FastMatrix::FastMatrix(std::vector<std::vector<int>> _elements)
    : Matrix(_elements), elementsBackup(_elements){};

matrix::LeanMatrix::LeanMatrix(std::vector<std::vector<int>> _elements)
    : Matrix(_elements){};

bool matrix::Matrix::isSet(position_t position) {
    this->elements[position.x][position.y] == 1;
}

bool matrix::Matrix::isValidPosition(position_t position) const
{
    return (position.x >= 0 && position.x < this->rows &&
            position.y >= 0 && position.y < this->cols);
}

void matrix::Matrix::markAsProcessed(position_t position)
{
    this->elements[position.x][position.y] = 2;
}

bool matrix::Matrix::alreadyProcessed(position_t position) const
{
    return this->elements[position.x][position.y] == 2;
}

std::vector<position_t> getNeighbourElements(position_t position)
{
    int offset_x[] = {0, 0, -1, 1};
    int offset_y[] = {-1, 1, 0, 0};
    int offset_steps = 4;
    std::vector<position_t> neighbours;

    for (int i = 0; i < offset_steps; ++i)
    {
        position_t newPosition;
        newPosition.x = position.x + offset_x[i];
        newPosition.y = position.y + offset_y[i];
        neighbours.push_back(newPosition);
    }

    return neighbours;
}

void matrix::Matrix::processAllConnectedElements(position_t startPosition)
{

    std::queue<position_t> searchQueue;
    searchQueue.push(startPosition);
    markAsProcessed(startPosition);

    while (!searchQueue.empty())
    {
        position_t position = searchQueue.front();
        searchQueue.pop();

        for (auto curPosition : getNeighbourElements(position))
        {
            if (isValidPosition(curPosition) && !alreadyProcessed(curPosition))
            {
                markAsProcessed(curPosition);
                searchQueue.push(curPosition);
            }
        }
    }
}

std::vector<position_t> matrix::Matrix::getAllElementPositions() {
    
    std::vector<position_t> positions;
    for (int x = 0; x < this->rows; ++x)
    { // i
        for (int y = 0; y < this->cols; ++y)
        { // j
            position_t pos = {x, y};
            positions.push_back(pos);
        }
    }
    
    return positions;
}

int matrix::Matrix::countFigures()
{
    if (this->elements.empty())
    {
        return 0;
    }

    int count = 0;
    for (auto position : getAllElementPositions()) {
        if (isSet(position) && !alreadyProcessed(position)) {
            ++count;
            processAllConnectedElements(position);
        }
    }

    return count;
}
