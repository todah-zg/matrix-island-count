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
#include <iostream>
#include <sstream>
#include <queue>

namespace matrix
{

    /**
     * @brief Simple struct to track position in a 2D matrix
     *
     */
    struct position
    {
        int x;
        int y;

        position(int _x, int _y) : x(_x), y(_y){} 

    };

    /**
     * @brief 2D matrix to store topographical data represented as elements
     *        that are either set or unset. Allows counting the connected figures.
     *        Default implementation does NOT preserve the original data.
     *
     */
    class Matrix
    {
    protected:
        std::vector<std::vector<int>> mElements;
        const int mRows;
        const int mCols;

        /**
         * @brief Check if a given position is set
         *
         * @param position
         * @return true
         * @return false
         */
        bool isSet(const position &position) const;

        /**
         * @brief Check that a given position is not out of bounds
         *
         * @param position
         * @return true
         * @return false
         */
        bool isValidPosition(const position &position) const;

        /**
         * @brief Get the list of all possible element positions
         *
         * @return std::vector<position_t>
         */
        std::vector<position> getAllElementPositions();

        /**
         * @brief Check if a given position has alread been visited to avoid
         *        processing it again
         *
         * @param position
         * @return true
         * @return false
         */
        virtual bool isProcessed(const position &position) const;

        /**
         * @brief Mark a given position as already processed.
         *        Changes the elements state.
         *
         * @param position
         */
        virtual void markAsProcessed(const position &position);

        /**
         * @brief Get the list of all Neighbouring elements
         *
         * @param position
         * @return std::vector<position_t>
         */
        std::vector<position> getNeighbourElements(const position &position);

        /**
         * @brief Process all neighbouring elements connected to a given position,
         *        comprising a single figure
         *
         * @param position
         */
        void processAllConnectedElements(const position &position);

    public:
        /**
         * @brief Construct a new Matrix object
         *
         * @param elements
         */
        Matrix(const std::vector<std::vector<int>> &elements);

        /**
         * @brief Returns the number of connected figures in the matrix
         *
         * @return int
         */
        virtual int countFigures();

        /**
         * @brief Returns the string representation of the 2D matrix
         *
         */
        std::string getString();

    }; // class Matrix

    /**
     * @brief Matrix implementation that perserves the original state by creating
     *        a backup copy of the elements.
     *        Requires more memory space but resets state faster.
     *
     */
    class FastMatrix : public Matrix
    {

    private:
        std::vector<std::vector<int>> mElementsBackup; // copy of the elements

        /**
         * @brief Check if the given position has already been visited.
         *        This is tracked in the elementsBackup matrix.
         *
         * @param position
         * @return true
         * @return false
         */
        bool isProcessed(const position &position) const override;

        /**
         * @brief Mark a given position as already processed.
         *        This is tracked in the elementsBackup matrix.
         *
         * @param position
         */
        void markAsProcessed(const position &position) override;

        /**
         * @brief Resets the original state of the mElementsBackup
         *
         */
        void reset();

    public:
        FastMatrix(const std::vector<std::vector<int>> &elements);

        /**
         * @brief Returns the number of connected figures in the matrix.
         *        Resets the original state afterwards.
         *
         * @return int
         */
        int countFigures() override;

    }; // class FastMatrix

    /**
     * @brief Matrix implementation that perserves the original state by modifying
     *        and later reverting the original state.
     *        Does not require additional memory but resets in O(row*col) complexity.
     *
     */
    class LeanMatrix : public Matrix
    {

    private:
        /**
         * @brief Check if the given position has already been visited.
         *
         * @param position
         * @return true
         * @return false
         */
        bool isProcessed(const position &position) const override;

        /**
         * @brief Mark a given position as already processed.
         *        Temporarily changes mElements.
         *
         * @param position
         */
        void markAsProcessed(const position &position) override;

        /**
         * @brief Resets the original state of the mElements
         *
         */
        void reset();

    public:
        LeanMatrix(const std::vector<std::vector<int>> &elements);

        /**
         * @brief Returns the number of connected figures in the matrix.
         *        Resets the original state afterwards.
         *
         * @return int
         */
        int countFigures() override;

    }; // class LeanMatrix

} // namespace matrix

#endif