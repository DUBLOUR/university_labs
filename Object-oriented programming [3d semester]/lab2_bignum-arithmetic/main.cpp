#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define PB push_back


class LongInt
{
private:
    bool is_pos;
    int base_size = 3;
    // LL base = 1000000000;
    LL base = 1000;
    vector<LL> v;

    void normalize() {
        while (v.size() > 1 && !v.back())
            v.pop_back();
        
        if (v.empty())
            v.PB(0);

        if (v.size() == 1 && !v[0])
            is_pos = true;
    }
public:
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

};

std::ostream& operator<< (std::ostream &out, LongInt& x) {
    return out << x.str();
}

std::istream& operator>> (std::istream &in, LongInt& x) {
    string s;
    cin >> s;
    x = LongInt(s);
    return in;
}


int main() 
{
    cout << LongInt("0").str() << '\n';
    cout << LongInt("10042000").str() << '\n';
    cout << LongInt("0010042000").str() << '\n';
    cout << LongInt("-123456789").str() << '\n';
    cout << LongInt(-13474332).str() << '\n';

    LongInt x;
    cin >> x;
    cout << x << '\n';

}
