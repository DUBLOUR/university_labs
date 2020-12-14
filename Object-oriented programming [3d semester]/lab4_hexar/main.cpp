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

const int SCREEN_W = 640,
          SCREEN_H = 480;
const double PI = acosl(-1);
const std::string WINDOW_NAME = "Hexar";


template<class DRAWABLE>
void setOriginToCenter(DRAWABLE& entity, double x=1, double y=1) {
    sf::FloatRect r = entity.getLocalBounds();
    entity.setOrigin(r.left + x * r.width / 2.f, 
                     r.top + y * r.height / 2.f);
}

sf::Font font;
    

class Map {
public:
    
    class Figure {
    public:
        CircleShape object;
    };

    class Hexagon: private Figure {
    public:
        int state = 0;
        CircleShape object;
        sf::Text object2;

        Hexagon(int x, int y, sf::Color color) {
            state = 0;
            object = CircleShape(Map::cell_size, 6);
            object.setFillColor(color);
            object.setOutlineThickness(2);
            object.setOutlineColor(Palette::fieldBg);
            setOriginToCenter(object);
            object.setRotation(360 / 6 / 2);
            
            double px,py;
            px = x * Map::cell_size * (1 + sin(PI/6));
            py = (y + (x&1)*0.5) * Map::cell_size * sqrt(3);
            // px += SCREEN_W / 2.0;
            // py += SCREEN_H / 2.0;
            object.setPosition(px, py);


            std::ostringstream label; 
            label << "(" << x << ";" << y << ")";
            
            sf::Text text;
            text.setFont(font);
            text.setString(label.str());
            text.setCharacterSize(7);
            text.setFillColor(Color(0, 0, 0, 255));
            text.setStyle(sf::Text::Regular);
            setOriginToCenter(text);
            text.setPosition(px, py);
            object2 = text;

    }


    
        void set_color(sf::Color color) {
            object.setFillColor(color);
        }
    };


    static const int cell_size;
    // RenderWindow& window;
    vector<vector<int>> a;
    vector<Hexagon> drawable;
    int n;
    

    
    Map(int sz) {
        n = sz;
        a.resize(n, vector<int>(n));
        draw_map();
    }

    void draw_map() {
        drawable.clear();

        int w = 19, h = 12;
        for (int i=1; i<=w; ++i)
            for (int j=1; j<=h; ++j)
                drawable.PB(Hexagon(i, j, Palette::fieldCell));

    }
};

const int Map::cell_size = 20;


class Player {
public:
    const int head_size = 15;
    const int tail_size = 4; 
    CircleShape head;
    vector<CircleShape> tail;
    sf::Color color;
    double x,y;
    bool leave_tail = true;
    int tail_spread = 10;
    int tail_spread_ticker = 0;

    Player(double sx, double sy, sf::Color col) {
        x = sx;
        y = sy;
        color = col;

        init_head();
        start_tail();
    }

    void init_head() {
        head = CircleShape(head_size, 32);
        head.setFillColor(sf::Color(255, 255, 255));
        head.setOutlineThickness(6);
        head.setOutlineColor(color);
        setOriginToCenter(head);
        head.setPosition(x, y);
    }

    void start_tail() {
        leave_tail = true;
    }


    void finish_tail() {
        leave_tail = false;
        tail.clear();
    }


    void add_tail_dot() {
        if (++tail_spread_ticker == tail_spread) {
            tail_spread_ticker = 0;
            CircleShape dot(tail_size, 12);
            dot.setFillColor(color);
            setOriginToCenter(dot);
            dot.setPosition(x, y);
            tail.PB(dot);
        }
    }


    void move_direction(double dx, double dy, double speed = 1) {
        dx -= x; dy -= y;
        double d = sqrt(dx*dx + dy*dy) / speed;
        dx /= d; dy /= d;
        
        x += dx; y += dy;
        head.setPosition(x, y);

        if (leave_tail)
            add_tail_dot();
    }
};

// const int Player::head_size = 15;

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    // settings.majorVersion = 2;
    RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), 
                        WINDOW_NAME, 
                        sf::Style::Default, 
                        settings);  
    
    window.setVerticalSyncEnabled(true);
    // window.setFramerateLimit(60);
    
    string fontFile = "JetBrains_Mono.ttf";
    font.loadFromFile(fontFile);
    

    Map m(3);
    Player p(200, 200, Palette::players[0]);
    
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)            
                window.close();
        }
        
        if (sf::Event::KeyReleased) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                window.close();
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
            }
            
            sf::sleep(sf::milliseconds(10));
        }
                

        sf::Vector2i cursorePosition = sf::Mouse::getPosition(window);
        p.move_direction(cursorePosition.x, cursorePosition.y);
        

        window.clear(Palette::fieldBg);
        
        for (auto i:m.drawable) {
            // cout << sizeof(i) << '\n';
            window.draw(i.object);
            window.draw(i.object2);
        }
        
        for (auto i:p.tail) 
            window.draw(i);
        window.draw(p.head);
        
        
        window.display();
    }
    return 0;
}