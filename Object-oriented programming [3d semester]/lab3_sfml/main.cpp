#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "configs.h"
#include "convex_hull.cpp"
#include "scenes.cpp"
#include "visualizer.cpp"
using namespace std;
using namespace sf;
typedef pair<double,double> PDD;
#define MP make_pair
#define PB push_back
#define S second
#define F first




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
    
    
    
    Scene *scenes[3] = {new MenuScene(), new GrahemScene(), new JarvisScene()};
    int scene_id = 0;
    int cnt_dots = START_DOTS;
    HullVisualiser gv(cnt_dots, 0);
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
                gv = HullVisualiser(cnt_dots, scene_id);
                while (gv.next())
                    ;
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
                gv.prev();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
                gv.next();
    
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                cnt_dots = min(cnt_dots+1, MAX_DOTS);
                gv = HullVisualiser(cnt_dots, scene_id);
                while (gv.next())
                    ;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                cnt_dots = max(cnt_dots-1, MIN_DOTS);
                gv = HullVisualiser(cnt_dots, scene_id);
                while (gv.next())
                    ;
            }
    

            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
            //     animation = true;

            int new_scene = scene_id;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) new_scene = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) new_scene = 1;            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) new_scene = 2;
            if (new_scene != scene_id) {
                scene_id = new_scene;
                gv = HullVisualiser(cnt_dots, scene_id);
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