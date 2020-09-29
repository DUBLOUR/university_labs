///This file is auto-generated by `codegen.cpp`
///Please, do not edit without codegen.

#include<bits/stdc++.h>
#include "measure.cpp"
using namespace std;

int Test_short_or(int count_of_iterations) {
    short mask = (1<<12)-1;
    short hash = 0, now = 0;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash | now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_short_or_empty(int count_of_iterations) {
    short mask = (1<<12)-1;
    short hash = 0, now = 0;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // | now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_int_plus(int count_of_iterations) {
    int mask = (1<<12)-1;
    int hash = 0, now = 0;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash + now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_int_plus_empty(int count_of_iterations) {
    int mask = (1<<12)-1;
    int hash = 0, now = 0;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // + now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_longlong_minus(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 0;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash - now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_longlong_minus_empty(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 0;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // - now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_unsignedlong_xor(int count_of_iterations) {
    unsigned long mask = (1<<12)-1;
    unsigned long hash = 0, now = 0;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash ^ now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_unsignedlong_xor_empty(int count_of_iterations) {
    unsigned long mask = (1<<12)-1;
    unsigned long hash = 0, now = 0;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // ^ now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_longlong_mult_plus(int count_of_iterations) {
    long long mask = (1<<20)-1;
    long long hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1) * a + b;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_longlong_mult_plus_empty(int count_of_iterations) {
    long long mask = (1<<20)-1;
    long long hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1); // * a + b;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_unsignedlonglong_mult_plus(int count_of_iterations) {
    unsigned long long mask = (1<<20)-1;
    unsigned long long hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1) * a + b;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_unsignedlonglong_mult_plus_empty(int count_of_iterations) {
    unsigned long long mask = (1<<20)-1;
    unsigned long long hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1); // * a + b;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test___int128_mult_mod(int count_of_iterations) {
    __int128 mask = (1<<20)-1;
    __int128 hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1) * a % b;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test___int128_mult_mod_empty(int count_of_iterations) {
    __int128 mask = (1<<20)-1;
    __int128 hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1); // * a % b;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_register__int128_mult_mod(int count_of_iterations) {
    register __int128 mask = (1<<20)-1;
    register __int128 hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1) * a % b;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_register__int128_mult_mod_empty(int count_of_iterations) {
    register __int128 mask = (1<<20)-1;
    register __int128 hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1); // * a % b;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_float_mult_div(int count_of_iterations) {
    float hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1) * a / b;
        now += 1;
    }
    return (int) hash;
}

int Test_float_mult_div_empty(int count_of_iterations) {
    float hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1); // * a / b;
        now += 1;
    }
    return (int) hash;
}


int Test_registerdouble_mult_div(int count_of_iterations) {
    register double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1) * a / b;
        now += 1;
    }
    return (int) hash;
}

int Test_registerdouble_mult_div_empty(int count_of_iterations) {
    register double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1); // * a / b;
        now += 1;
    }
    return (int) hash;
}


int Test_double_plus_div(int count_of_iterations) {
    double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1) + a / b;
        now += 1;
    }
    return (int) hash;
}

int Test_double_plus_div_empty(int count_of_iterations) {
    double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1); // + a / b;
        now += 1;
    }
    return (int) hash;
}


int Test_registerdouble_plus_div(int count_of_iterations) {
    register double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1) + a / b;
        now += 1;
    }
    return (int) hash;
}

int Test_registerdouble_plus_div_empty(int count_of_iterations) {
    register double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1); // + a / b;
        now += 1;
    }
    return (int) hash;
}


int Test_registerdouble_mult_minus(int count_of_iterations) {
    register double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1) * a - b;
        now += 1;
    }
    return (int) hash;
}

int Test_registerdouble_mult_minus_empty(int count_of_iterations) {
    register double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1); // * a - b;
        now += 1;
    }
    return (int) hash;
}


int Test_double_mult_minus(int count_of_iterations) {
    double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1) * a - b;
        now += 1;
    }
    return (int) hash;
}

int Test_double_mult_minus_empty(int count_of_iterations) {
    double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = (hash+1); // * a - b;
        now += 1;
    }
    return (int) hash;
}




vector<Measure> list_of_tests = {
   Measure(
       "short",       "|", "or",
       "", "",
       Test_short_or,
       Test_short_or_empty
   ),
   Measure(
       "int",       "+", "plus",
       "", "",
       Test_int_plus,
       Test_int_plus_empty
   ),
   Measure(
       "long long",       "-", "minus",
       "", "",
       Test_longlong_minus,
       Test_longlong_minus_empty
   ),
   Measure(
       "unsigned long",       "^", "xor",
       "", "",
       Test_unsignedlong_xor,
       Test_unsignedlong_xor_empty
   ),
   Measure(
       "long long",       "*", "mult",
       "+", "plus",
       Test_longlong_mult_plus,
       Test_longlong_mult_plus_empty
   ),
   Measure(
       "unsigned long long",       "*", "mult",
       "+", "plus",
       Test_unsignedlonglong_mult_plus,
       Test_unsignedlonglong_mult_plus_empty
   ),
   Measure(
       "__int128",       "*", "mult",
       "%", "mod",
       Test___int128_mult_mod,
       Test___int128_mult_mod_empty
   ),
   Measure(
       "register __int128",       "*", "mult",
       "%", "mod",
       Test_register__int128_mult_mod,
       Test_register__int128_mult_mod_empty
   ),
   Measure(
       "float",       "*", "mult",
       "/", "div",
       Test_float_mult_div,
       Test_float_mult_div_empty
   ),
   Measure(
       "register double",       "*", "mult",
       "/", "div",
       Test_registerdouble_mult_div,
       Test_registerdouble_mult_div_empty
   ),
   Measure(
       "double",       "+", "plus",
       "/", "div",
       Test_double_plus_div,
       Test_double_plus_div_empty
   ),
   Measure(
       "register double",       "+", "plus",
       "/", "div",
       Test_registerdouble_plus_div,
       Test_registerdouble_plus_div_empty
   ),
   Measure(
       "register double",       "*", "mult",
       "-", "minus",
       Test_registerdouble_mult_minus,
       Test_registerdouble_mult_minus_empty
   ),
   Measure(
       "double",       "*", "mult",
       "-", "minus",
       Test_double_mult_minus,
       Test_double_mult_minus_empty
   )
};