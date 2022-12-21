/**
 * @file matrix_test.cc
 * @author Marijan Kozic (marijan@todah.hr)
 * @brief Unit tests for the Matrix class
 * @version 0.1
 * @date 2022-12-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../src/Matrix.h"
#include <gtest/gtest.h>

namespace
{

    /**
     * For the sake of brevity, all classes are tested simultaneously.
     *
     */

    TEST(Matrix, EmptyElements)
    {

        std::vector<std::vector<int>> v(0, std::vector<int>(0));

        auto mm = matrix::Matrix(v);
        auto fm = matrix::FastMatrix(v);
        auto lm = matrix::LeanMatrix(v);

        EXPECT_EQ(0, mm.countFigures());
        EXPECT_EQ(0, fm.countFigures());
        EXPECT_EQ(0, lm.countFigures());
    }

    TEST(Matrix, NoFigures)
    {
        std::vector<std::vector<int>> v = {{0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0}};

        auto mm = matrix::Matrix(v);
        auto fm = matrix::FastMatrix(v);
        auto lm = matrix::LeanMatrix(v);

        EXPECT_EQ(0, mm.countFigures());
        EXPECT_EQ(0, fm.countFigures());
        EXPECT_EQ(0, lm.countFigures());
    }

    TEST(Matrix, NoEmptyElements)
    {
        std::vector<std::vector<int>> v = {{1, 1, 1, 1, 1},
                                           {1, 1, 1, 1, 1},
                                           {1, 1, 1, 1, 1},
                                           {1, 1, 1, 1, 1},
                                           {1, 1, 1, 1, 1}};

        auto mm = matrix::Matrix(v);
        auto fm = matrix::FastMatrix(v);
        auto lm = matrix::LeanMatrix(v);

        EXPECT_EQ(1, mm.countFigures());
        EXPECT_EQ(1, fm.countFigures());
        EXPECT_EQ(1, lm.countFigures());
    }

    TEST(Matrix, OneBorderElement)
    {
        std::vector<std::vector<int>> v = {{0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 1},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0}};

        auto mm = matrix::Matrix(v);
        auto fm = matrix::FastMatrix(v);
        auto lm = matrix::LeanMatrix(v);

        EXPECT_EQ(1, mm.countFigures());
        EXPECT_EQ(1, fm.countFigures());
        EXPECT_EQ(1, lm.countFigures());
    }

    TEST(Matrix, OneCornerElement)
    {
        std::vector<std::vector<int>> v = {{0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {1, 0, 0, 0, 0}};

        auto mm = matrix::Matrix(v);
        auto fm = matrix::FastMatrix(v);
        auto lm = matrix::LeanMatrix(v);

        EXPECT_EQ(1, mm.countFigures());
        EXPECT_EQ(1, fm.countFigures());
        EXPECT_EQ(1, lm.countFigures());
    }

    TEST(Matrix, ThreeElements)
    {
        std::vector<std::vector<int>> v = {{1, 0, 0, 0, 0},
                                           {1, 0, 1, 1, 0},
                                           {0, 1, 0, 1, 1},
                                           {0, 1, 1, 1, 0},
                                           {0, 0, 0, 0, 1}};

        auto mm = matrix::Matrix(v);
        auto fm = matrix::FastMatrix(v);
        auto lm = matrix::LeanMatrix(v);

        EXPECT_EQ(3, mm.countFigures());
        EXPECT_EQ(3, fm.countFigures());
        EXPECT_EQ(3, lm.countFigures());
    }

    TEST(Matrix, TwoFiguresNonSquareMatrix)
    {
        std::vector<std::vector<int>> v = {{0, 0, 1},
                                           {0, 1, 1},
                                           {1, 0, 0},
                                           {1, 0, 0},
                                           {0, 0, 0}};

        auto mm = matrix::Matrix(v);
        auto fm = matrix::FastMatrix(v);
        auto lm = matrix::LeanMatrix(v);

        EXPECT_EQ(2, mm.countFigures());
        EXPECT_EQ(2, fm.countFigures());
        EXPECT_EQ(2, lm.countFigures());
    }

    TEST(Matrix, CheckeredBoardElements)
    {
        std::vector<std::vector<int>> v = {{1, 0, 1, 0, 1},
                                           {0, 1, 0, 1, 0},
                                           {1, 0, 1, 0, 1},
                                           {0, 1, 0, 1, 0},
                                           {1, 0, 1, 0, 1}};

        auto mm = matrix::Matrix(v);
        auto fm = matrix::FastMatrix(v);
        auto lm = matrix::LeanMatrix(v);

        EXPECT_EQ(13, mm.countFigures());
        EXPECT_EQ(13, fm.countFigures());
        EXPECT_EQ(13, lm.countFigures());
    }
} // namespace