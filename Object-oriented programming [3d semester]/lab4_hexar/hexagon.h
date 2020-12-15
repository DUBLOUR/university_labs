#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "palette.h"
using namespace std;
using namespace sf;
typedef pair<double,double> PDD;
#define MP make_pair
#define PB push_back
#define S second
#define F first


template<class DRAWABLE>
void setOriginToCenter(DRAWABLE& entity, double x=1, double y=1) {
    sf::FloatRect r = entity.getLocalBounds();
    entity.setOrigin(r.left + x * r.width / 2.f, 
                     r.top + y * r.height / 2.f);
}


class Hexagon {
public:
    static const int size = 20;
    int state = 0;
    int owner = 0;
    int prev_owner = 0;
    pair<int,int> coord;
    
    Hexagon(int x, int y) {
        coord = MP(x,y);
        owner = 0;
        state = 0;
        prev_owner = 0;
    }

    void draw(RenderWindow& w) {
        Color c;
        if (!owner) {
            if (!state)
                c = Palette::fieldCell;
            else
                c = Palette::fieldBorder;
        } else {
            c = Palette::players[owner % Palette::players.size()];
            if (state == 1)
                c.a = Palette::non_captured_opacity;
        }
        
        CircleShape object(Hexagon::size, 6);
        object.setFillColor(c);
        object.setOutlineThickness(1.5);
        object.setOutlineColor(Palette::fieldBg);
        setOriginToCenter(object);
        object.setRotation(360 / 6 / 2);
        
        double px,py;
        px = Hexagon::size * coord.F * 1.5;
        py = Hexagon::size * (coord.S + (coord.F&1)*0.5) * sqrt(3);
        object.setPosition(px, py);   

        w.draw(object);
    }


    void set_state(int own) {
        if (owner != own/2)
            prev_owner = owner;
        owner = own / 2;
        state = own % 2;
    }
};

