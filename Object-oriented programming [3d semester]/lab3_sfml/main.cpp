#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "convex_hull.cpp"
using namespace std;
using namespace sf;

typedef pair<double,double> PDD;
#define MP make_pair
#define PB push_back
#define S second
#define F first


const int   CNT_DOTS = 50;
const int   SCREEN_W = 640,
            SCREEN_H = 480;



template<class DRAWABLE>
void setOriginToCenter(DRAWABLE& entity, double x=1, double y=1) {
    sf::FloatRect r = entity.getLocalBounds();
    entity.setOrigin(r.left + x * r.width / 2.f, 
                     r.top + y * r.height / 2.f);
}


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


VertexArray gen_hull(vector<PDD> dots) {
    vector<int> ids = ConvexHull(dots).hull;
    ids.push_back(ids[0]);

    int n = ids.size();
    VertexArray res(sf::LineStrip, n);
    for (int i=0; i<n; ++i) {
        res[i].position = sf::Vector2f(dots[ids[i]].F, dots[ids[i]].S);
        res[i].color = Color(255*(1-i%2), 0, 255*(i%2));
    }
    return res;

}

void generate_rand_field(int n, vector<CircleShape>& vertices, VertexArray& hull) {
    vector<PDD> dots = gen_random_dots(n);
    vertices = gen_vert(dots);
    hull = gen_hull(dots);
}


class GrahemVisualiser {
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


    GrahemVisualiser(int count_point) {
        cnt_dot = count_point;
        up.clear();
        dn.clear();

        dots = gen_random_dots(count_point);
        vertices = gen_vert(dots);
        events = ConvexHull(dots).events;
        step = 0;
    }

    void gen_hull_part() {
        vector<int> ids = dn;
        // ids.pop_back();
        reverse(ids.begin(), ids.end());
        ids.insert(ids.end(), up.begin(), up.end());

        // cout << ":: "; for (int i:ids) cout << i << ' '; cout << "::\n";

        int n = ids.size();
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


class RootView {
private:
    const string    WINDOW_NAME = "Karasick";
    const bool      ENABLE_VSYNC = true;    // vertical syncronisation; disable MAX_FPS option
    const int       MAX_FPS = 60;           // 0 for disable
    const int       ANTI_ALIASING = 8;
    sf::Font font;
    
public:    
    sf::RenderWindow window;
    sf::Text    text, 
                bottom_text;
        
    RootView() {
        cout << "$$$";
        sf::ContextSettings settings;
        settings.antialiasingLevel = ANTI_ALIASING;
        // settings.majorVersion = 2;
        window.create(sf::VideoMode(SCREEN_W, SCREEN_H), 
                       WINDOW_NAME, 
                       sf::Style::Default, 
                       settings);  
    
        
        if (ENABLE_VSYNC)  
            window.setVerticalSyncEnabled(true);
        else      
            if (MAX_FPS)
                window.setFramerateLimit(MAX_FPS);
        
        load_helvetica();
        text = set_title_text("Convex hull: Graham");
        bottom_text = set_bottom_text("");
        cout << "$$$";
    }


    void load_helvetica() {
        font.loadFromFile("HelveticaLTStd-Blk.otf");
    }


    sf::Text set_title_text(string str) {
        sf::Text text;
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(16);
        text.setFillColor(Color(0, 0, 0, 255));
        text.setStyle(sf::Text::Regular);
        setOriginToCenter(text, 1, 0);
        text.setPosition(SCREEN_W/2, 5);
        return text;
    }


    sf::Text set_bottom_text(string t) {
        sf::Text text;
        text.setFont(font);
        text.setString("");
        text.setCharacterSize(10);
        text.setFillColor(Color(0, 0, 0, 255));
        text.setStyle(sf::Text::Regular);
        setOriginToCenter(text, 0, 0);
        text.setPosition(3, SCREEN_H-15);
        return text;
    }


    void handle_window() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)            
                window.close();
        }        
    }


    void handle_cursor() {
        bool mouse_pressed = false;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mouse_pressed = true;
        }

        sf::Vector2i cursorePosition = sf::Mouse::getPosition(window);
        std::ostringstream bottom_text_s; 
        bottom_text_s << "cursor:\t" << cursorePosition.x << 'x' << cursorePosition.y;   
        if (mouse_pressed)
            bottom_text_s << "\tpress";
        bottom_text.setString(bottom_text_s.str());
    }

};


int main()
{

    RootView rview();

    GrahemVisualiser gv(CNT_DOTS);
    bool animation = false;
    while (rview.window.isOpen())
    {
        rview.handle_window();  
        rview.handle_cursor();
        
        if (sf::Event::KeyReleased) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                rview.window.close();
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
                gv = GrahemVisualiser(CNT_DOTS);
                while (gv.next())
                    ;
                animation = false;
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
                gv.prev();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
                gv.next();
    
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
                animation = true;

            sf::sleep(sf::milliseconds(10));
        }
        



        rview.window.clear(sf::Color::White);
        rview.window.draw(rview.text);
        rview.window.draw(rview.bottom_text);
        rview.window.draw(gv.hull);
        for (auto v:gv.vertices)
            rview.window.draw(v);

        rview.window.display();
    }
    return 0;
}