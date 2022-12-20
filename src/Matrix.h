#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

typedef struct {
    int x;
    int y;
} position_t;
namespace matrix
{
    class Matrix
    {
    private:
        std::vector<std::vector<int>> elements;
        const int rows;
        const int cols;

        bool isSet(position_t);
        bool isValidPosition(position_t) const;
        bool alreadyProcessed(position_t) const;
        std::vector<position_t> getNeighbourElements(position_t);
        void processAllConnectedElements(position_t);
        void markAsProcessed(position_t);
        void reset();

    public:
        Matrix(std::vector<std::vector<int>>);
        std::vector<position_t> getAllElementPositions();
        int countFigures();
    };

    class FastMatrix : public Matrix
    {
    private:
        std::vector<std::vector<int>> elementsBackup;

    public:
        FastMatrix(std::vector<std::vector<int>>);
    };

    class LeanMatrix : public Matrix
    {
    public:
        LeanMatrix(std::vector<std::vector<int>>);
    };
} // namespace matrix

#endif