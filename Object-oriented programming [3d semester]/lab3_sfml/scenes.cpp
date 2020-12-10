#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace sf;

template<class DRAWABLE>
void setOriginToCenter(DRAWABLE& entity, double x=1, double y=1) {
    sf::FloatRect r = entity.getLocalBounds();
    entity.setOrigin(r.left + x * r.width / 2.f, 
                     r.top + y * r.height / 2.f);
}


class Scene {
public:
    sf::Font font;
    sf::Text title_text, bottom_text, med_text;
    int algo;

    Scene() {
        init();
    }


    void init() {
        string fontFile = "HelveticaLTStd-Blk.otf";
        font.loadFromFile(fontFile);
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
            "Press \"1\" for back to the Menu\n"
            "\"2\" for Grahem, \"3\" for Jarvis algo\n\n"
            "\"F5\" for generate new points\n"
            "Left/Right arrows for animate build\n"
            "\"K\" for increase points number, \"L\" for decrease\n"
            "\"ESC\" or \"Q\" for exit");
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
