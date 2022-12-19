#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace matrix
{

    class Matrix
    {
    private:
        std::vector<std::vector<int>> elements;
        int rows;
        int cols;

        bool isValid(int x, int y) const;
        void findAllNeighbours(int x, int y);
        void markAsProcessed(int x, int y);
        bool isProcessed(int x, int y) const;

    public:
        int countFigures();
        Matrix() {}
        Matrix(std::vector<std::vector<int>> _elements)
            : elements(_elements),
              rows(_elements.size()),
              cols(_elements[0].size()){};
    };

} // namespace matrix

#endif