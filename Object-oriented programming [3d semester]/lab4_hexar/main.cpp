#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
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
const std::string WINDOW_NAME = "Convex-hull";


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
            object.setOutlineThickness(1);
            object.setOutlineColor(sf::Color(0, 0, 0));
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
            text.setCharacterSize(12);
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

        int w = 13, h = 8;
        for (int i=1; i<=w; ++i)
            for (int j=1; j<=h; ++j)
                drawable.PB(Hexagon(i, j, sf::Color(127, 255, 127)));

        // drawable.PB(Hexagon(0, 0, sf::Color(255, 0, 0)));
        // drawable.PB(Hexagon(0, 1, sf::Color(255, 0, 0)));
        // drawable.PB(Hexagon(1, 0, sf::Color(255, 0, 0)));
        // drawable.PB(Hexagon(1, 1, sf::Color(255, 0, 0)));
        // drawable.PB(Hexagon(2, 0, sf::Color(255, 0, 0)));
        // drawable.PB(Hexagon(2, 1, sf::Color(255, 0, 0)));
    }
};

const int Map::cell_size = 30;


int main()
{

    sf::ContextSettings settings;
    // settings.antialiasingLevel = 8;
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
                
        // get_cursor_text(window);
    

        window.clear(sf::Color::White);
        for (auto i:m.drawable) {
            // cout << sizeof(i) << '\n';
            window.draw(i.object);
            window.draw(i.object2);
        }
        
        window.display();
    }
    return 0;
}