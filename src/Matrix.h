#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace matrix
{

    class Matrix
    {
    private:
        std::vector<std::vector<int>> elements;
        const int rows;
        const int cols;

        bool isValid(int x, int y) const;
        void findAllNeighbours(int x, int y);
        void markAsProcessed(int x, int y);
        bool isProcessed(int x, int y) const;

    public:
        Matrix(std::vector<std::vector<int>>);
        int countFigures();
    };

} // namespace matrix

#endif