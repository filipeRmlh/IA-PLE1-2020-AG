//
// Created by filipe on 25/10/2020.
//

#ifndef IA_AG_PLE1_2020_RUN_H
#define IA_AG_PLE1_2020_RUN_H
#include <armadillo>
#include "Sudoku.h"
#include "AG.h"

using namespace std;

//Parsing string in the format "nxm" to BlockSize type
BlockSize parseBlock(const string& s){
    int delimPos = s.find('x');
    auto argvBlockW = s.substr(0, delimPos);
    auto argvBlockH = s.substr(delimPos + 1, s.size() - delimPos + 1);
    return BlockSize {stoi(argvBlockW), stoi(argvBlockH)};
}

//Parse all option parameters
void askParameters(int argc, char *argv[],
                   int *batches,
                   int *nGenerations,
                   BlockSize *blockSize,
                   int *ncuts,
                   int *popSize,
                   int *nmuts,
                   float *mutProb,
                   float *crossProb,
                   bool *doElitism,
                   bool *debug) {
    if(argc < 10 || argc > 11){
        throw invalid_argument("Number of parameters must be 9 or 10. Read the docs");
    }
    int i = 1;
    *batches = stoi(argv[i++]);
    *nGenerations = stoi(argv[i++]);
    *blockSize = parseBlock(argv[i++]);
    *popSize = stoi(argv[i++]);
    *ncuts = stoi(argv[i++]);
    *nmuts = stoi(argv[i++]);
    *mutProb = stof(argv[i++]);
    *crossProb = stof(argv[i++]);
    *doElitism = strcmp(argv[i], "y") == 0 || strcmp(argv[i], "Y") == 0;
    i++;
    if(argc == 11) {
        *debug = strcmp(argv[i],"y") == 0 || strcmp(argv[i],"Y") == 0;
    }
}

//Run the batches of A.G.
int Run (int argc, char*argv[]) {
    /************* Default Values **************/
    //Size of the region/block
    BlockSize blockSize = BlockSize {2,2};
    //Number of cut points for crossover
    int ncuts = 3;
    //Population size
    int popSize = 100;
    //Number of mutation points
    int nmuts = 7;
    //Mutation probability
    float mutProb = 0.03;
    //Crossover probability
    float crossProb = 0.80;
    //Number of generations
    int nGenerations = 100;
    //With elitism (yes/no)
    bool doElitism = false;
    //Number of experiments
    int batches = 10;
    //If is debug execution
    bool debug = true;

    if(argc > 1) {
        askParameters(argc,argv, &batches, &nGenerations, &blockSize, &ncuts, &popSize, &nmuts, &mutProb, &crossProb, &doElitism, &debug);
    }
    isDebug = debug;

    cout << "**********Config**********" << endl;
    cout << "Number of experiments: " << batches << endl;
    cout << "Number of generations: " << nGenerations << endl;
    cout << "Population size: " << popSize << endl;
    cout << "Sudoku Size: " << (blockSize.first*blockSize.second) << "x" << (blockSize.first*blockSize.second) << endl;
    cout << "Block Size: " << blockSize.first << "x" << blockSize.second << endl;
    cout << "Number of crossover cuts: " << ncuts << endl;
    cout << "Number of mutation positions: " << nmuts << endl;
    cout << "Crossover probability: " << crossProb << endl;
    cout << "Mutation probability: " << mutProb << endl;
    cout << "With elitism: " << (doElitism? "Yes" : "No") << endl;
    cout << "With debug enabled: " << (debug? "Yes" : "No") << endl;
    cout << "**************************" << endl;
    cout << endl;

    for(auto i = 0; i < batches; i++) {
        cout << "*** Starting experiment #" << (i + 1) << " ***" <<endl;
        auto result = genetic(blockSize, ncuts, popSize, nmuts, mutProb, crossProb, nGenerations, doElitism);
        cout << "---- Mean ----" << endl;
        cout << "Start: "<< get<3>(result) << endl;
        cout << "End: "<< get<4>(result) << endl;
        cout << "--------------" << endl;
        cout << "*** End of experiment #" << (i + 1) << " ***"<< endl;
        cout << endl;
    }

    return 0;
}
#endif //IA_AG_PLE1_2020_RUN_H
