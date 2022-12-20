/**
 * @file Matrix.h
 * @author Marijan Kozic (marijan@todah.hr)
 * @brief Matrix class and related subclasses
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace matrix
{

    /**
     * @brief Simple struct type to track position in a 2D matrix
     *
     */
    typedef struct
    {
        int x;
        int y;
    } position_t;

    class Matrix
    {
    private:
        std::vector<std::vector<int>> elements;
        const int rows;
        const int cols;

        bool isSet(const position_t& position) const;
        bool isValidPosition(const position_t& position) const;
        bool alreadyProcessed(const position_t& position) const;
        std::vector<position_t> getNeighbourElements(const position_t& position);
        void processAllConnectedElements(const position_t& position);
        void markAsProcessed(const position_t& position);
        void reset();

    public:
        Matrix(const std::vector<std::vector<int>>& elements);
        std::vector<position_t> getAllElementPositions();
        int countFigures();
    };

    class FastMatrix : public Matrix
    {
    private:
        std::vector<std::vector<int>> elementsBackup;

    public:
        FastMatrix(const std::vector<std::vector<int>>& elements);
    };

    class LeanMatrix : public Matrix
    {
    public:
        LeanMatrix(const std::vector<std::vector<int>>& elements);
    };
} // namespace matrix

#endif