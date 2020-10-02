///This file is auto-generated by `codegen.cpp`
///Please, do not edit without codegen.

#include<bits/stdc++.h>
#include "measure.cpp"
using namespace std;

int Test_char_plus(int count_of_iterations) {
    char mask = (1<<12)-1;
    char hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash + now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_char_plus_empty(int count_of_iterations) {
    char mask = (1<<12)-1;
    char hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // + now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_unsignedint_plus(int count_of_iterations) {
    unsigned int mask = (1<<12)-1;
    unsigned int hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash + now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_unsignedint_plus_empty(int count_of_iterations) {
    unsigned int mask = (1<<12)-1;
    unsigned int hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // + now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_unsignedint_minus(int count_of_iterations) {
    unsigned int mask = (1<<12)-1;
    unsigned int hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash - now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_unsignedint_minus_empty(int count_of_iterations) {
    unsigned int mask = (1<<12)-1;
    unsigned int hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // - now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_unsignedint_mult(int count_of_iterations) {
    unsigned int mask = (1<<12)-1;
    unsigned int hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash * now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_unsignedint_mult_empty(int count_of_iterations) {
    unsigned int mask = (1<<12)-1;
    unsigned int hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // * now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_unsignedint_div(int count_of_iterations) {
    unsigned int mask = (1<<12)-1;
    unsigned int hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash / now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_unsignedint_div_empty(int count_of_iterations) {
    unsigned int mask = (1<<12)-1;
    unsigned int hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // / now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_unsignedint_mod(int count_of_iterations) {
    unsigned int mask = (1<<12)-1;
    unsigned int hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash % now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_unsignedint_mod_empty(int count_of_iterations) {
    unsigned int mask = (1<<12)-1;
    unsigned int hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // % now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_longlong_xor(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash ^ now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_longlong_xor_empty(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // ^ now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_longlong_plus(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash + now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_longlong_plus_empty(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // + now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_longlong_minus(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash - now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_longlong_minus_empty(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // - now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_longlong_mult(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash * now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_longlong_mult_empty(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // * now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_longlong_div(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash / now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_longlong_div_empty(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // / now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_longlong_mod(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash % now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_longlong_mod_empty(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // % now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_unsignedlonglong_mult_mod(int count_of_iterations) {
    unsigned long long mask = (1<<20)-1;
    unsigned long long hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1) * a) % b;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_unsignedlonglong_mult_mod_empty(int count_of_iterations) {
    unsigned long long mask = (1<<20)-1;
    unsigned long long hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1)); // * a) % b;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test___int128_mult_mod(int count_of_iterations) {
    __int128 mask = (1<<20)-1;
    __int128 hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1) * a) % b;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test___int128_mult_mod_empty(int count_of_iterations) {
    __int128 mask = (1<<20)-1;
    __int128 hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1)); // * a) % b;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}


int Test_float_plus_mult(int count_of_iterations) {
    float hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1) + a) * b;
        now += 1;
    }
    return (int) hash;
}

int Test_float_plus_mult_empty(int count_of_iterations) {
    float hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1)); // + a) * b;
        now += 1;
    }
    return (int) hash;
}


int Test_registerfloat_plus_mult(int count_of_iterations) {
    register float hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1) + a) * b;
        now += 1;
    }
    return (int) hash;
}

int Test_registerfloat_plus_mult_empty(int count_of_iterations) {
    register float hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1)); // + a) * b;
        now += 1;
    }
    return (int) hash;
}


int Test_float_mult_div(int count_of_iterations) {
    float hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1) * a) / b;
        now += 1;
    }
    return (int) hash;
}

int Test_float_mult_div_empty(int count_of_iterations) {
    float hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1)); // * a) / b;
        now += 1;
    }
    return (int) hash;
}


int Test_registerfloat_mult_div(int count_of_iterations) {
    register float hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1) * a) / b;
        now += 1;
    }
    return (int) hash;
}

int Test_registerfloat_mult_div_empty(int count_of_iterations) {
    register float hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1)); // * a) / b;
        now += 1;
    }
    return (int) hash;
}


int Test_double_plus_mult(int count_of_iterations) {
    double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1) + a) * b;
        now += 1;
    }
    return (int) hash;
}

int Test_double_plus_mult_empty(int count_of_iterations) {
    double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1)); // + a) * b;
        now += 1;
    }
    return (int) hash;
}


int Test_registerdouble_plus_mult(int count_of_iterations) {
    register double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1) + a) * b;
        now += 1;
    }
    return (int) hash;
}

int Test_registerdouble_plus_mult_empty(int count_of_iterations) {
    register double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1)); // + a) * b;
        now += 1;
    }
    return (int) hash;
}


int Test_double_mult_div(int count_of_iterations) {
    double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1) * a) / b;
        now += 1;
    }
    return (int) hash;
}

int Test_double_mult_div_empty(int count_of_iterations) {
    double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1)); // * a) / b;
        now += 1;
    }
    return (int) hash;
}


int Test_registerdouble_mult_div(int count_of_iterations) {
    register double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1) * a) / b;
        now += 1;
    }
    return (int) hash;
}

int Test_registerdouble_mult_div_empty(int count_of_iterations) {
    register double hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1)); // * a) / b;
        now += 1;
    }
    return (int) hash;
}




vector<Measure> list_of_tests = {
   Measure(
       "char",
       "+", "plus",
       "", "",
       Test_char_plus,
       Test_char_plus_empty
   ),
   Measure(
       "unsigned int",
       "+", "plus",
       "", "",
       Test_unsignedint_plus,
       Test_unsignedint_plus_empty
   ),
   Measure(
       "unsigned int",
       "-", "minus",
       "", "",
       Test_unsignedint_minus,
       Test_unsignedint_minus_empty
   ),
   Measure(
       "unsigned int",
       "*", "mult",
       "", "",
       Test_unsignedint_mult,
       Test_unsignedint_mult_empty
   ),
   Measure(
       "unsigned int",
       "/", "div",
       "", "",
       Test_unsignedint_div,
       Test_unsignedint_div_empty
   ),
   Measure(
       "unsigned int",
       "%", "mod",
       "", "",
       Test_unsignedint_mod,
       Test_unsignedint_mod_empty
   ),
   Measure(
       "long long",
       "^", "xor",
       "", "",
       Test_longlong_xor,
       Test_longlong_xor_empty
   ),
   Measure(
       "long long",
       "+", "plus",
       "", "",
       Test_longlong_plus,
       Test_longlong_plus_empty
   ),
   Measure(
       "long long",
       "-", "minus",
       "", "",
       Test_longlong_minus,
       Test_longlong_minus_empty
   ),
   Measure(
       "long long",
       "*", "mult",
       "", "",
       Test_longlong_mult,
       Test_longlong_mult_empty
   ),
   Measure(
       "long long",
       "/", "div",
       "", "",
       Test_longlong_div,
       Test_longlong_div_empty
   ),
   Measure(
       "long long",
       "%", "mod",
       "", "",
       Test_longlong_mod,
       Test_longlong_mod_empty
   ),
   Measure(
       "unsigned long long",
       "*", "mult",
       "%", "mod",
       Test_unsignedlonglong_mult_mod,
       Test_unsignedlonglong_mult_mod_empty
   ),
   Measure(
       "__int128",
       "*", "mult",
       "%", "mod",
       Test___int128_mult_mod,
       Test___int128_mult_mod_empty
   ),
   Measure(
       "float",
       "+", "plus",
       "*", "mult",
       Test_float_plus_mult,
       Test_float_plus_mult_empty
   ),
   Measure(
       "register float",
       "+", "plus",
       "*", "mult",
       Test_registerfloat_plus_mult,
       Test_registerfloat_plus_mult_empty
   ),
   Measure(
       "float",
       "*", "mult",
       "/", "div",
       Test_float_mult_div,
       Test_float_mult_div_empty
   ),
   Measure(
       "register float",
       "*", "mult",
       "/", "div",
       Test_registerfloat_mult_div,
       Test_registerfloat_mult_div_empty
   ),
   Measure(
       "double",
       "+", "plus",
       "*", "mult",
       Test_double_plus_mult,
       Test_double_plus_mult_empty
   ),
   Measure(
       "register double",
       "+", "plus",
       "*", "mult",
       Test_registerdouble_plus_mult,
       Test_registerdouble_plus_mult_empty
   ),
   Measure(
       "double",
       "*", "mult",
       "/", "div",
       Test_double_mult_div,
       Test_double_mult_div_empty
   ),
   Measure(
       "register double",
       "*", "mult",
       "/", "div",
       Test_registerdouble_mult_div,
       Test_registerdouble_mult_div_empty
   )
};