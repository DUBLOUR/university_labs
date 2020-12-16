#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
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
const std::string WINDOW_NAME = "Hexar SERVER";


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
    Player();
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
    void move(PDD p);
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
    

Player::Player() {
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

void Player::move(PDD p) {
    x = p.F; y = p.F;
    head.setPosition(x, y);
    
    if (leave_tail)
        add_tail_dot();
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

int rand_int(int l, int r) {
    return rand() % (r-l+1) + l;
}

int add_player(int x = 0, int y = 0) {
    if (!x && !y) {
        x = rand_int(100, 900);
        y = rand_int(100, 900);
    }
    all_players.PB(Player(x, y));
    return all_players.size() - 1;
}



/*

struct PMovePack {
    sf::Uint32 id;
    double x,y;

    PMovePack(int _id=0, double _x=0, double _y=0) {
        id = _id;
        x = _x;
        y = _y;   
    }
};

std::ostream& operator <<(std::ostream& os, const PMovePack& p) {
    return os << p.id << p.x << p.y;
}

sf::Packet& operator <<(sf::Packet& packet, const PMovePack& p) {
    return packet << p.id << p.x << p.y;
}

sf::Packet& operator >>(sf::Packet& packet, PMovePack& p) {
    return packet >> p.id >> p.x >> p.y;
}

*/


struct MovePack {
    vector<pair<sf::Uint32,PDD>> v; 

    MovePack(int n=0, int id=0, double x=0, double y=0) {
        v.resize(n);
        if (n) {
            v[0].F = id;
            v[0].S = MP(x,y);
        }
    }
};

std::ostream& operator <<(std::ostream& os, const MovePack& p) {
    os << "(" << p.v.size() << "): ";
    for (auto& i:p.v)
        os << "{" << i.F << ' ' << i.S.F << ' ' << i.S.S << "} ";
    return os;
}

sf::Packet& operator <<(sf::Packet& packet, const MovePack& p) {
    packet << (sf::Uint32) p.v.size();
    for (auto& i:p.v)
        packet << i.F << i.S.F << i.S.S;
    return packet;    
}

sf::Packet& operator >>(sf::Packet& packet, MovePack& p) {
    sf::Uint32 n;
    packet >> n;
    p.v.resize(n);
    for (auto& i:p.v)
        packet >> i.F >> i.S.F >> i.S.S;
    return packet;    
}



class Server {
public:
    class Client {
    public:
        sf::IpAddress ip;
        int port;
        int pid;

        Client(sf::IpAddress _ip, int _port) {
            ip = _ip;
            port = _port;
            // pid = _pid;
        }
    };

    int listen_port;
    vector<Client> clients;
    sf::UdpSocket socket_r,socket_s;
    mutex mutlock;

    Server(int port = 0) {
        if (!port)
            return;

        listen_port = port;
        socket_r.bind(listen_port);
    }

    void join_client(sf::IpAddress ip, int port) {
        cout << ip << ' ' << port << " has joined!" << endl;
        mutlock.lock();
        clients.PB(Client(ip, port));
        mutlock.unlock();
        add_player();
        send_all();

        
    }

    void listen_all() {
        mutlock.lock();
        cout << "listened:\n";
        IpAddress sender; 
        unsigned short port; 
        MovePack message; 
        Packet packet;

        socket_r.receive(packet, sender, port);
        packet >> message;
        cout << "(" << sender << ":" << port << ") > " << message << endl;

        // bool remembered = false;
        // for (auto& i:clients)
        //     if (i.ip == sender && i.port == port) {
        //         remembered = true;
        //         break;
        //     }

        if (message.v.empty()) 
            join_client(sender, port);
        else {
            int id = message.v[0].F;
            PDD p = message.v[0].S;
            all_players[id].move(p);
        }
        mutlock.unlock();
    }

    void handle() {

    }

    void send_all() {
        mutlock.lock();
        MovePack m;
        m.v.resize(all_players.size());
        for (int i=0; i<all_players.size(); ++i)
            m.v[i] = MP(i, MP(all_players[i].x, all_players[i].y));

        Packet packet;
        packet << m;
        // vector<Client> clients;
        bool has = false;
        for (Client& c:clients) {   
            cout << "send {" << m << "} " << c.ip << ":" << c.port << "\n";
            mutlock.unlock();
            socket_s.send(packet, c.ip, c.port);
            mutlock.lock();
            has = true;
        }
        if (has)
            cout << endl;
        mutlock.unlock();
    }


};

void listen_clients(Server& srv) {
    while (true)
        srv.listen_all();
}

void send_clients(Server& srv) {
    while (true) {
        srv.send_all();
    }
}

void listen_clients_once(Server& srv)   {srv.listen_all();}
void send_clients_once(Server& srv)     {srv.send_all();}



// Server srv;


int main(int argc, char** argv)
{
    int listen_port = 27900;
    if (argc > 1)
        listen_port = atoi(argv[1]); 

    Server srv(listen_port);
    thread thr_listen(listen_clients, std::ref(srv));
    // thread thr_sender(send_clients, std::ref(srv));
    thr_listen.detach();
    // thr_sender.detach();

    window.create(sf::VideoMode(100, 100), "Hexar SERVER", sf::Style::Default);
    window.setFramerateLimit(60);
    
    
    while (window.isOpen())
    {
        srv.mutlock.lock();
        if (srv.need_join) {
            
        }
        srv.mutlock.unlock();
        
            
        // thread thr_listen_o(listen_clients_once, std::ref(srv));
        thread thr_sender_o(send_clients_once, std::ref(srv));
        // thr_listen_o.detach();
        thr_sender_o.detach();


        static int tt=0;
        srv.mutlock.lock();
        cout << ++tt << ' ' << srv.clients.size() << endl;
        srv.mutlock.unlock();
        sf::sleep(sf::seconds(0.1));
        // std::this_thread::sleep_for(1s);
        // listen_clients(srv);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)            
                window.close();
        }
        
        if (sf::Event::KeyReleased) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                window.close();
        }
                
        srv.handle();

        // static double t = 2; t += 0.2;
        // all_players[1].move_direction(sin(t/log(t)), cos(t*t/50/log(t)));
        // all_players[2].move_direction(sin(t/log(t)), sin(t/20)*cos(t/50/log(t)));
        
        for (Player& i:all_players)
            for (Player& j:all_players)
                collapse_check(i, j);

        for (Player& i:all_players)
            m.handle(i);
        
    }
    return 0;
}