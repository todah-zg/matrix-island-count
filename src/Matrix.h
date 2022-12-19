#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace matrix {

class Matrix 
{
private:
    std::vector<std::vector<int>> data;

    bool isValid(int x, int y);
    void findAllNeighbours(int x, int y);
    void markAsProcessed(int x, int y);
    bool isProcessed(int x, int y);

public:
    int countFigures();
};

} // namespace matrix



#endif