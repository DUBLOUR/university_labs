#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LD;
#define PB push_back
#define MP make_pair


template <typename T1, typename T2>
ostream& operator << (ostream& out, pair<T1, T2>& p) {
    out << p.F << " " << p.S; 
    return out;
}



const int   N = 1e5 + 10,
            INF = 1e9,
            MOD = 1e9 + 7;
const LL    INFL = 1e18,
            MODL = 1e9 + 7;
const LD    EPS = 1e-8,
            PI = acosl(-1);


bool prime(int n) {
    if (n < 2)
        return false;

    for (int i=2; i*i<=n; ++i)
        if (n%i == 0)
            return false;
    return true;
}






vector<int> g0() {
    vector<int> res={0,0,1,1,2,2,3,3};
    return res;
}
 
vector<int> g1() {
    vector<int> res={0,12,3};
    return res;
}

vector<int> g2(...) {
    vector<int> res;
    return res;
}


int main()
{

    auto (*p)(...) = &g2;
    auto res = p(1);
    cout << res.size() << '\n';

    // vector< vector<int>(*)() > vg = {&g0, &g1, &g2}; 
    // for (int i=0; i<vg.size(); ++i)
    //     cout << i << '\t' << vg[i]().size() << '\n';

    return 0;
    






}
