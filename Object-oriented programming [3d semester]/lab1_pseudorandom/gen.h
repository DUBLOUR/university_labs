#pragma once
#include<bits/stdc++.h>
using namespace std;


class RanGenerator
{
public:
    virtual double genReal()=0;
    vector<double> genVecReal(int n);
};  


class RanIntGenerator: public RanGenerator
{
protected:
    int maxInt;
public:
    virtual int genInt()=0;
    virtual double genReal();
    vector<int> genVecInt(int n);
};  


class RanRealGenerator: public RanGenerator
{
protected:
    RanGenerator* g;
public:
    virtual double genReal()=0;
    vector<double> genVecReal(int n);
};  
