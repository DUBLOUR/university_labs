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



template<class DRAWABLE>
void setOriginToCenter(DRAWABLE& entity, double x=1, double y=1) {
    sf::FloatRect r = entity.getLocalBounds();
    entity.setOrigin(r.left + x * r.width / 2.f, 
                     r.top + y * r.height / 2.f);
}


vector<PDD> gen_random_dots(int n) {
    vector<PDD> res(n);
    int d = 50;    
    for (PDD& x:res) {
        x.F = rand() % (640 - 2*d) + d;
        x.S = rand() % (480 - 2*d) + d;
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


int main()
{



    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    // settings.majorVersion = 2;

    RenderWindow window(sf::VideoMode(640, 480), "SFML shapes", sf::Style::Default, settings);  
    // RenderWindow window(sf::VideoMode(640, 480), "Karasick");
    window.setVerticalSyncEnabled(true);
    // window.setFramerateLimit(60);
    

    sf::CircleShape circle(20);
    circle.setPointCount(10);
    circle.setFillColor(sf::Color(150, 50, 250));

    circle.setOutlineThickness(5.f);
    circle.setOutlineColor(sf::Color(250, 150, 100));
    setOriginToCenter(circle);
    circle.setPosition(300, 100);
    circle.setPosition(0, 0);
    circle.setPosition(640, 480);
    
    
    sf::Font font;
    sf::Text text;
    font.loadFromFile("HelveticaLTStd-Blk.otf");
    text.setFont(font);
    text.setString("Convex hull: Graham");
    text.setCharacterSize(16);
    text.setFillColor(Color(0, 0, 0, 255));
    text.setStyle(sf::Text::Regular);
    setOriginToCenter(text, 1, 0);
    text.setPosition(640/2, 5);
        
    vector<PDD> dots = gen_random_dots(20);
    vector<CircleShape> vertices = gen_vert(dots);
    VertexArray hull = gen_hull(dots);

    // sf::Vertex line[2];
    // line[0].position = sf::Vector2f(10, 0);
    // line[0].color  = sf::Color::Red;
    // line[1].position = sf::Vector2f(20, 0);
    // line[1].color = sf::Color::Red;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)            
            window.close();
        }
        window.clear(sf::Color::White);
        

        // window.draw(circle);
        window.draw(text);

        window.draw(hull);
        for (auto v:vertices)
            window.draw(v);


        window.display();
    }
    return 0;
}