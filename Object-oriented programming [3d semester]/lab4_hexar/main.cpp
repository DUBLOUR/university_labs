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
    static const int head_size = 18;
    static const int tail_size = 4; 
    CircleShape head;
    vector<CircleShape> tail;
    int id;
    int color;
    int tail_spread = 3;
    int tail_spread_ticker = 0;
    int first_tail_id = 0;
    double x,y;
    double speed = 1.5*3;
    double speed_bonus = 1.0;
    bool leave_tail = true;
    bool alive = true;
    
    Player(double sx, double sy);
    void init_head();    
    void start_tail();
    void finish_tail();
    void add_tail_dot();
    void move_direction(double dx, double dy);
    void die();
    void kill(Player& prey);
    void capture_cell(Hexagon& cell);
    bool collide(Player& enemy);
    void show(RenderWindow& w);
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
        if (i.owner == pid) {
            if (i.prev_owner == pid)
                i.set_state(0);
            else
                i.set_state(i.prev_owner);
        }
}


void Map::capture_region(Player& p) {
    for (Hexagon &i:drawable)
        if (i.owner == p.id)
            i.set_state(2*p.id);
    p.finish_tail();
}


void Map::handle(Player& p) {
    if (!p.alive)
        return;
    Hexagon& cell = nearest_cell(p.x, p.y);
    // cout << "handle " << p.id << ' ' << p.x << ' ' << p.y << '\n';
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


Map m(3);
vector<Player> all_players;
int my_id;

void Map::handle_tail_collision(Player& hunter, Hexagon& cell) {
    for (Player& i:all_players)
        if (cell.owner == i.id)
            hunter.kill(i);
}
    


Player::Player(double sx, double sy) {
    static int id_counter = 0;
    id = ++id_counter;
    x = sx;
    y = sy;
    color = id % (Palette::players.size());
    // cout << id << ' ' << color << ' ' << x << ' ' << y << '\n';
    
    init_head();

    Hexagon& cell = m.nearest_cell(x, y);
    cell.set_state(id*2);
}

void Player::init_head() {
    int thick = 5;
    head = CircleShape(head_size-thick, 32);
    head.setFillColor(sf::Color(255, 255, 255));
    head.setOutlineThickness(thick);
    head.setOutlineColor(Palette::players[color]);
    setOriginToCenter(head);
    head.setPosition(x, y);
}

void Player::start_tail() {
    leave_tail = true;
}


void Player::finish_tail() {
    leave_tail = false;
    first_tail_id = tail.size();
    // tail.clear(); first_tail_id = 0;
}


void Player::add_tail_dot() {
    if (++tail_spread_ticker == tail_spread) {
        tail_spread_ticker = 0;
        CircleShape dot(tail_size, 12);
        dot.setFillColor(Palette::players[color]);
        setOriginToCenter(dot);
        dot.setPosition(x, y);
        tail.PB(dot);
    }
}


void Player::move_direction(double dx, double dy) {
    // dx -= x; dy -= y;
    double d = sqrt(dx*dx + dy*dy);
    if (!d) {
        d = 1;
        dx = 1;
    }
    d /= (speed * speed_bonus);
    dx /= d; dy /= d;
    
    x += dx; y += dy;
    head.setPosition(x, y);
    
    if (leave_tail)
        add_tail_dot();
}


void Player::die() {
    cout << " -- " << id << " has die " << alive << ' ' << (this -> alive) << '\n';
    // return;
    this -> alive = false;
    alive = false;
    finish_tail();
    m.remove_player(id);
    cout << " ++ " << id << " has die " << alive << ' ' << (this -> alive) << '\n';
    
}


void Player::capture_cell(Hexagon& cell) {
    if (alive)
        leave_tail = true;
    if (leave_tail)
        cell.set_state(id*2 + 1);
}


void Player::kill(Player& prey) {
    prey.die();
}


bool Player::collide(Player& enemy) {
    double dx, dy, d;
    dx = x - enemy.x;
    dy = y - enemy.y;
    d = sqrt(dx*dx + dy*dy);
    return d < (Player::head_size*2);
}

void Player::show(RenderWindow& w) {
    for (int i=first_tail_id; i<tail.size(); ++i)
        w.draw(tail[i]);
    // for (auto i:tail) 
    //     w.draw(i);
    w.draw(head);   
}


void collapse_check(Player& a, Player& b) {
    if (!a.alive || !b.alive || a.id == b.id || !a.collide(b))
        return;

    cout << "collide!!\n";
    // Hexagon& hi,hj;
    auto hi = m.nearest_cell(a.x, a.y);
    auto hj = m.nearest_cell(b.x, b.y);
    if (hi.coord == hj.coord) {
        if ((hi.owner == a.id && !hi.state) ||
            (hi.prev_owner == a.id && hi.state)) {
            a.kill(b);
            return;
        }
        if ((hi.owner == b.id && !hi.state) ||
            (hi.prev_owner == b.id && hi.state)) {
            b.kill(a);
            return;
        }   
        a.die();
        b.die();
        return;
    }
    cout << "I don't know what happening...\n";
    a.die();
    b.die();
}


int add_player(int x, int y) {
    all_players.PB(Player(x, y));
    return all_players.size() - 1;
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

    my_id = add_player(200, 200);
    add_player(500, 500);
    
    while (window.isOpen())
    {
        static double t = 2; t += 0.2;

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
        all_players[my_id].move_direction(
            cursorePosition.x - SCREEN_W * 0.5, 
            cursorePosition.y - SCREEN_H * 0.5);
        
        all_players[1].move_direction(sin(t/log(t)), cos(t*t/50/log(t)));
        
        for (Player& i:all_players)
            for (Player& j:all_players)
                collapse_check(i, j);

        for (Player& i:all_players)
            m.handle(i);
        
        view.setCenter(all_players[my_id].x, all_players[my_id].y);
        
        window.clear(Palette::fieldCell);
        window.setView(view);

        for (auto& i:m.drawable)
            i.draw(window);
        
        for (Player& i:all_players)
            i.show(window);
        
        window.display();
    }
    return 0;
}