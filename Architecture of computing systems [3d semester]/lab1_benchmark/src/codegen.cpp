/// Need to generate functions and vector with measures to `tests.cpp`
/// Use `drafts.h` for set up functions.

#include<bits/stdc++.h>
#include "measures.h"
#include "drafts.h"
using namespace std;


class Gen {
private:
    void template_1(const char* type, const char* type_name, const char* op, const char* op_name) {
    
        char f[] = 
        "int Test_%2$s_%4$s%5$s(int count_of_iterations) {\n"
        "    %1$s mask = (1<<12)-1;\n"
        "    %1$s hash = 0, now = 1;\n"
        "    for (int i=0; i<count_of_iterations; ++i) {\n"
        "        hash = hash%6$s %3$s now;\n"
        "        now += 1;\n"
        "        hash &= mask;\n"
        "    }\n"
        "    return (int) hash + mask;\n"
        "}\n\n";

        //         1        2       3    4       5   6    
        printf(f, type, type_name, op, op_name, "", "");
        printf(f, type, type_name, op, op_name, "_empty", "; //");
        printf("\n");
    }

    void template_2(const char* type, const char* type_name, const char* op1, const char* op1_name, const char* op2, const char* op2_name) {
    
        char f[] = 
        "int Test_%2$s_%4$s_%6$s%7$s(int count_of_iterations) {\n"
        "    %1$s mask = (1<<20)-1;\n"
        "    %1$s hash = 1, now = 1, a = 173, b = 9973;\n"
        "    for (int i=0; i<count_of_iterations; ++i) {\n"
        "        hash = ((hash+1)%8$s %3$s a) %5$s b;\n"
        "        now += 1;\n"
        "        hash &= mask;\n"
        "    }\n"
        "    return (int) hash + mask;\n"
        "}\n\n";

        //         1        2       3      4       5      6       7   8 
        printf(f, type, type_name, op1, op1_name, op2, op2_name, "", "");
        printf(f, type, type_name, op1, op1_name, op2, op2_name, "_empty", "); //");
        printf("\n");
    }

    void template_3(const char* type, const char* type_name, const char* op1, const char* op1_name, const char* op2, const char* op2_name) {
    
        char f[] = 
        "int Test_%2$s_%4$s_%6$s%7$s(int count_of_iterations) {\n"
        "    %1$s hash = 1, a = 173, b = 9973;\n"
        "    for (int i=0; i<count_of_iterations; ++i) {\n"
        "        hash = ((hash+1)%8$s %3$s a) %5$s b;\n"
        "    }\n"
        "    return (int) hash;\n"
        "}\n\n";

        //         1        2       3      4       5      6       7   8  
        printf(f, type, type_name, op1, op1_name, op2, op2_name, "", "");
        printf(f, type, type_name, op1, op1_name, op2, op2_name, "_empty", "); //");
        printf("\n");
    }

    string del_space(string s) {
        string res = s;
        res.erase(remove(res.begin(), res.end(), ' '), res.end());
        return res;
    }

public:
    Gen(){}

    pair<string,string> print_func_1(string type, string op, string op_name) {
        string type_name = del_space(type);
        template_1(type.c_str(), type_name.c_str(), op.c_str(), op_name.c_str());

        pair<string,string> f_names;
        f_names.first = "Test_" + type_name + "_" + op_name;
        f_names.second = f_names.first + "_empty";
        return f_names;
    }


    pair<string,string> print_func_2(string type, string op1, string op_name1, string op2, string op_name2) {
        string type_name = del_space(type);
        template_2(type.c_str(), type_name.c_str(), op1.c_str(), op_name1.c_str(), op2.c_str(), op_name2.c_str());

        pair<string,string> f_names;
        f_names.first = "Test_" + type_name + "_" + op_name1 + "_" + op_name2;
        f_names.second = f_names.first + "_empty";
        return f_names;
    }


    pair<string,string> print_func_3(string type, string op1, string op_name1, string op2, string op_name2) {
        string type_name = del_space(type);
        template_3(type.c_str(), type_name.c_str(), op1.c_str(), op_name1.c_str(), op2.c_str(), op_name2.c_str());

        pair<string,string> f_names;
        f_names.first = "Test_" + type_name + "_" + op_name1 + "_" + op_name2;
        f_names.second = f_names.first + "_empty";
        return f_names;
    }

};



void MeasureDraft::PrintTests() {
    pair<string,string> p;
    switch (tpl) {
        case 1: 
            p = Gen().print_func_1(type, op1, op_name1); 
            break;
        case 2: 
            p = Gen().print_func_2(type, op1, op_name1, op2, op_name2); 
            break;
        case 3: 
            p = Gen().print_func_3(type, op1, op_name1, op2, op_name2); 
            break;
    }
    
    f_normal = p.first;
    f_empty = p.second;
}


void MeasureDraft::PrintInstance(bool is_last) {
    char f[] = 
    "   Measure(\n"
    "       \"%1$s\",\n"
    "       \"%2$s\", \"%3$s\",\n"
    "       \"%4$s\", \"%5$s\",\n"
    "       %6$s,\n"
    "       %7$s\n"
    "   )%8$s\n";

    printf(f,
        type.c_str(),
        op1.c_str(), op_name1.c_str(), 
        op2.c_str(), op_name2.c_str(), 
        f_normal.c_str(), 
        f_empty.c_str(),
        is_last ? "" : ","
    );

}


void print_header() {
    cout << "///This file is auto-generated by `codegen.cpp`\n";
    cout << "///Please, do not edit without codegen.\n\n";
    cout << "#include<bits/stdc++.h>\n";
    cout << "#include \"measure.cpp\"\n";
    cout << "using namespace std;\n\n";
}


void print_list(vector<MeasureDraft> d) {
    for (auto& x : d) 
        x.PrintTests();

    cout << "\n\nvector<Measure> list_of_tests = {\n";
    for (int i=0; i<d.size(); ++i) {
        bool is_last = i == d.size()-1;
        d[i].PrintInstance(is_last);
    }
    cout << "};";
}


int main() {

    freopen("tests.cpp", "w", stdout);

    print_header();
    print_list(drafts());

}

