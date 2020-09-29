#include<bits/stdc++.h>
#include "measures.h"
using namespace std;

vector<MeasureDraft> drafts() {
    return vector<MeasureDraft>{
        MeasureDraft(1, "short", "|", "or"),
        MeasureDraft(1, "int", "+", "plus"),
        MeasureDraft(1, "long long", "-", "minus"),
        MeasureDraft(1, "unsigned long", "^", "xor"),
        MeasureDraft(2, "long long", "*", "mult", "+", "plus", false),
        MeasureDraft(2, "long long", "*", "mult", "+", "plus", true),
        MeasureDraft(2, "__int128", "*", "mult", "%", "mod", false),
        MeasureDraft(2, "__int128", "*", "mult", "%", "mod", true),
        MeasureDraft(3, "float", "*", "mult", "/", "div", false),
        MeasureDraft(3, "double", "*", "mult", "/", "div", true),
        MeasureDraft(3, "double", "+", "plus", "/", "div", false),
        MeasureDraft(3, "double", "+", "plus", "/", "div", true),
        MeasureDraft(3, "double", "*", "mult", "-", "minus", true),
        MeasureDraft(3, "double", "*", "mult", "-", "minus", false),
    };
}