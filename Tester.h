//
// Created by filipe on 25/10/2020.
//

#ifndef IA_AG_PLE1_2020_TESTER_H
#define IA_AG_PLE1_2020_TESTER_H

#include <armadillo>
#include "Sudoku.h"
#include "FixedValuesCollection.h"
#include "AG.h"

int Test (int argc, char*argv[]) {

    //Code Here. Replace the code below as you wish.

    auto blockSize = BlockSize{2,2};
    auto content = Mat<int>{{1, 2, 3, 4},
                            {4, 3, 1, 2},
                            {3, 4, 2, 1},
                            {2, 1, 4, 3}};

    set<Pos> fixed = set<Pos>{
            Pos{0,0},
            Pos{0,3},
            Pos{1,1},
            Pos{1,2},
            Pos{2,0},
            Pos{2,1},
            Pos{2,3},
            Pos{3,2},
            Pos{3,3}
    };

    Sudoku sudoku = Sudoku(blockSize, content, fixed);
    sudoku.print();
    cout << "Gn: " << Gn(sudoku) << endl;


    //End

 return 0;
}

#endif //IA_AG_PLE1_2020_FUNCTIONTESTER_H