#include<bits/stdc++.h>
#include "measures.h"
using namespace std;
using namespace std::chrono;


void Measure::run(long long iters, int num_of_run) {
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

