#include<bits/stdc++.h>
#include "tests.cpp"
using namespace std;




void draw_row(Measure m, double fastest_op, int bar_max_width = 44) {
    double ratio = m.op_per_sec / fastest_op;
    int percent = min(100, (int) round(ratio * 100));
    int bar_len = min(ratio, 1.0) * bar_max_width * 2;
    
    string bar = "";
    while ((bar_len -= 2) > 1)
        bar += "#";
    if (bar_len == 1)
        bar += ":";
    
    // cout << op_per_sec << ' ' << ratio << ' ' << percent << ' ' << bar_len << '\n'; return;
    
    printf(
        " %-3s %-15s %.3e %-*s%d%%\n", 
        ("=" + m.op1 + m.op2).c_str(), 
        ((m.reg ? "reg " : "") + m.type).c_str(), 
        m.op_per_sec, 
        bar_max_width,
        bar.c_str(),
        percent);
    
}



int main() {

    for (int t=1; t<=5; ++t) {
        for (auto &x : list_of_tests) {
            x.run(10000000, t);
            // cout << x.time << '\t' << x.op_per_sec << '\n';
        }   
        // cout << '\n';
    }

    double best = 0;
    for (auto &x : list_of_tests) 
        best = max(best, x.op_per_sec);

    for (auto &x : list_of_tests) 
        draw_row(x, best);


}
