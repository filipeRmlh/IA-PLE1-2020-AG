//
// Created by filipe on 17/10/2020.
//

#ifndef IA_AG_PLE1_2020_UTILS_H
#define IA_AG_PLE1_2020_UTILS_H
#include <random>

using namespace std;

auto isDebug = false;

function<double()> randomGen;

void startGenerator () {
    random_device rd {};
    mt19937_64 generator(rd());
    uniform_real_distribution<double> dist{0.0, 1.0};
    randomGen = bind( dist, generator );
}

//get a random integer in the range [min, max[
int getRandomInt(int min=0, int max=1) {
    auto n = randomGen();
    return (int) floor(n * (max - min)) + min;
}

//get a random real in the range [min, max[
double getRandomReal(double min=0, double max=1) {
    auto n = randomGen();
    return n * (max - min) + min;
}

#endif //IA_AG_PLE1_2020_UTILS_H
