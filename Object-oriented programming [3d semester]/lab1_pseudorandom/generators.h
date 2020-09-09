#pragma once
#include<bits/stdc++.h>
#include "gen.h"
#include "generators.h"
using namespace std;



class LCG: public RanIntGenerator //Linear congruential generator
{
private:
    int a,c,m,x;
public:
    LCG(int a = 1777, int c = 7351, int m = 9973, int x = 0);
    int genInt();
};


class SCG: public RanIntGenerator //Square congruential generator
{
private:
    int d,a,c,m,x;
public:
    SCG(int d = 1292, int a = 1810, int c = 3102, int m = 4913, int x = 8014);
    int genInt();
};

    
    //Lagged Fibonacci generator
class LFG: public RanIntGenerator 
{
private:
    int m,x1,x2;
public:
    LFG(int m = 9973, int x1 = 3889, int x2 = 7351);
    int genInt();
};


    //Inversive congruential generator
class ICG: public RanIntGenerator 
{
private:
    int a,c,x,m;
    int inverse(long long x);
public:
    ICG(int a = 1777, int c = 7351, int m = 9973, int x = 3889);
    int genInt();
};


    //Merge-memes genarator
class MMG: public RanIntGenerator 
{
private:
    int a,b,c,m,y,x0;
public:
    MMG(int a = 3889, int b = 1777, int c = 5641, int m = 9973, int x0 = 1301);
    int genInt();
};


    //Three-sigma limits
class TSL: public RanRealGenerator 
{
private:
    double m,sig;
public:
    TSL(double m = 0, double sig = 1, RanIntGenerator* g = new LFG());
    double genReal();
};


    //Marsaglia polar method
class MPM: public RanRealGenerator 
{
public:
    MPM(RanIntGenerator* g = new LFG());
    double genReal();
};

    
    //Ratio mem generator
class RMG: public RanRealGenerator 
{
public:
    RMG(RanIntGenerator* g = new LFG());
    double genReal();
};

    
    //Log-mem distribution generator
class LMDG: public RanRealGenerator 
{
private:
    double mu;
public:
    LMDG(double mu = 1, RanIntGenerator* g = new LFG());
    double genReal();
};


    //Arsen gamma distrubution method
class AGDM: public RanRealGenerator 
{
private:
    double a;
public:
    AGDM(double a = sqrt(2), RanIntGenerator* g = new LFG());
    double genReal();
};
