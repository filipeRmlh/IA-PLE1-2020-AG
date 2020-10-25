#include "Run.h"
#include "Tester.h"
#include "Utils.h"

int main(int argc, char* argv[]) {
    startGenerator();//Seed Random generator;
    if(argc > 1 && strcmp(argv[1],"test")==0) {
        cout << "**** Starting Test ****" << endl;
        return Test(argc, argv);
    }
    cout << "**** Starting Algorithm ****" << endl;
    return Run(argc, argv);
}