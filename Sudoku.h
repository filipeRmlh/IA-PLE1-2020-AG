//
// Created by filipe on 17/10/2020.
//
#ifndef IA_AG_PLE1_2020_SUDOKU_H
#define IA_AG_PLE1_2020_SUDOKU_H
#include <armadillo>
#include <list>
#include <set>
#include <random>
#include <utility>
#include "Utils.h"

using namespace std;
using namespace arma;

typedef pair<int, int> BlockSize;
typedef pair<int, int> Pos;

class Sudoku {
private:
    BlockSize blockSize;
    int matrixSide;
    Mat<int> content;
    set<Pos> fixedPos;
    set<Pos> mutablePos;
public:

    explicit Sudoku(BlockSize blockSize) {
        matrixSide = blockSize.first * blockSize.second;
        content = Mat<int>(matrixSide, matrixSide, fill::zeros);
    }

    Sudoku(int blockWidth, int blockHeight): Sudoku( BlockSize(blockWidth, blockHeight) ) { }

    Sudoku(BlockSize blockSize, Mat<int> content, set<Pos> fixedPos) {
        this->blockSize = BlockSize(blockSize);
        matrixSide = blockSize.first * blockSize.second;
        this->content = Mat<int>(content);
        generatePositions(std::move(fixedPos));
    }

    Sudoku(BlockSize blockSize, const map<Pos, int>& fixedValues){
        this->blockSize = blockSize;
        matrixSide = blockSize.first * blockSize.second;
        content = Mat<int>(matrixSide, matrixSide, fill::zeros);
        setFixedValues(fixedValues);
    }

    Pos getBlockPos(Pos pos) const;
    void print();
    void setFixedValues(const map<Pos, int>& fixed);
    void randomFill ();
    int cellOk (Pos cellIndex);
    Mat<int> getBlock(int i, int j);
    int operator[](int n);
    int operator()(int i, int j);
    Mat<int> getContent();
    set<Pos> getMutablePos();
    set<Pos> getFixedPos();
    void generatePositions(set<Pos> fixedPosition);
    BlockSize getBlockSize();
    int getMatrixSide() const;
};

//Get the n-th element considering the flattened matrix
int Sudoku::operator[](int n) {
    return this->content[n];
}

//Get the element at [i,j] position of matrix
int Sudoku::operator()(int i, int j) {
    return this->content(i,j);
}

//Fill sudoku matrix with the given fixed values and store these positions.
void Sudoku::setFixedValues(const map<Pos, int>& fixed) {
    for(const auto elm : fixed){
        auto coords = elm.first;
        auto val = elm.second;
        fixedPos.insert(coords);
        this->content(coords.first, coords.second) = val;
    }
}

//Print colored sudoku matrix
void Sudoku::print() {
    auto cols = content.n_cols;
    auto rows = content.n_rows;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            auto block = getBlockPos(Pos(i,j));
            auto isEvenBlock = (block.first+block.second)%2 == 0;
            auto isFixed = fixedPos.find(Pos(i,j)) != fixedPos.end();
            auto value = content(i,j);
            string fg = isFixed? "34": "31";
            string bg = isEvenBlock? "100": "107";
            cout << "\033[" << bg << ";" << fg << "m";
            cout << "  " << (value==0? " " : to_string(value)) << "  " << "\033[0;0m";
        }
        cout << endl;
    }
}

//Returns the block position of the sudoku matrix given the current position.
Pos Sudoku::getBlockPos(Pos pos) const{
    return {trunc(pos.first/blockSize.first), trunc(pos.second/blockSize.second)};
}

//Store all fixed and mutable positions given the fixed positions.
void Sudoku::generatePositions(set<Pos> fixedPosition) {
    auto newMutablePos = set<Pos>();
    auto newFixedPos = set<Pos>();

    for (int i = 0; i < content.n_rows; i++) {
        for (int j = 0; j < content.n_cols; j++) {
            if(fixedPosition.find(Pos(i, j)) == fixedPosition.end()) {
               newMutablePos.insert(Pos(i,j));
            } else {
                newFixedPos.insert(Pos(i,j));
            }
        }
    }
    fixedPos = newFixedPos;
    mutablePos = newMutablePos;
}

//Fill all mutable positions of the matrix with a random value between 1 and the max value;
void Sudoku::randomFill() {
    const auto cols = content.n_cols;
    const auto rows = content.n_rows;
    auto max = matrixSide+1;
    auto min = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(fixedPos.find(Pos(i,j)) == fixedPos.end()) {
                int generated = getRandomInt(min, max);
                content(i, j) = generated;
                mutablePos.insert(Pos(i,j));
            }
        }
    }
}

//Get a slice of the sudoku corresponding the block at i,j position.
Mat<int> Sudoku::getBlock(int i, int j) {
    return content.submat( i*blockSize.first,j*blockSize.second, size(blockSize.first,blockSize.second) );
}

//Check if the cell at the given index is unique in the column, row, and block.
int Sudoku::cellOk(Pos cellIndex) {
    const Pos blockIndex = getBlockPos(cellIndex);
    const Mat<int> block = getBlock(blockIndex.first, blockIndex.second);
    const Row<int> row = content.row(cellIndex.first);
    const Col<int> col = content.col(cellIndex.second);
    uvec equalsR = find(row == content(cellIndex.first,cellIndex.second));
    uvec equalsC = find(col == content(cellIndex.first,cellIndex.second));
    uvec equalsB = find(block == content(cellIndex.first,cellIndex.second));
    return (equalsR.size() == 1 ? 1 : 0 ) + (equalsC.size() == 1 ? 1 : 0) + (equalsB.size() == 1 ? 1 : 0);
}

//Return the sudoku's matrix content.
Mat<int> Sudoku::getContent() {
    return content;
}

//Return a list containing all mutable cell positions of sudoku.
set<Pos> Sudoku::getMutablePos() {
    return mutablePos;
}

//Return a list containing all fixed cell positions of sudoku.
set<Pos> Sudoku::getFixedPos() {
    return fixedPos;
}

//get width and height of a region/block of sudoku.
BlockSize Sudoku::getBlockSize() {
    return blockSize;
}

//get the size of the matrix side
int Sudoku::getMatrixSide() const {
    return matrixSide;
}

#endif //IA_AG_PLE1_2020_SUDOKU_H
