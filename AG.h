//
// Created by filipe on 18/10/2020.
//

#ifndef IA_AG_PLE1_2020_AG_H
#define IA_AG_PLE1_2020_AG_H

#include <armadillo>
#include <utility>
#include <memory>
#include "Sudoku.h"
#include "FixedValuesCollection.h"
using namespace std;

//Original test function
int Fn(Sudoku sudoku) {
    const auto mutablePos = sudoku.getMutablePos();
    int numberOfMutableCellsOk = 0;
    for(const auto pos : mutablePos) {
        numberOfMutableCellsOk += sudoku.cellOk(pos);
    }
    return numberOfMutableCellsOk;
}

//Translated test function (to be greater than 0).
int Gn(Sudoku sudoku) {
    return Fn(std::move(sudoku)) + 1;
}

//Get the best sudoku and index of a given population.
pair<Sudoku, int> getBest(vector<Sudoku> p, const s32_vec& fns) {
    int bestIdx = fns.index_max();
    return {p[bestIdx], bestIdx};
}

// Get function values of all elements of the population.
s32_vec getPFunctionValues (const vector<Sudoku>& sudokus) {
    auto results = s32_vec (sudokus.size());
    for (int i = 0; i < sudokus.size(); i++) {
        results[i] = Gn(sudokus[i]);
    }
    return results;
}

//Get the roulette vector, with values between 0 and 1 added to the previous values;
vec getRoulette(s32_vec& fns) {
    int totalSum = sum(fns);
    auto r = vec(fns.size());
    float partialSum = 0.0;
    for(int i = 0; i < fns.size(); i++) {
        const auto sliceValue = ((float) fns[i] / (float) totalSum) ;
        r[i] = sliceValue + partialSum;
        partialSum += sliceValue;
    }
    return r;
}

//get intermediate population, given the current population, the roulette and if elitism are enabled.
vector<Sudoku> getIntermediateP(vector<Sudoku> pop, vec roulette, bool elitism = false) {
        auto intermediatePop = vector<Sudoku>();
        auto numElm = roulette.size() - (elitism ? 1 : 0);
        auto scale = ((float)roulette.size()-1) / roulette.size();// Limiting the selected index to roulette.size - 1;
    for(int i = 0; i < numElm; i++) {
        double n = getRandomReal(0,1);
        int pos = (int) (upper_bound(roulette.begin(), roulette.end(), n) - roulette.begin());
        int selectedIndex = (int) (scale * (float) pos);
        intermediatePop.push_back(pop[selectedIndex]);
    }
    return intermediatePop;
}

//Get the initial population
vector<Sudoku> getP0(const int n, BlockSize blockSize, map<Pos, int>& fixedValues) {
    auto  population = vector<Sudoku>();
    for(int i = 0; i < n; i++){
        Sudoku sudoku = Sudoku(blockSize, fixedValues);
        sudoku.randomFill();
        population.push_back(sudoku);
    }
    return population;
}

//Remove a random index from a given index vector passed by reference, and return that index;
int getRandomIndex(vector<int>& v) {
    auto i = getRandomInt(0, v.size());
    int temp = v[i];
    v[i] = v.back();
    v.pop_back();
    return temp;
}

//Get the cut indexes;
set<int> getCuts(int nCuts, int size) {
    auto cuts = set<int>();
    if(nCuts > size-1) {
        throw invalid_argument("nCuts: Maximum: "+to_string(size-1)+". Provided: "+to_string(nCuts));
    }
    vector<int> v(size-1);
    iota (begin(v), end(v), 1);
    cuts.insert(0);
    cuts.insert(size-1);
    while(cuts.size() < nCuts){
        int n = getRandomIndex(v);
        cuts.insert(n);
    }
    return cuts;
}

//Crossover: Merge s1 and s2 slices and produce s3 and s4.
pair<Sudoku, Sudoku> crossover(Sudoku s1, Sudoku s2, int nCuts) {
    auto s1Content = s1.getContent();
    auto s2Content = s2.getContent();
    auto n_cols = s1Content.n_cols;
    auto n_rows = s1Content.n_rows;
    auto n_elem = s1Content.n_elem;
    auto cuts = getCuts(nCuts, n_elem);
    s1Content.reshape(n_elem, 1);
    s2Content.reshape(n_elem, 1);
    auto s3Content = Mat<int>(n_elem, 1);
    auto s4Content = Mat<int>(n_elem, 1);
    auto evenIteration = true;
    for(auto it = cuts.begin(), it2 = next(cuts.begin()); it != prev(cuts.end()); it++, it2++) { // walks through the slices, separating and regrouping them.
        int start = *it;
        int end = *it2;
        auto slice1 = s1Content(span(start, end),0);
        auto slice2 = s2Content(span(start, end),0);

        if(evenIteration) {
            s3Content(span(start,end),0) = slice1;
            s4Content(span(start,end), 0) = slice2;
        } else {
            s3Content(span(start,end),0) = slice2;
            s4Content(span(start,end), 0) = slice1;
        }

        evenIteration = !evenIteration;
    }
    s3Content.reshape(n_rows, n_cols);
    s4Content.reshape(n_rows, n_cols);
    auto s3 = Sudoku(s1.getBlockSize(), s3Content, s1.getFixedPos());
    auto s4 = Sudoku(s1.getBlockSize(), s4Content, s1.getFixedPos());
    return pair<Sudoku, Sudoku>(s3, s4);
}

//Get a collection with all mutable indexes that will suffer mutation.
set<int> getMuts(int nMut, int size) {
    auto muts = set<int>();
    if(nMut > size) {
        throw  invalid_argument("num of Mutations: maximum: " + to_string(size) + ". Provided: " + to_string(nMut) );
    }
    vector<int> v(size) ;
    iota (begin(v), end(v), 0);
    while(muts.size() < nMut){
        int n = getRandomIndex(v);
        muts.insert(n);
    }
    return muts;
}

//Do the mutation in one sudoku
Sudoku mutate(Sudoku s1, int nMut) {
    auto mutablePos = s1.getMutablePos();
    auto size = mutablePos.size();
    auto content = s1.getContent();
    auto mutPos = getMuts(nMut, size);
    auto v1 = vector<Pos>(mutablePos.begin(), mutablePos.end());
    for(auto mut: mutPos){
        auto pos = v1[mut];
        auto value = getRandomInt(1,s1.getMatrixSide()+1);
        content(pos.first, pos.second) = value;
    }

    return Sudoku(s1.getBlockSize(), content, s1.getFixedPos());
}

//Remove a random element from a given population passed by reference, and return that element;
Sudoku getRandomElement(vector<Sudoku>& pop) {
    auto i = getRandomInt(0, pop.size());
    Sudoku temp = pop[i];
    pop[i] = pop[pop.size()-1];
    pop.pop_back();
    return temp;
}

//Do a entire generation of the Genetic Algorithm.
vector<Sudoku> generation(const vector<Sudoku>& pop,
                          s32_vec& fns,
                          const pair <Sudoku, int>& bestSelected,
                          int nCuts,
                          int nMuts,
                          float crossProb,
                          float mutateProb, bool elitism = false ){

    auto roulette = getRoulette(fns);
    auto iPop = getIntermediateP(pop, roulette, elitism);

    auto crossPop = vector<Sudoku>();
    while(!iPop.empty()) {
        auto el1 = getRandomElement(iPop);
        if(iPop.empty()) {
            crossPop.push_back(el1);
            break;
        }
        auto el2 = getRandomElement(iPop);
        auto n = getRandomReal();

        if(n <= crossProb){
            auto cross = crossover(el1, el2, nCuts);
            crossPop.push_back(cross.first);
            crossPop.push_back(cross.second);
        } else {
            crossPop.push_back(el1);
            crossPop.push_back(el2);
        }
    }

    auto mutPop = vector<Sudoku>();
    while(!crossPop.empty()) {
        auto el1 = getRandomElement(crossPop);
        auto n = getRandomReal();
        if(n <= mutateProb){
            auto mut = mutate(el1, nMuts);
            mutPop.push_back(mut);
        } else {
            mutPop.push_back(el1);
        }
    }

    if(elitism) {
        mutPop.push_back(bestSelected.first);
    }

    return mutPop;
}

//Get the mean value of the population function values.
float meanPopFunction(const s32_vec& fns){
    float sum = 0;
    for(auto f : fns) {
        sum += f;
    }
    return sum/fns.size();
}

//Run the entire Genetic algorithm
tuple<vector<Sudoku>, s32_vec, int, float, float> genetic(BlockSize  blockSize, int ncuts, int popSize, int nmuts, float mutProb, float crossProb, int nGenerations, bool doElitism) {

    auto pop = getP0(popSize, blockSize, fixedValuesCollection[blockSize]);

    float meanStart;
    float meanEnd;

    for(auto i=0; i < nGenerations; i++) {
        auto fns = getPFunctionValues(pop);
        auto bestSelected = getBest(pop, fns);
        if(i==0){

            cout << "----- Best Start ------" << endl;
            cout << "Gn: "<< fns[bestSelected.second] << endl;
            if(isDebug) {
                cout << "Sudoku: " << endl;
                bestSelected.first.print();
            }
            cout  << "----------------------" << endl;
            cout << endl;

            meanStart = meanPopFunction(fns);
        }
        pop = generation(pop,fns, bestSelected, ncuts, nmuts, mutProb, crossProb, doElitism);
    }

    auto fns = getPFunctionValues(pop);
    auto roulette = getRoulette(fns);
    auto bestSelected = getBest(pop, fns);

    meanEnd = meanPopFunction(fns);


    cout << "----- Best End ------" << endl;
    cout << "Gn: "<< fns[bestSelected.second] << endl;
    if(isDebug) {
        cout << "Sudoku: " << endl;
        bestSelected.first.print();
    }
    cout << "---------------------"<<  endl;
    cout << endl;


    return {pop, fns, bestSelected.second, meanStart, meanEnd};
}

#endif //IA_AG_PLE1_2020_AG_H
