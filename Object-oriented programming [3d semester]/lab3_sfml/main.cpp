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

const int       SCREEN_W = 640,
                SCREEN_H = 480,
                CNT_DOTS = 25;
const string    WINDOW_NAME = "Karasick";


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



class Scene {
public:
    sf::Font font;
    sf::Text title_text, bottom_text, med_text;
    int algo;

    Scene() {
        init();
    }


    void init() {
        font.loadFromFile("HelveticaLTStd-Blk.otf");
        title_text = set_title_text("", font);
        med_text = set_med_text("", font);
        bottom_text = set_bottom_text("", font);
    }


    sf::Text set_title_text(string str, sf::Font& font) {
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


    sf::Text set_med_text(string str, sf::Font& font) {
        sf::Text text;
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(14);
        text.setFillColor(Color(0, 0, 0, 255));
        text.setStyle(sf::Text::Regular);
        setOriginToCenter(text, 1, 1);
        text.setPosition(10, 50);
        return text;
    }


    sf::Text set_bottom_text(string str, sf::Font& font) {
        sf::Text text;
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(10);
        text.setFillColor(Color(0, 0, 0, 255));
        text.setStyle(sf::Text::Regular);
        setOriginToCenter(text, 0, 0);
        text.setPosition(3, SCREEN_H-15);
        return text;
    }


    string get_cursor_text(RenderWindow& window) {
        sf::Vector2i cursorePosition = sf::Mouse::getPosition(window);
        std::ostringstream bottom_text_s; 
        bottom_text_s << "cursor:\t" << cursorePosition.x << 'x' << cursorePosition.y;   
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            bottom_text_s << "\tpress";
        return bottom_text_s.str();
    }
};


class MenuScene: public Scene {
public:
    MenuScene() {
        init();
        title_text.setString("Menu");
        med_text.setString(
            "Press 1 for back to the Menu\n"
            "2 for Grahem, 3 for Jarvis algo\n\n"
            "F5 for generate new points\n"
            "Left/Right arrows for animate build\n"
            "ESC or Q for exit");
    }
};

class GrahemScene: public Scene {
public:
    GrahemScene() {
        init();
        title_text.setString("Convex hull: Graham");
        algo = 0;
    }
};


class JarvisScene: public Scene {
public:
    JarvisScene() {
        init();
        title_text.setString("Convex hull: Jarvis");
        algo = 1;
    }
};


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
    

    
    HullVisualiser gv(CNT_DOTS, 0);

    Scene *scenes[3] = {new MenuScene(), new GrahemScene(), new JarvisScene()};
    int scene_id = 0;

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
                gv = HullVisualiser(CNT_DOTS, scene_id-1);
                while (gv.next())
                    ;
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
                gv.prev();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
                gv.next();
    
            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
            //     animation = true;

            int new_scene = scene_id;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) new_scene = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) new_scene = 1;            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) new_scene = 2;
            if (new_scene != scene_id) {
                scene_id = new_scene;
                gv = HullVisualiser(CNT_DOTS, scene_id);
                while (gv.next())
                    ;
            }

            sf::sleep(sf::milliseconds(10));
        }
                
        scenes[scene_id] -> bottom_text.setString(scenes[scene_id] -> get_cursor_text(window));
    

        window.clear(sf::Color::White);
        
        switch (scene_id) {
            case 0:
                window.draw(scenes[scene_id] -> title_text);
                window.draw(scenes[scene_id] -> med_text);
                break;
            case 1:
                window.draw(scenes[scene_id] -> title_text);
                window.draw(scenes[scene_id] -> bottom_text);
                window.draw(gv.hull);
                for (auto v:gv.vertices)
                    window.draw(v);
                break;

            case 2:
                window.draw(scenes[scene_id] -> title_text);
                window.draw(scenes[scene_id] -> bottom_text);
                window.draw(gv.hull);
                for (auto v:gv.vertices)
                    window.draw(v);
                break;
        }
        
        window.display();
    }
    return 0;
}