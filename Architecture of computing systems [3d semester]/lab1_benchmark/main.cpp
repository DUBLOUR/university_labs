#include<bits/stdc++.h>
#include "tests.cpp"
using namespace std;

string type_cutter(string s) {
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
        string abbr = type_cutter(type);
        abbreviations.push_back(make_pair(abbr, type));
        type = abbr;
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

    vector<pair<string,string>> abbr;
    for (auto &x : list_of_tests) 
        draw_row(x, abbr, best);

    if (!abbr.empty()) {
        abbr.erase(unique(abbr.begin(), abbr.end()), abbr.end());
        cout << "\nAbbreviations:\n";
        for (auto& x:abbr)
            cout << '\t' << x.first << " = " << x.second << '\n';
    }



}
