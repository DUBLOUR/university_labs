#pragma once
#include<bits/stdc++.h>
using namespace std;


class MeasureDraft 
{
public:
    int tpl;
    string type;
    string op1, op_name1;
    string op2, op_name2;
    string f_normal, f_empty;

    MeasureDraft(int t, string _type, string _op1, string _op_name1, string _op2="", string _op_name2="") {
        tpl = t;
        type = _type;
        op1 = _op1; op_name1 = _op_name1;
        op2 = _op2; op_name2 = _op_name2;
        f_normal = f_empty = "";
    }

    void PrintTests();
    void PrintInstance(bool is_last = false);
};


class Measure 
{
public:
    string type;
    string op1, op_name1, op2, op_name2;
    int (*f_normal)(int) = nullptr;
    int (*f_empty)(int) = nullptr;
    double time,op_per_sec;
    long long iterations;

    Measure(string type_,
            string op1_, string op_name1_, 
            string op2_, string op_name2_,
            int (*f_normal_)(int), int (*f_empty_)(int))
    {
        type = type_; 
        op1 = op1_; op2 = op2_;
        f_normal = f_normal_;
        f_empty = f_empty_;
        time = 0; 
        op_per_sec = 0;
    }


    void run(long long iters = 1000000, int num_of_run = 1);
};



