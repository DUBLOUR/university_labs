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


class LFG: public RanIntGenerator //Lagged Fibonacci generator
{
private:
    int m,x1,x2;
public:
    LFG(int m = 9973, int x1 = 3889, int x2 = 7351);
    int genInt();
};



class ICG: public RanIntGenerator //Inversive congruential generator
{
private:
    int a,c,x,m;
    int inverse(long long x);
public:
    ICG(int a = 1777, int c = 7351, int m = 9973, int x = 3889);
    int genInt();
};



class MMG: public RanIntGenerator //Merge-memes genarator
{
private:
    int a,b,c,m,y,x0;
public:
    MMG(int a = 3889, int b = 1777, int c = 5641, int m = 9973, int x0 = 1301);
    int genInt();
};


class TSL: public RanRealGenerator //Three-sigma limits
{
private:
    double m,sig;
public:
    TSL(double m = 0, double sig = 1);
    double genReal();
};


class MPM: public RanRealGenerator //Marsaglia polar method
{
private:
public:
    MPM();
    double genReal();
};


class RMG: public RanRealGenerator //Ratio mem generator
{
private:
public:
    RMG();
    double genReal();
};



class LMDG: public RanRealGenerator //Log-mem distribution generator
{
private:
    double mu;
public:
    LMDG(double mu = 1);
    double genReal();
};



class AGDM: public RanRealGenerator //Arsen gamma distrubution method
{
private:
    double a;
public:
    AGDM(double a = sqrt(2));
    double genReal();
};
