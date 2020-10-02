#include<bits/stdc++.h>
#include "tests.cpp"
using namespace std;


string get_acronym(string s) {
    string res = "";
    for (int i=0; i<s.size(); ++i)
        if (!i || s[i-1] == ' ')
            res += toupper(s[i]);
    return res;
}


void draw_row(Measure m, vector<pair<string,string>>& abbreviations, double fastest_op, int bar_max_width = 44) {
    double ratio = m.op_per_sec / fastest_op;
    int percent = min(100, (int) round(ratio * 100));
    int bar_len = min(ratio, 1.0) * bar_max_width * 2;
    
    string bar = "";
    while ((bar_len -= 2) > 1)
        bar += "#";
    if (bar_len == 1)
        bar += ":";

    string type = m.type;
    if (type.size() > 12) {
        string abbr = get_acronym(type);
        abbreviations.push_back(make_pair(abbr, type));
        type = abbr;
    }

    static bool need_header = true;
    if (need_header) {
        need_header = false;
        cout << " Op  Type            OpPerSec              [More is faster]             Percent\n";
             // " *-  short           6.597e+08 ########################################### 100%"
    }
    
    printf(
        " %-3s %-15s %.3e %-*s%d%%\n", 
        (m.op1 + m.op2).c_str(), 
        type.c_str(), 
        m.op_per_sec, 
        bar_max_width,
        bar.c_str(),
        percent);
}


int main() {

    int number_experiments = 8;
    int cnt_of_iters = 10000000;

    double expect_time = (double) number_experiments * list_of_tests.size() * cnt_of_iters;
    expect_time *= 15.0 / 1e9;

    cout << fixed << setprecision(1);
    cout << "Testing is running. Expected run time: about " << expect_time << " sec.\n\n";

    for (int t=1; t<=number_experiments; ++t) {
        for (auto &x : list_of_tests) {
            x.run(cnt_of_iters, t);
            // cout << x.time << '\t' << x.op_per_sec << '\n';
        }   
        // cout << '\n';
    }

    
    double fastest = 0;
    for (auto &x : list_of_tests) 
        fastest = max(fastest, x.op_per_sec);

    vector<pair<string,string>> abbr;
    for (auto &x : list_of_tests) 
        draw_row(x, abbr, fastest);

    if (!abbr.empty()) {
        abbr.erase(unique(abbr.begin(), abbr.end()), abbr.end());
        cout << "\nAbbreviations:\n";
        for (auto& x:abbr)
            cout << '\t' << x.first << " = " << x.second << '\n';
    }



}
