#include<bits/stdc++.h>
#include "measures.h"
using namespace std;

vector<MeasureDraft> drafts() {
    return vector<MeasureDraft>{
        // templete, type, operation1, op1_name, operation2, op2_name
        // MeasureDraft(1, "short", "|", "or"),
        // MeasureDraft(1, "int", "+", "plus"),
        // MeasureDraft(1, "long long", "-", "minus"),
        // MeasureDraft(1, "unsigned long", "^", "xor"),
        // MeasureDraft(2, "long long", "*", "mult", "+", "plus"),
        // MeasureDraft(2, "unsigned long long", "*", "mult", "+", "plus"),
        // MeasureDraft(2, "__int128", "*", "mult", "%", "mod"),
        // MeasureDraft(2, "register __int128", "*", "mult", "%", "mod"),
        // MeasureDraft(3, "float", "*", "mult", "/", "div"),
        // MeasureDraft(3, "register double", "*", "mult", "/", "div"),
        // MeasureDraft(3, "double", "+", "plus", "/", "div"),
        // MeasureDraft(3, "register double", "+", "plus", "/", "div"),
        // MeasureDraft(3, "register double", "*", "mult", "-", "minus"),
        // MeasureDraft(3, "double", "*", "mult", "-", "minus"),
            
        MeasureDraft(1, "char", "+", "plus"),
        MeasureDraft(1, "unsigned int", "+", "plus"),
        MeasureDraft(1, "unsigned int", "-", "minus"),
        MeasureDraft(1, "unsigned int", "*", "mult"),
        MeasureDraft(1, "unsigned int", "/", "div"),
        MeasureDraft(1, "unsigned int", "%", "mod"),
        
        MeasureDraft(1, "long long", "^", "xor"),
        MeasureDraft(1, "long long", "+", "plus"),
        MeasureDraft(1, "long long", "-", "minus"),
        MeasureDraft(1, "long long", "*", "mult"),
        MeasureDraft(1, "long long", "/", "div"),
        MeasureDraft(1, "long long", "%", "mod"),

        MeasureDraft(2, "unsigned long long", "*", "mult", "%", "mod"),
        MeasureDraft(2, "__int128", "*", "mult", "%", "mod"),

        MeasureDraft(3, "float", "+", "plus", "*", "mult"),
        MeasureDraft(3, "register float", "+", "plus", "*", "mult"),
        MeasureDraft(3, "float", "*", "mult", "/", "div"),
        MeasureDraft(3, "register float", "*", "mult", "/", "div"),
        MeasureDraft(3, "double", "+", "plus", "*", "mult"),
        MeasureDraft(3, "register double", "+", "plus", "*", "mult"),
        MeasureDraft(3, "double", "*", "mult", "/", "div"),
        MeasureDraft(3, "register double", "*", "mult", "/", "div"),
    };
}