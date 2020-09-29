#include<bits/stdc++.h>
//#include "MeasureDraft.h"
using namespace std;


class Gen {
private:
    void template_1(const char* type, const char* type_name, const char* op, const char* op_name, bool need_register) {
    
        char f[] = 
        "int Test_%7$s%2$s_%4$s%5$s(int count_of_iterations) {\n"
        "    %1$s mask = (1<<12)-1;\n"
        "    %7$s %1$s hash = 0, now = 0;\n"
        "    for (int i=0; i<count_of_iterations; ++i) {\n"
        "        hash = hash%6$s %3$s now;\n"
        "        now += 1;\n"
        "        hash &= mask;\n"
        "    }\n"
        "    return (int) hash + mask;\n"
        "}\n\n";

        string reg = "";
        if (need_register)
            reg =  "register";

        //         1        2       3    4       5   6    7             
        printf(f, type, type_name, op, op_name, "", "", reg.c_str());
        printf(f, type, type_name, op, op_name, "_empty", "; //", reg.c_str());
        printf("\n");
    }

    void template_2(const char* type, const char* type_name, const char* op1, const char* op1_name, const char* op2, const char* op2_name, bool need_register) {
    
        char f[] = 
        "int Test_%9$s%2$s_%4$s_%6$s%7$s(int count_of_iterations) {\n"
        "    %1$s mask = (1<<20)-1;\n"
        "    %9$s %1$s hash = 1, now = 1, a = 173, b = 9973;\n"
        "    for (int i=0; i<count_of_iterations; ++i) {\n"
        "        hash = (hash+1)%8$s %3$s a %5$s b;\n"
        "        now += 1;\n"
        "        hash &= mask;\n"
        "    }\n"
        "    return (int) hash + mask;\n"
        "}\n\n";

        string reg = "";
        if (need_register)
            reg =  "register";

        //         1        2       3      4       5      6       7   8   9
        printf(f, type, type_name, op1, op1_name, op2, op2_name, "", "", reg.c_str());
        printf(f, type, type_name, op1, op1_name, op2, op2_name, "_empty", "; //", reg.c_str());
        printf("\n");
    }

    void template_3(const char* type, const char* type_name, const char* op1, const char* op1_name, const char* op2, const char* op2_name, bool need_register) {
    
        char f[] = 
        "int Test_%9$s%2$s_%4$s_%6$s%7$s(int count_of_iterations) {\n"
        "    %9$s %1$s hash = 1, now = 1, a = 173, b = 9973;\n"
        "    for (int i=0; i<count_of_iterations; ++i) {\n"
        "        hash = (hash+1)%8$s %3$s a %5$s b;\n"
        "        now += 1;\n"
        "    }\n"
        "    return (int) hash;\n"
        "}\n\n";

        string reg = "";
        if (need_register)
            reg =  "register";

        //         1        2       3      4       5      6       7   8   9
        printf(f, type, type_name, op1, op1_name, op2, op2_name, "", "", reg.c_str());
        printf(f, type, type_name, op1, op1_name, op2, op2_name, "_empty", "; //", reg.c_str());
        printf("\n");
    }

    string del_space(string s) {
        string res = s;
        res.erase(remove(res.begin(), res.end(), ' '), res.end());
        return res;
    }

public:
    Gen(){}

    pair<string,string> print_func_1(string type, string op, string op_name, bool reg = false) {
        string type_name = del_space(type);
        cout << "// " << type_name << ' ' << op << ' ' << op_name << '\n';
        template_1(type.c_str(), type_name.c_str(), op.c_str(), op_name.c_str(), reg);

        pair<string,string> f_names;
        f_names.first = "Test_" + string(reg?"register":"") + type_name + "_" + op_name;
        f_names.second = f_names.first + "_empty";
        return f_names;
    }


    pair<string,string> print_func_2(string type, string op1, string op_name1, string op2, string op_name2, bool reg = false) {
        string type_name = del_space(type);
        template_2(type.c_str(), type_name.c_str(), op1.c_str(), op_name1.c_str(), op2.c_str(), op_name2.c_str(), reg);

        pair<string,string> f_names;
        f_names.first = "Test_" + string(reg?"register":"") + type_name + "_" + op_name1 + "_" + op_name2;
        f_names.second = f_names.first + "_empty";
        return f_names;
    }


    pair<string,string> print_func_3(string type, string op1, string op_name1, string op2, string op_name2, bool reg = false) {
        string type_name = del_space(type);
        template_3(type.c_str(), type_name.c_str(), op1.c_str(), op_name1.c_str(), op2.c_str(), op_name2.c_str(), reg);

        pair<string,string> f_names;
        f_names.first = "Test_" + string(reg?"register":"") + type_name + "_" + op_name1 + "_" + op_name2;
        f_names.second = f_names.first + "_empty";
        return f_names;
    }

};



class MeasureDraft {
public:
    int tpl;
    string type;
    bool reg;
    string op1, op_name1;
    string op2, op_name2;
    string f_normal, f_empty;

    MeasureDraft(int t, string _type, string _op1, string _op_name1, string _op2="", string _op_name2="", bool _reg = false) {
        type = _type;
        op1 = _op1;
        op2 = _op2;
        op_name1 = _op_name1;
        op_name2 = _op_name2;
        reg = _reg;
        
        tpl = t;
        f_normal = f_empty = "";
    }

    
    void PrintFuncs() {
        pair<string,string> p;
        switch (tpl) {
            case 1: 
                p = Gen().print_func_1(type, op1, op_name1, reg); 
                break;
            case 2: 
                p = Gen().print_func_2(type, op1, op_name1, op2, op_name2, reg); 
                break;
            case 3: 
                p = Gen().print_func_3(type, op1, op_name1, op2, op_name2, reg); 
                break;
        }
        
        f_normal = p.first;
        f_empty = p.second;
    }


    void PrintInit(bool is_last = false) {
        char f[] = 
        "   Measure(\n"
        "       \"%1$s\", %2$s,\n"
        "       \"%3$s\", \"%4$s\",\n"
        "       \"%5$s\", \"%6$s\",\n"
        "       %7$s,\n"
        "       %8$s\n"
        "   )%9$s\n";

        printf(f,
            type.c_str(), reg ? "true" : "false",
            op1.c_str(), op_name1.c_str(), 
            op2.c_str(), op_name2.c_str(), 
            f_normal.c_str(), 
            f_empty.c_str(),
            is_last ? "" : ","
        );

    }
};


void print_header() {
    cout << "///This file is auto-generated by `codegen.cpp`\n";
    cout << "///Do not touch!\n\n";
    cout << "#include<bits/stdc++.h>\n";
    // cout << "#include \"tests.h\"\n";
    cout << "#include \"measure.cpp\"\n";
    cout << "using namespace std;\n\n";
}
/*
void f() {

    // Gen().print_func_1("int", "+", "plus");
    // Gen().print_func_1("long long", "-", "minus");
    // Gen().print_func_1("unsigned long", "^", "xor");
    // Gen().print_func_2("__int128", "*", "mult", "%", "mod");
    // Gen().print_func_2("__int128", "*", "mult", "%", "mod", true);
    
    vector<MeasureDraft> m = {
        MeasureDraft("int", "+", "plus"),
        MeasureDraft("long long", "-", "minus"),
        MeasureDraft("unsigned long", "^", "xor"),
        MeasureDraft("__int128", "*", "mult", "%", "mod"),
        MeasureDraft("__int128", "*", "mult", "%", "mod", true)
    };

    print_header();
    for (auto& x:m) {   
        x.PrintFuncs(1);
    }

    cout << "\n\nvector<MeasureDraft> m = {\n";
    for (int i=0; i<m.size(); ++i) {
        m[i].PrintInit(i == m.size()-1);
    }
    cout << "};";

    

}*/




int main() {

    freopen("tests.cpp", "w", stdout);

    vector<MeasureDraft> m = {
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
    };

    print_header();
    for (auto& x:m) {   
        x.PrintFuncs();
    }

    cout << "\n\nvector<Measure> list_of_tests = {\n";
    for (int i=0; i<m.size(); ++i) {
        m[i].PrintInit(i == m.size()-1);
    }
    cout << "};";


}

