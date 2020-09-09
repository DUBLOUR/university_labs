#include "gen.h"
using namespace std;


vector<double> RanGenerator::genVecReal(int n) {
    vector<double> res(n);
    for (int i=0; i<n; ++i)
        res[i] = genReal();
    return res;
}



double RanIntGenerator::genReal() {
    return double(genInt())/maxInt;

}


vector<int> RanIntGenerator::genVecInt(int n) {
    vector<int> res(n);
    for (int i=0; i<n; ++i)
        res[i] = genInt();
    return res;
}

