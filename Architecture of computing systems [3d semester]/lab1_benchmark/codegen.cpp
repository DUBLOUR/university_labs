#include<bits/stdc++.h>
using namespace std;



class Gen {
private:
    void template_1(const char* type, const char* type_name, const char* op, const char* op_name, bool need_register) {
    
        char f[] = 
        "int Test_%7$s%2$s_%4$s%5$s(int count_of_iterations, %1$s mask = (1<<12)-1) {\n"
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
        "int Test_%9$s%2$s_%4$s_%6$s%7$s(int count_of_iterations, %1$s mask = (1<<20)-1) {\n"
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

    string del_space(string s) {
        string res = s;
        res.erase(remove(res.begin(), res.end(), ' '), res.end());
        return res;
    }

public:
    Gen(){}

    pair<string,string> print_func_1(string type, string op, string op_name, bool reg = false) {
        string type_name = del_space(type);
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

};



class Measure {
public:
    int tpl;
    string type;
    bool reg;
    string op1, op_name1;
    string op2, op_name2;
    // (int&) (*f_normal)(...)
    // (int&) (*f_empty)(...)
    string f_normal, f_empty;

    Measure(string _type, string _op1, string _op_name1, string _op2="", string _op_name2="", bool _reg = false) {
        type = _type;
        op1 = _op1;
        op2 = _op2;
        op_name1 = _op_name1;
        op_name2 = _op_name2;
        reg = _reg;
        
        tpl = 1;
        if (op2 == "")
            tpl = 2;
    
        f_normal = f_empty = "";
    }

    void PrintFuncs(int t = 0) {
        if (!t) t = tpl;
        pair<string,string> p;
        if (t == 1) {
            p = Gen().print_func_1(type, op1, op_name1, reg);
        }

        if (t == 2) {
            p = Gen().print_func_2(type, op1, op_name1, op2, op_name2, reg);
        }
        
        f_normal = p.first;
        f_empty = p.second;
    }

    void PrintInit(bool is_last = false) {
// Measure{
//     type, reg
//     op1, op_name1,
//     op2, op_name2,
//     f_normal,
//     f_empty,
// }

        char f[] = 
        "   Measure{\n"
        "       \"%1$s\", %2$s,\n"
        "       \"%3$s\", \"%4$s\",\n"
        "       \"%5$s\", \"%6$s\",\n"
        "       %7$s,\n"
        "       %8$s\n"
        "   }%9$s\n";

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




void f() {

    // Gen().print_func_1("int", "+", "plus");
    // Gen().print_func_1("long long", "-", "minus");
    // Gen().print_func_1("unsigned long", "^", "xor");
    // Gen().print_func_2("__int128", "*", "mult", "%", "mod");
    // Gen().print_func_2("__int128", "*", "mult", "%", "mod", true);
    
    vector<Measure> m = {
        Measure("int", "+", "plus"),
        Measure("long long", "-", "minus"),
        Measure("unsigned long", "^", "xor"),
        Measure("__int128", "*", "mult", "%", "mod"),
        Measure("__int128", "*", "mult", "%", "mod", true)
    };

    for (auto& x:m) {   
        x.PrintFuncs(1);
    }

    for (auto& x:m) {
        x.PrintInit();
    }

    

}




int main() {

    f();

    vector<int> x = {1,2,3};
    map<vector<int>,int> kek;
    kek[x] = 5;
    cout << kek[x];

}

