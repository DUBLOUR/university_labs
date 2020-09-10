#include<bits/stdc++.h>
using namespace std;


struct measure {
    string operation, type;
    double op_per_sec;
};


template<typename Tp>
Tp TestIntPlus(int count_of_iterations, Tp mask) {
    Tp hash = 0;
    for (Tp i=0; i<count_of_iterations; ++i) {
        hash = hash + i;
        hash &= mask;
    }
    return hash;
}


class Gen {
private:
    void template_1(const char* type, const char* type_name, const char* op_name, const char* op) {
    
        char f[] = 
        "Test_%2$s_%4$s%5$s(int count_of_iterations, %1$s mask = (1<<12)-1) {\n"
        "    %1$s hash = 0, now = 0;\n"
        "    for (int i=0; i<count_of_iterations; ++i) {\n"
        "        hash = hash%6$s %3$s now;\n"
        "        now += 1;\n"
        "        hash &= mask;\n"
        "    }\n"
        "    return hash + mask;\n"
        "}\n\n";

        printf(f, type, type_name, op, op_name, "", "");
        printf(f, type, type_name, op, op_name, "_empty", "; //");
        printf("\n");
    }

public:
    Gen(){}

    // void print_func(string type, string type_name, string op_name, string op) {
    //     print_func_(type.c_str(), type.c_str(), op_name.c_str(), op.c_str());
    // }

    void print_func(string type, string op_name, string op) {
        string type_name = type;
        type_name.erase(remove(type_name.begin(), type_name.end(), ' '), type_name.end());
        template_1(type.c_str(), type_name.c_str(), op_name.c_str(), op.c_str());
    }

    
};








void f() {
    
    char f[] = 
"template<typename Tp>\n"
"Tp TestIntPlus(int count_of_iterations, Tp mask) {\n"
"    Tp hash = 0, now = 0;\n"
"    for (int i=0; i<count_of_iterations; ++i) {\n"
"        hash = hash + now;\n"
"        now += 1;\n"
"        hash &= mask;\n"
"    }\n"
"    return hash;\n"
"}\n";

    char f1[] = 
" Test_%1$s_%2$s(int count_of_iterations, %1$s mask = (1<<12)-1) {\n"
"    %1$s hash = 0, now = 0;\n"
"    for (int i=0; i<count_of_iterations; ++i) {\n"
"        hash = hash %3$s now;\n"
"        now += 1;\n"
"        hash &= mask;\n"
"    }\n"
"    return hash;\n"
"}\n";


    Gen().print_func("int", "plus", "+");
    Gen().print_func("long long", "minus", "-");
    Gen().print_func("unsigned long", "xor", "^");
    // printf(f1, "int", "plus", "+");
    // printf(f1, "long long", "minus", "-");
    // printf(f1, "unsigned long", "xor", "^");
}




int main() {
    f();

}

