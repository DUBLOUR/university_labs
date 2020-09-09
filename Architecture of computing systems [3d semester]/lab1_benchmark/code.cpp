#include<bits/stdc++.h>
using namespace std;


struct measure {
    string operation, type;
    double op_per_sec;
};


void draw_row(measure m, double fastest_op, int bar_max_width = 44) {
    double ratio = m.op_per_sec / fastest_op;
    int percent = round(ratio * 100);
    int bar_len = min(ratio, 1.0) * bar_max_width * 2;
    
    string bar = "";
    while (bar_len -= 2)
        bar += "#";
    if (bar_len == 1)
        bar += ":";
    while (bar.size() < bar_max_width) 
        bar += " ";

    printf(
        " %-3s  %-12s  %.5e %s%d%%\n", 
        m.operation.c_str(), 
        m.type.c_str(), 
        m.op_per_sec, 
        bar.c_str(),
        percent);
    
}

 
// + int    7.825654е07 ХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХХ    100%
// / double 4.094732e06 ХХХ 5%


int main() {
    measure m;
    m.operation = "+";
    m.type = "int";
    m.op_per_sec = 7.825654e7;

    measure k = {"=/*", "long double", 4.094732e06};

    draw_row(m, 7.825654e7);
    draw_row(k, 7.825654e7);
    draw_row({"/=", "long long", 5e7}, 7.825654e7);

}
