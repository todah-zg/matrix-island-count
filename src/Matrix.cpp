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
      mRows(_elements.empty() ? 0 : _elements.size()),
      mCols(_elements.empty() ? 0 : _elements[0].size()) {}

// matrix::Matrix::~Matrix(){}

bool matrix::Matrix::isSet(const matrix::position &position) const
{
    return mElements[position.x][position.y] == ::matrix::State::set;
}

bool matrix::Matrix::isValidPosition(const matrix::position &position) const
{
    return (position.x >= 0 && position.x < mRows &&
            position.y >= 0 && position.y < mCols);
}

std::vector<matrix::position> matrix::Matrix::getAllElementPositions()
{

    std::vector<matrix::position> positions;
    for (int x = 0; x < mRows; ++x)
    { // i
        for (int y = 0; y < mCols; ++y)
        { // j
            positions.emplace_back(x, y);
        }
    }

    return positions;
}

bool matrix::Matrix::isProcessed(const matrix::position &position) const
{
    return mElements[position.x][position.y] == ::matrix::State::visited;
}

void matrix::Matrix::markAsProcessed(const matrix::position &position)
{
    mElements[position.x][position.y] = ::matrix::State::visited;
}

std::vector<matrix::position> matrix::Matrix::getNeighbourElements(const matrix::position &position)
{
    int offset_x[] = {0, 0, -1, 1};
    int offset_y[] = {-1, 1, 0, 0};
    int offset_steps = 4;
    std::vector<matrix::position> neighbours;

    for (int i = 0; i < offset_steps; ++i)
    {
        neighbours.emplace_back(position.x + offset_x[i], position.y + offset_y[i]);
    }

    return neighbours;
}

void matrix::Matrix::processAllConnectedElements(const matrix::position &startPosition)
{

    std::queue<matrix::position> searchQueue;
    searchQueue.push(startPosition);
    markAsProcessed(startPosition);

    while (!searchQueue.empty())
    {
        matrix::position position = searchQueue.front();
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

std::string matrix::Matrix::getString() const
{
    std::stringstream ss;

    ss << "{";
    for (int i = 0; i < mRows; i++)
    {
        ss << "{";
        for (int j = 0; j < mCols; j++)
        {
            if (j == 0){
                ss << mElements[i][j];
            } else {
                ss << ", " << mElements[i][j];
            }
        }
        if (i == mRows - 1) {
            ss << "}}";
        } else {
            ss << "},\n ";
        }
    }
    return ss.str();
}

std::ostream& matrix::operator<<(std::ostream &s, const matrix::Matrix &m)
{
    return (s << m.getString());
}


//
// FastMatrix class implementation. Preserves state. Requires additional memory.
//

matrix::FastMatrix::FastMatrix(const std::vector<std::vector<int>> &_elements)
    : Matrix(_elements), mElementsBackup(_elements){};

bool matrix::FastMatrix::isProcessed(const matrix::position &position) const
{
    return mElementsBackup[position.x][position.y] == ::matrix::State::visited;
}

void matrix::FastMatrix::markAsProcessed(const matrix::position &position)
{
    mElementsBackup[position.x][position.y] = ::matrix::State::visited;
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

void matrix::LeanMatrix::reset()
{
    for (auto position : getAllElementPositions())
    {
        if (isProcessed(position))
        {
            mElements[position.x][position.y] = ::matrix::State::set;
        }
    }
}

int matrix::LeanMatrix::countFigures()
{
    int count = matrix::Matrix::countFigures();
    reset();

    return count;
}