//
// Created by filipe on 17/10/2020.
//
#ifndef IA_AG_PLE1_2020_FIXEDVALUESCOLLECTION_H
#define IA_AG_PLE1_2020_FIXEDVALUESCOLLECTION_H
#include "Sudoku.h"

//Fixed Positions and values of sudokus with given region size.
//Originally, only with regions <2,2> (sudoku 4x4) and <3,3> (sudoku 9x9).
map<BlockSize, map<Pos, int>> fixedValuesCollection{
    {BlockSize {3,3},
        {
            {Pos{0,3}, 7},
            {Pos{1,0}, 1},
            {Pos{2,3}, 4},
            {Pos{2,4}, 3},
            {Pos{2,6}, 2},
            {Pos{3,8}, 6},
            {Pos{4,3}, 5},
            {Pos{4,5}, 9},
            {Pos{5,6}, 4},
            {Pos{5,7}, 1},
            {Pos{5,8}, 8},
            {Pos{6,4}, 8},
            {Pos{6,5}, 1},
            {Pos{7,2}, 2},
            {Pos{7,7}, 5},
            {Pos{8,1}, 4},
            {Pos{8,6}, 3},
        }
    },
    {BlockSize {2,2},
        {
            {Pos{0,0}, 3},
            {Pos{0,3}, 2},
            {Pos{1,1}, 1},
            {Pos{1,2}, 4},
            {Pos{2,0}, 1},
            {Pos{2,1}, 2},
            {Pos{2,3}, 4},
            {Pos{3,2}, 2},
            {Pos{3,3}, 1},
        }
    },
};

#endif //IA_AG_PLE1_2020_FIXEDVALUESCOLLECTION_H
