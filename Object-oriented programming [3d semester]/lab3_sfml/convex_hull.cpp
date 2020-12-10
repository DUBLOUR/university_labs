#include <bits/stdc++.h>
using namespace std;
#define MP make_pair
#define PB push_back
#define S second
#define F first


class ConvexHull {
private:
    const double eps = 1e-6;
public:
    vector<pair<double,double>> v;
    // vector<pair<double,double>,int> a;
    vector<int> hull;
    vector<pair<int,int>> events;

    ConvexHull(vector<pair<double, double>> _v){
        v = _v;
        hull.clear();
        events.clear();
    
        // runGraham();
        runJarvis();
    }

    int sign(pair<double,double> a, pair<double,double> b, pair<double,double> c) {
        double s = 
            a.F * (b.S - c.S) +
            b.F * (c.S - a.S) + 
            c.F * (a.S - b.S);
        if (s < -eps) 
            return -1;
        if (s > +eps) 
            return +1;
        return 0;

    }

    void runGraham(){
        vector<pair<pair<double,double>,int>> a(v.size());
        for (int i=0; i<v.size(); ++i)
            a[i] = MP(v[i], i);

        hull.clear();
        if (a.size() == 1) {
            hull.PB(a[0].S);
            return;
        }

        sort(a.begin(), a.end());

        auto p_st = a.front(),
             p_fn = a.back();
        vector<pair<pair<double,double>,int>> up,dn;
        up.PB(p_st);
        dn.PB(p_st);
        events.PB(MP(+1, p_st.S));
        events.PB(MP(+2, p_st.S));

        for (int i=1; i<a.size(); ++i) {
            if (i == a.size()-1 || sign(p_st.F, a[i].F, p_fn.F) < 0) {
                while (up.size() >= 2 && sign(up[up.size()-2].F, up.back().F, a[i].F) >= 0) {
                    events.PB(MP(-1, up.back().S));
                    up.pop_back();
                }
                up.PB(a[i]);
                events.PB(MP(+1, a[i].S));
            }
            if (i == a.size()-1 || sign(p_st.F, a[i].F, p_fn.F) > 0) {
                while (dn.size() >= 2 && sign(dn[dn.size()-2].F, dn.back().F, a[i].F) <= 0) {
                    events.PB(MP(-2, dn.back().S));
                    dn.pop_back();
                }
                dn.PB(a[i]);
                events.PB(MP(+2, a[i].S));
            }
        }

        hull.reserve(up.size() + dn.size() - 2);
        for (auto i:up)
            hull.PB(i.S);
        for (auto i=dn.size()-1; i; --i)
            hull.PB(dn[i].S);

    
    }

    
    // https://neerc.ifmo.ru/wiki/index.php?title=%D0%A1%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5_%D0%B2%D1%8B%D0%BF%D1%83%D0%BA%D0%BB%D1%8B%D0%B5_%D0%BE%D0%B1%D0%BE%D0%BB%D0%BE%D1%87%D0%BA%D0%B8:_%D0%94%D0%B6%D0%B0%D1%80%D0%B2%D0%B8%D1%81,_%D0%93%D1%80%D1%8D%D1%85%D0%B5%D0%BC,_%D0%AD%D0%BD%D0%B4%D1%80%D1%8E,_%D0%A7%D0%B5%D0%BD,_QuickHull#.D0.90.D0.BB.D0.B3.D0.BE.D1.80.D0.B8.D1.82.D0.BC_.D0.94.D0.B6.D0.B0.D1.80.D0.B2.D0.B8.D1.81.D0.B0
    void runJarvis(){
        int n = v.size();
        vector<pair<pair<double,double>,int>> a(n);
        for (int i=0; i<n; ++i)
            a[i] = MP(v[i], i);

        hull.clear();
        if (n == 1) {
            hull.PB(a[0].S);
            return;
        }

        for (int i=1; i<n; ++i)
            if (a[i] < a[0])
                swap(a[i], a[0]);
        
        hull.PB(a[0].S);
        events.PB(MP(+1,a[0].S));
        
        int k = 0;
        while (k < n) {
            ++k;
            events.PB(MP(1,a[k].S));
            for (int j=k; j<n; ++j)
                if (sign(a[k-1].F, a[k].F, a[j].F) < 0) {
                    events.PB(MP(-1,events.back().S));
                    swap(a[k], a[j]);
                    events.PB(MP(1,a[k].S));
                }

            
            if (sign(a[k-1].F, a[k].F, a[0].F) < 0) {
                events.PB(MP(-1,a[k].S));
                break;
            }

            hull.PB(a[k].S);
            // events.PB(MP(1,a[k].S));
        } 
        events.PB(events.front());
            

    }


};

/*
int main() 
{
    srand(time(NULL));
    int n = 20;
    int square = 300;

    vector<pair<double, double>> _v(n);
    for (int i=0; i<n; ++i)
        _v[i] = MP(rand() % square, rand() % square);
    ConvexHull c(_v);

    for (int i=0; i<n; ++i)
        cout << i << '\t' << c.v[i].F << ' ' << c.v[i].S << '\n';
    cout << '\n';
    for (int i=0; i<n; ++i)
        cout << c.v[i].F << ' ' << c.v[i].S << ' ' << char(i+'A') << '\n';
    cout << '\n';
    
    cout << "Polygon\n";
    for (int i:c.hull)
        cout << c.v[i].F << ' ' << c.v[i].S << '\n';
    cout << "...\n";

    for (int i:c.hull)
        cout << i << ' ';
    cout << '\n';
    
}
*/