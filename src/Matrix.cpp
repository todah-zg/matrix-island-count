/**
 * @file Matrix.cpp
 * @author Marijan Kozic (marijan@todah.hr)
 * @brief Implementation of the Matrix class
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Matrix.h"

//
// Default Matrix class implementation. Does NOT preserve state.
//

matrix::Matrix::Matrix(const std::vector<std::vector<int>> &_elements)
    : mElements(_elements),
      mRows(_elements.size()),
      mCols(_elements[0].size()){};

bool matrix::Matrix::isSet(const matrix::position_t &position) const
{
    return mElements[position.x][position.y] == 1;
}

bool matrix::Matrix::isValidPosition(const matrix::position_t &position) const
{
    return (position.x >= 0 && position.x < mRows &&
            position.y >= 0 && position.y < mCols);
}

std::vector<matrix::position_t> matrix::Matrix::getAllElementPositions()
{

    std::vector<matrix::position_t> positions;
    for (int x = 0; x < mRows; ++x)
    { // i
        for (int y = 0; y < mCols; ++y)
        { // j
            matrix::position_t pos = {x, y};
            positions.push_back(pos);
        }
    }

    return positions;
}

bool matrix::Matrix::isProcessed(const matrix::position_t &position) const
{
    return mElements[position.x][position.y] == 2;
}

void matrix::Matrix::markAsProcessed(const matrix::position_t &position)
{
    mElements[position.x][position.y] = 2;
}

std::vector<matrix::position_t> matrix::Matrix::getNeighbourElements(const matrix::position_t &position)
{
    int offset_x[] = {0, 0, -1, 1};
    int offset_y[] = {-1, 1, 0, 0};
    int offset_steps = 4;
    std::vector<matrix::position_t> neighbours;

    for (int i = 0; i < offset_steps; ++i)
    {
        matrix::position_t newPosition;
        newPosition.x = position.x + offset_x[i];
        newPosition.y = position.y + offset_y[i];
        neighbours.push_back(newPosition);
    }

    return neighbours;
}

void matrix::Matrix::processAllConnectedElements(const matrix::position_t &startPosition)
{

    std::queue<matrix::position_t> searchQueue;
    searchQueue.push(startPosition);
    markAsProcessed(startPosition);

    while (!searchQueue.empty())
    {
        matrix::position_t position = searchQueue.front();
        searchQueue.pop();

        for (auto curPosition : getNeighbourElements(position))
        {
            if (isValidPosition(curPosition) && isSet(curPosition) && !isProcessed(curPosition))
            {
                markAsProcessed(curPosition);
                searchQueue.push(curPosition);
            }
        }
    }
}

int matrix::Matrix::countFigures()
{
    if (mElements.empty())
    {
        return 0;
    }

    int count = 0;
    for (auto position : getAllElementPositions())
    {
        if (isSet(position) && !isProcessed(position))
        {
            count++;
            processAllConnectedElements(position);
        }
    }

    return count;
}

void matrix::Matrix::print()
{
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mCols; j++)
        {
            printf("%d ", mElements[i][j]);
        }
        printf("\n");
    }
}

//
// FastMatrix class implementation. Preserves state. Requires additional memory.
//

matrix::FastMatrix::FastMatrix(const std::vector<std::vector<int>> &_elements)
    : Matrix(_elements), mElementsBackup(_elements){};

bool matrix::FastMatrix::isProcessed(const matrix::position_t &position) const
{
    return mElementsBackup[position.x][position.y] == 2;
}

void matrix::FastMatrix::markAsProcessed(const matrix::position_t &position)
{
    mElementsBackup[position.x][position.y] = 2;
}

void matrix::FastMatrix::reset()
{
    mElementsBackup = mElements;
}

int matrix::FastMatrix::countFigures()
{
    int count = matrix::Matrix::countFigures();
    reset();

    return count;
}

//
// LeanMatrix class implementation. Preserves state. Slower to reset.
//

matrix::LeanMatrix::LeanMatrix(const std::vector<std::vector<int>> &_elements)
    : Matrix(_elements){};

bool matrix::LeanMatrix::isProcessed(const matrix::position_t &position) const
{
    return mElements[position.x][position.y] >= 2;
}

void matrix::LeanMatrix::markAsProcessed(const matrix::position_t &position)
{
    mElements[position.x][position.y] += 2;
}

void matrix::LeanMatrix::reset()
{
    for (auto position : getAllElementPositions())
    {
        if (isProcessed(position))
        {
            mElements[position.x][position.y] -= 2;
        }
    }
}

int matrix::LeanMatrix::countFigures()
{
    int count = matrix::Matrix::countFigures();
    reset();

    return count;
}