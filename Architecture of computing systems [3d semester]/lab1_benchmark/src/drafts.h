#include<bits/stdc++.h>
#include "measures.h"
using namespace std;

vector<MeasureDraft> drafts() {
    return vector<MeasureDraft>{
        MeasureDraft(1, "short", "|", "or"),
        MeasureDraft(1, "int", "+", "plus"),
        MeasureDraft(1, "long long", "-", "minus"),
        MeasureDraft(1, "unsigned long", "^", "xor"),
        MeasureDraft(2, "long long", "*", "mult", "+", "plus"),
        MeasureDraft(2, "unsigned long long", "*", "mult", "+", "plus"),
        MeasureDraft(2, "__int128", "*", "mult", "%", "mod"),
        MeasureDraft(2, "register __int128", "*", "mult", "%", "mod"),
        MeasureDraft(3, "float", "*", "mult", "/", "div"),
        MeasureDraft(3, "register double", "*", "mult", "/", "div"),
        MeasureDraft(3, "double", "+", "plus", "/", "div"),
        MeasureDraft(3, "register double", "+", "plus", "/", "div"),
        MeasureDraft(3, "register double", "*", "mult", "-", "minus"),
        MeasureDraft(3, "double", "*", "mult", "-", "minus"),
    };
}