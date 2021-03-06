#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
typedef pair<double,double> PDD;
#define MP make_pair
#define PB push_back
#define S second
#define F first


vector<PDD> gen_random_dots(int n, int d = 50) {
    vector<PDD> res(n);
    for (PDD& x:res) {
        x.F = rand() % (SCREEN_W - 2*d) + d;
        x.S = rand() % (SCREEN_H - 2*d) + d;
    }
    return res;
}


vector<CircleShape> gen_vert(vector<PDD>& dots) {
    vector<CircleShape> res(dots.size());
    double r = 5;
    Color color(150, 50, 250);

    int pointCount = 30;
    for (int i=0; i<dots.size(); ++i) {
        CircleShape c(r, pointCount);
        c.setFillColor(color);
        c.setOutlineThickness(2);
        c.setOutlineColor(sf::Color(0, 0, 0));
        setOriginToCenter(c);
        c.setPosition(dots[i].F, dots[i].S);
        
        res[i] = c;
    }
    return res;
}


class HullVisualiser {
private:
    int step;
    vector<int> up,dn;
    vector<pair<int,int>> events;
    vector<bool> on_hull;
public:
    int cnt_dot;
    vector<PDD> dots;
    vector<CircleShape> vertices;
    VertexArray hull;


    HullVisualiser(int count_point, int algo) {
        cnt_dot = count_point;
        up.clear();
        dn.clear();

        dots = gen_random_dots(count_point);
        vertices = gen_vert(dots);
        events = ConvexHull(dots, algo).events;
        step = 0;
    }

    void gen_hull_part() {
        vector<int> ids = dn;
        // ids.pop_back();
        reverse(ids.begin(), ids.end());
        ids.insert(ids.end(), up.begin(), up.end());

        // cout << ":: "; for (int i:ids) cout << i << ' '; cout << "::\n";

        int n = ids.size();
        hull.clear();
        hull = VertexArray(sf::LineStrip, n);
        for (int i=0; i<n; ++i) {
            hull[i].position = sf::Vector2f(dots[ids[i]].F, dots[ids[i]].S);
            hull[i].color = Color(255*(1-i%2), 0, 255*(i%2));
        }

        on_hull.clear();
        on_hull.resize(cnt_dot, false);
        for (int i:ids)
            on_hull[i] = true;

        for (int i=0; i<cnt_dot; ++i)
            if (on_hull[i])
                vertices[i].setFillColor(sf::Color(250, 50, 100));
            else
                vertices[i].setFillColor(sf::Color(150, 50, 250));

    }


    bool next() {
        if (step == events.size())
            return false;

        auto now = events[step++];
        if (now.F == +1) up.PB(now.S);
        if (now.F == -1) up.pop_back();

        if (now.F == +2) dn.PB(now.S);
        if (now.F == -2) dn.pop_back();
        gen_hull_part();

        return step < events.size();
    }


    bool prev() {
        if (!step)
            return false;

        auto now = events[--step];
        if (now.F == -1) up.PB(now.S);
        if (now.F == +1) up.pop_back();

        if (now.F == -2) dn.PB(now.S);
        if (now.F == +2) dn.pop_back();
        gen_hull_part();

        return step;
    }
};

