#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

class Measure
{
public:
    string type;
    bool reg;
    string op1, op_name1, op2, op_name2;
    int (*f_normal)(int) = nullptr;
    int (*f_empty)(int) = nullptr;
    double time,op_per_sec;
    long long iterations;

    Measure(string type_, bool reg_,
            string op1_, string op_name1_, 
            string op2_, string op_name2_,
            int (*f_normal_)(int), int (*f_empty_)(int)) 
    {
        type = type_;
        reg = reg_;
        op1 = op1_;
        op2 = op2_;
        // op_name1 = op_name1_;
        // op_name2 = op_name2_;
        f_normal = f_normal_;
        f_empty = f_empty_;

        time = 0;
        op_per_sec = 0;
    }

    void run(long long iters = 1000000, int num_of_run = 1) {
        iterations = iters;
        high_resolution_clock::time_point t1,t2;
        microseconds all_time, dirt_time;

        t1 = high_resolution_clock::now();
        f_normal(iterations);
        t2 = high_resolution_clock::now();
        all_time = duration_cast<microseconds>(t2 - t1);   

        t1 = high_resolution_clock::now();
        f_empty(iterations);
        t2 = high_resolution_clock::now();
        dirt_time = duration_cast<microseconds>(t2 - t1);

        double now_time = (all_time - dirt_time).count();   
        time = ((num_of_run-1) * time + now_time) / num_of_run;
        op_per_sec = iterations / time * 1e6;

    }

};
