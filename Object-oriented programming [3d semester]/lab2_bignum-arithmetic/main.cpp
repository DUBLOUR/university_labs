// Has implemented Karatsuba and Toom3 multiplication

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define PB push_back

    
class LongInt
{
private:
public:
    const static int base_size = 4; // Prefer be <= 9
    const static LL base = 10000; // Must be 10^base_size
    static LongInt (*mult_method)(LongInt, LongInt);
    static bool (*prime_method)(LongInt);

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
        assert(only_digits);

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


    LongInt(vector<LL>& a, int l=0, int r=-1) {
        if (r == -1 || r > a.size())
            r = a.size();
        if (r < l || l >= a.size()) 
            l = r = 0;

        is_pos = true;
        v.resize(r-l);
        for (int i=0; i<v.size(); ++i)
            v[i] = a[l + i];
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


    LongInt add(LongInt x, LongInt y) {    
        if (x.is_pos != y.is_pos) {
            bool need_change_sign = false;
            if (less_then(x, y, true)) // |x| < |y|
            {
                if (x.is_pos) { // x > 0, y < 0
                    need_change_sign = true;
                    y.is_pos = true; // x > 0, y > 0
                }
                swap(x, y); // 0 < y < x
            }

            // now: x >= y; we need x - y
            for (int i=0; i<y.v.size(); ++i) {
                x.v[i] -= y.v[i];
                if (x.v[i] < 0) {
                    x.v[i] += base;
                    x.v[i+1] -= 1;
                }
            }
            x.is_pos ^= need_change_sign;
            x.normalize();

            return x;
        }

        LongInt res;
        res.is_pos = x.is_pos;
        res.v.resize(max(x.v.size(), y.v.size())+1);
        res.v[0] = x.v[0] + y.v[0];
        for (int i=1; i<res.v.size(); ++i) {
            res.v[i] = res.v[i-1] / base;
            res.v[i-1] %= base;

            if (i < x.v.size()) res.v[i] += x.v[i];
            if (i < y.v.size()) res.v[i] += y.v[i];
        }

        res.normalize();
        return res;
    }

        // *= base^m
    LongInt shift(int m) {
        assert(m >= 0);
        LongInt res = *this;
        vector<LL> tmp(m);
        res.v.insert(res.v.begin(), tmp.begin(), tmp.end());
        return res;
    }

        // return x < y   (or |x| < |y|)
    bool less_then(LongInt x, LongInt y, bool by_absolute = false) {
        if (x.is_pos != y.is_pos && !by_absolute)
            return !x.is_pos; // x < 0 < y

        if (x.v.size() != y.v.size())
            return (x.v.size() < y.v.size()) ^ (!by_absolute) * (!x.is_pos);

        for (int i=x.v.size()-1; i>=0; --i)
            if (x.v[i] != y.v[i])
                return (x.v[i] < y.v[i]) ^ (!by_absolute) * (!x.is_pos);
        return false;
    }


    bool operator<(LongInt x) {
        return less_then((*this), x);
    }

    bool operator<=(LongInt x) {
        return !less_then(x, (*this));
    }

    bool operator>(LongInt x) {
        return less_then(x, (*this));
    }

    bool operator>=(LongInt x) {
        return !less_then((*this), x);
    }

    bool operator==(LongInt x) {
        return x.is_pos == is_pos && x.v == v;
    }

    bool operator!=(LongInt x) {
        return !((*this) == x);
    }

    LongInt operator+(LongInt x) {
        return add((*this), x);
    }

    void operator+=(LongInt x) {
        (*this) = add((*this), x);
    }

    LongInt operator-() {
        LongInt res = *this;
        res.is_pos ^= 1;
        return res;
    }    

    LongInt operator-(LongInt x) {
        x.is_pos ^= 1;
        return add((*this), x);
    }    

    void operator-=(LongInt x) {
        x.is_pos ^= 1;
        (*this) = add((*this), x);
    }    
    
    LongInt operator*(LongInt x) {
        LongInt y = *this;
        // cout << " -- " << y.v[0] << ' ' << x.v[0] << '\n';
        if (x.v.size() > y.v.size())
            swap(x, y);
        assert(!x.v.empty());
        if (x.v.size() == 1) 
            return y * int(x.is_pos ? x.v[0] : -x.v[0]);

        bool sign = x.is_pos == y.is_pos;
        x.is_pos = true; 
        y.is_pos = true; 
        LongInt res = mult_method(x, y);
        res.is_pos = sign;
        return res;
    }

    LongInt operator*(LL x) {
        if (abs(x) >= base)
            return mult_method(*this, LongInt(x));

        if (!x)
            return LongInt();

        LongInt res;
        res.is_pos = is_pos;
        res.v.resize(v.size()+1);

        if (x < 0)
            res.is_pos ^= 1;

        res.v[0] = x * v[0];
        for (int i=1; i<res.v.size(); ++i) {
            res.v[i] = res.v[i-1] / base;
            res.v[i-1] %= base;
            if (i < v.size())
                res.v[i] += x * v[i];
        }
        
        res.normalize();
        return res;
    }    

    void operator*=(LongInt x) {
        (*this) = (*this) * x;
    }    

    void operator*=(LL x) {
        (*this) = (*this) * x;
    }    

    LongInt operator/(LL x) {
        assert(x != 0);
        LongInt res = (*this);
        if (x < 0) {
            x = -x;
            res.is_pos ^= 1;
        } 
        LL curr = 0;
        for (int i=v.size()-1; i>=0; --i) {
            curr = curr * base + v[i];
            res.v[i] = curr / x;
            curr %= x;
        }
        res.normalize();
        return res;
    }    

    void operator/=(LL x) {
        (*this) = (*this) / x;
    }    


    void operator=(const char x[]) {
        (*this) = LongInt(string(x));
    }    

    bool prime() {
        return prime_method(*this);
    }

};


std::ostream& operator<<(std::ostream &out, LongInt x) {
    return out << x.str();
}


std::istream& operator>>(std::istream &in, LongInt& x) {
    string s;
    cin >> s;
    x = LongInt(s);
    return in;
}



class Multiplex
{
public:
    Multiplex(){}

        // 0: Grade-school multiplication;     O(N^2)
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

        // 1: Karatsuba multiplication;     O(N^1.58)
    static LongInt Karatsuba(LongInt x, LongInt y) // 0 <= x <= y
    {   
        LongInt a,b,c,d,ac,bd,s;
        int m = y.v.size() / 2;

            // x = a * base^m + b
        a = LongInt(x.v, m);
        b = LongInt(x.v, 0, m);

        c = LongInt(y.v, m);
        d = LongInt(y.v, 0, m);
        
            // x*y = ac * base^(2m) + (ad + bc) * base^m + bd
            // x*y = ac * base^(2m) + ((a+b)*(c+d) - ac - bd) * base^m + bd
            // x*y = ac * base^(2m) + (s - ac - bd) * base^m + bd
        ac = a*c;
        bd = b*d;
        s = (a+b) * (c+d);
        
        LongInt res;
        res = ac.shift(2*m);
        res += (s - ac - bd).shift(m);
        res += bd;

        res.normalize();
        return res;
    }


        // return a * x^2 + b * x + c
    LongInt f(LongInt& a, LongInt& b, LongInt& c, int x) {
        if (!x) return c;
        return a*(x*x) + b*x + c;
    }

        // Toom–Cook, O(n^1.46)
    static LongInt Toom3(LongInt x, LongInt y) // 0 <= x <= y
    {
        int dv = max(x.v.size(), y.v.size())/3+1; 
        LongInt m0, m1, m2, n0, n1, n2;
        m0 = LongInt(x.v, 0, dv);  
        m1 = LongInt(x.v, dv, dv*2);
        m2 = LongInt(x.v, dv*2, dv*3);

        n0 = LongInt(y.v, 0, dv);
        n1 = LongInt(y.v, dv, dv*2);
        n2 = LongInt(y.v, dv*2, dv*3);
        
        vector<LongInt> r(5);
        r[0] = m0 * n0;
        for (int i=1; i<5; ++i) 
            r[i] = Multiplex().f(m2, m1, m0, i) * Multiplex().f(n2, n1, n0, i);
        
        vector<vector<LongInt>> s(5);
        s[0] = r;
        for (int i=1; i<5; ++i) {
            s[i].resize(5-i);
            for (int j=0; j<5-i; ++j) 
                s[i][j] = (s[i-1][j+1] - s[i-1][j]) / i;
        }

        vector<vector<LongInt>> ss(4);
        for (int i=0; i<4; ++i) 
            ss[i].resize(5);
        for (int i=0; i<4; ++i)
            ss[i][0] = s[4][0];
        
        for (int i=0; i<4; ++i)
            ss[i][i+1] = s[3-i][0];
        for (int i=1; i<4; ++i)
            for (int j=1; j<=i; ++j)
                ss[i][j] = ss[i-1][j] - (ss[i-1][j-1] * (4-i));

        LongInt res = ss[3][4];
        for (int i=1; i<=4; ++i)
            res += ss[3][4-i].shift(dv*i);
        res.normalize();
        return res;
    }

};



class Primes
{
public:
    Primes(){}

    // https://en.wikipedia.org/wiki/Fermat_primality_test
    static bool Fermat(LongInt x) {
        return true;
    }

    // https://ru.wikipedia.org/wiki/%D0%A2%D0%B5%D1%81%D1%82_%D0%9C%D0%B8%D0%BB%D0%BB%D0%B5%D1%80%D0%B0_%E2%80%94_%D0%A0%D0%B0%D0%B1%D0%B8%D0%BD%D0%B0
    static bool MillerRabin(LongInt x) {
        return true;
    }

    // https://ru.wikipedia.org/wiki/%D0%A2%D0%B5%D1%81%D1%82_%D0%A1%D0%BE%D0%BB%D0%BE%D0%B2%D0%B5%D1%8F_%E2%80%94_%D0%A8%D1%82%D1%80%D0%B0%D1%81%D1%81%D0%B5%D0%BD%D0%B0
    static bool SolovayStrasse(LongInt x) {
        return true;
    }

    // https://ru.wikipedia.org/wiki/%D0%A2%D0%B5%D1%81%D1%82_%D0%90%D0%B3%D1%80%D0%B0%D0%B2%D0%B0%D0%BB%D0%B0_%E2%80%94_%D0%9A%D0%B0%D1%8F%D0%BB%D0%B0_%E2%80%94_%D0%A1%D0%B0%D0%BA%D1%81%D0%B5%D0%BD%D1%8B
    // http://fatphil.org/maths/AKS/
    static bool AKS(LongInt x) {
        return true;
    }


};

LongInt (*LongInt::mult_method)(LongInt, LongInt) = &Multiplex::Stupid;
bool (*LongInt::prime_method)(LongInt) = &Primes::Fermat;

int main() 
{
    LongInt::mult_method = &Multiplex::Karatsuba;
    LongInt::mult_method = &Multiplex::Toom3;

    
    LongInt x,y;
    x = LongInt("-21431974198264721");
    y = "9034795873215";
    // x = LongInt("1111111");
    // y = "11";
    // x = "21";
    // x = "1234567890123456789012";
    // y = "987654321987654321098"; 

    // cout << "-5220\n";
    // cout << "1219326312467611632493760095208585886175176\n";
    // cout << x*2 << " * " << y*3 << '\n';
    // cout << x+x << " * " << y+y+y << '\n';
    // return 0;
    // x = y = 234;
    cout << x << " * " << y << " = \n" << x*y << '\n';
    // cout << "1219326312467611632493760095208585886175176\n";
    // return 0;
    // cout << LongInt("-193633512041332459504923348015") << '\n';
    // cout << 234*234 << '\n';
    cout << LongInt("-193633512041332459504923348015") + LongInt(0) << '\n';
    // cout << (x*y / 5)*5 << '\n';
    // cout << (x*y / 3)*3 << '\n';
    return 0;

    cout << '\n';
    x = 123;
    y = 15;
    cout << (x*y).shift(2) << '\n';

    // cout << LongInt(429) + LongInt(15) << '\n';
    // cout << LongInt(429) - LongInt(15) << '\n';
    // cout << LongInt(-421) - LongInt(1500) << '\n';

    // for (int i=0; i<100; ++i) {
    //     LL x = rand()*2ll - rand();
    //     LL y = rand()*2ll - rand();
    //     cout << x+y << '' << LongInt(x) + LongInt(y) << "\t" << x << ' ' << y << '\n';
    // }
    
}
