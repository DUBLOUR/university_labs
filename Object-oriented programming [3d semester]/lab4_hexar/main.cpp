#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "palette.h"
#include "hexagon.h"
using namespace std;
using namespace sf;
typedef pair<double,double> PDD;
#define MP make_pair
#define PB push_back
#define S second
#define F first


const int       SCREEN_W = 720,
                SCREEN_H = 600;
const double    SCREEN_RATIO = (double) SCREEN_W / SCREEN_H,
                SCALE = 1000,
                PI = acosl(-1);
const std::string WINDOW_NAME = "Hexar";


sf::RenderWindow window;
sf::View view;
sf::Font font;

class Hexagon;
class Player;
class Map {
public:
    vector<vector<int>> a;
    vector<Hexagon> drawable;
    int n;

    Map(int sz);
    void draw_map();
    Hexagon& nearest_cell(double px, double py);
    void remove_player(int pid);
    void capture_region(Player& p);
    void handle(Player& p);
    void handle_tail_collision(Player& hunter, Hexagon& cell);
};
class Player {
public:
    static const int head_size = 12;
    static const int tail_size = 4; 
    CircleShape head;
    vector<CircleShape> tail;
    int color;
    int id;
    double x,y;
    bool leave_tail = true;
    int tail_spread = 3;
    int tail_spread_ticker = 0;
    double speed = 1.5*3, speed_bonus = 1.0;
    bool alive = true;

    Player(double sx, double sy, int col);
    void init_head();    
    void start_tail();
    void finish_tail();
    void add_tail_dot();
    void move_direction(double dx, double dy);
    void die();
    void capture_cell(Hexagon& cell);
};



Map::Map(int sz) {
    n = sz;
    a.resize(n, vector<int>(n));
    draw_map();
}


void Map::draw_map() {
    drawable.clear();

    int w = 30, h = 30;
    for (int i=1; i<=w; ++i)
        for (int j=1; j<=h; ++j) {
            drawable.PB(Hexagon(i, j));
            if (i == 1 || i == w || j == 1 || j == h)
                drawable.back().set_state(1);
        }

}


Hexagon& Map::nearest_cell(double px, double py) {
    int x = px / (Hexagon::size * 1.5) + 0.5;
    int y = py / (Hexagon::size * sqrt(3)) + 0.5*(1 - x%2); 

    pair<int,int> p = MP(x,y);
    for (Hexagon &i:drawable)
        if (i.coord == p) 
            return i;
    assert(true);
}



void Map::remove_player(int pid) {
    for (auto& i:drawable)
        if (i.owner == pid)
            i.set_state(0);
}


void Map::capture_region(Player& p) {
    for (Hexagon &i:drawable)
        if (i.owner == p.id)
            i.set_state(2*p.id);
}


void Map::handle(Player& p) {
    Hexagon& cell = nearest_cell(p.x, p.y);

    if (cell.owner == p.id) 
    {
        if (cell.state == 0 && p.leave_tail) { 
            capture_region(p);
            return;
        }
        return;
    }

    if (cell.owner == 0 && cell.state == 1) { /// border of map
        p.die();
        return;
    }

    if (cell.state == 0) {
        p.capture_cell(cell);
        return;
    }

    if (cell.state != 0) {
        handle_tail_collision(p, cell);
        return;
    }
}


void Map::handle_tail_collision(Player& hunter, Hexagon& cell) {

}



Map m(3);



Player::Player(double sx, double sy, int col) {
    static int id_counter = 0;
    id = ++id_counter;
    x = sx;
    y = sy;
    color = col;

    init_head();

    Hexagon& cell = m.nearest_cell(x, y);
    cell.set_state(id*2);

    start_tail();
}

void Player::init_head() {
    head = CircleShape(head_size, 32);
    head.setFillColor(sf::Color(255, 255, 255));
    head.setOutlineThickness(5);
    head.setOutlineColor(list_colors[color]);
    setOriginToCenter(head);
    head.setPosition(x, y);
}

void Player::start_tail() {
    leave_tail = true;
}


void Player::finish_tail() {
    leave_tail = false;
    tail.clear();
}


void Player::add_tail_dot() {
    if (++tail_spread_ticker == tail_spread) {
        tail_spread_ticker = 0;
        CircleShape dot(tail_size, 12);
        dot.setFillColor(list_colors[color]);
        setOriginToCenter(dot);
        dot.setPosition(x, y);
        tail.PB(dot);
    }
}


void Player::move_direction(double dx, double dy) {
    // dx -= x; dy -= y;
    double d = sqrt(dx*dx + dy*dy) / (speed * speed_bonus);
    dx /= d; dy /= d;
    
    x += dx; y += dy;
    head.setPosition(x, y);
    
    if (leave_tail)
        add_tail_dot();
}


void Player::die() {
    alive = false;
    tail.clear();
    m.remove_player(id);
}


void Player::capture_cell(Hexagon& cell) {
    cell.set_state(id*2 + 1);
}






int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(SCREEN_W, SCREEN_H), 
                  WINDOW_NAME, 
                  sf::Style::Default, 
                  settings);  

    window.setVerticalSyncEnabled(true);
    // window.setFramerateLimit(60);
    

    string fontFile = "JetBrains_Mono.ttf";
    font.loadFromFile(fontFile);
    view.reset(sf::FloatRect(0, 0, SCALE * SCREEN_RATIO, SCALE));


    m = Map(3);
    Player p(200, 200, 1);
    vector<Player> other_players;

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
        p.move_direction(
            cursorePosition.x - SCREEN_W * 0.5, 
            cursorePosition.y - SCREEN_H * 0.5);
        
        view.setCenter(p.x, p.y);
        m.handle(p);

        window.clear(Palette::fieldCell);
        window.setView(view);

        for (auto i:m.drawable) {
            i.draw(window);
            // continue;
            // cout << sizeof(i) << '\n';
            // if (i.object.getFillColor() != Palette::fieldCell)
            //     window.draw(i.object);
            // window.draw(i.object2);
        }
        
        
        for (auto i:p.tail) 
            window.draw(i);
        window.draw(p.head);
        
        
        window.display();
    }
    return 0;
}