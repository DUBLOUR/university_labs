#include<bits/stdc++.h>
#include <typeinfo>
using namespace std;
typedef long long LL;
#define PB push_back

    

class LongInt
{
private:
public:
    const static int base_size = 3;
    const static LL base = 1000; // Must be 10^base_size
    static LongInt (*mult_method)(LongInt, LongInt);

    bool is_pos;
    vector<LL> v;
    

    void normalize() {
        while (v.size() > 1 && !v.back())
            v.pop_back();
        
        if (v.empty())
            v.PB(0);

        if (v.size() == 1 && !v[0])
            is_pos = true;
    }


    LongInt(string s) {
        if (s == "")
            s = "0";

        is_pos = true;
        if (s[0] == '+' || s[0] == '-') {
            if (s[0] == '-')
                is_pos = false;
            s.erase(s.begin());
        }

        bool only_digits = true;
        for (char i:s)
            if (!isdigit(i)) {
                only_digits = false;
                return;
            }

        reverse(s.begin(), s.end());
        LL accum = 0;
        LL st = 1;
        for (char i:s) {
            accum += st * (i-'0');
            st *= 10;
            if (st == base) {
                v.PB(accum);
                accum = 0;
                st = 1;
            }
        }
        if (accum > 0 || v.empty())
            v.PB(accum);

        normalize();
    }

    // LongInt(char x[]) {
    //     (*this) = LongInt(string(x));
    // }

    LongInt(long long x = 0) {
        is_pos = true;
        if (x < 0) {
            x = -x;
            is_pos = false;
        }

        while (x) {
            v.PB(x % base);
            x /= base;
        }
        if (v.empty())
            v.PB(0);

        normalize();
    }

    // &LongInt(string s) {
    //     (*this) = LongInt(s);
    // }
    
    // &LongInt(long long x) {
    //     (*this) = LongInt(x);
    // }


    string str(bool show_plus = false) {
        // cout << "# " << v.size() << ": "; for (LL x:v) cout << x << ", "; cout << '\n';
        string res = "";

        for (LL i:v) 
            for (int j=0; j<base_size; ++j) {
                res += char('0' + i%10);
                i /= 10;
            }

        while (res.size() > 1 && res.back() == '0')
            res.pop_back();

        if (!is_pos) 
            res += "-";
        else if (show_plus) 
            res += "+";

        reverse(res.begin(), res.end());
        return res;
    }

    
    void setMultAlgo(LongInt (*method)(LongInt, LongInt)) {
        mult_method = method;
    }


    LongInt mult(LongInt x) {
        return mult_method(*this, x);
    }

    
    LongInt operator*(LongInt x) {
        return mult(x);
    }    


    void operator*=(LongInt x) {
        (*this) = mult(x);
    }    

};


class Multiplex
{
public:
    Multiplex(){}

    static LongInt Stupid(LongInt a, LongInt b) 
    {
        LongInt res;

        res.v.resize(a.v.size() + b.v.size() + 1);
        res.is_pos = !(a.is_pos ^ b.is_pos);
        for (int i=0; i<res.v.size()-1; ++i) 
        {
            LL accum = res.v[i], nxt = 0;
            for (int j=0; j<=i && j<a.v.size(); ++j) {
                if (i-j >= b.v.size()) 
                    continue;
                
                accum += a.v[j] * b.v[i-j];
                if (accum >= LongInt::base) {
                    nxt += accum / LongInt::base;
                    accum %= LongInt::base;
                }
            }
            res.v[i] = accum;
            res.v[i+1] = nxt;
        }
        res.normalize();
        return res;
    }



};



std::ostream& operator<< (std::ostream &out, LongInt x) {
    return out << x.str();
}

std::istream& operator>> (std::istream &in, LongInt& x) {
    string s;
    cin >> s;
    x = LongInt(s);
    return in;
}


LongInt (*LongInt::mult_method)(LongInt, LongInt) = &Multiplex::Stupid;


int main() 
{
    LongInt::mult_method = &Multiplex::Stupid;

    LongInt x,y;
    
    x = string("-21431974198264721");
    y = string("9034795873215");
    cout << x << " * " << y << " = \n" << x*y << '\n';
    cout << LongInt("-193633512041332459504923348015") << '\n';

    x = 123;
    y = 5;
    cout << x*y << '\n';
    
}
