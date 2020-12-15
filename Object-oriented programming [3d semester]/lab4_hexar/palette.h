#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

namespace Palette {
    const int non_captured_opacity = 120;
    const sf::Color fieldBg(180, 180, 180);
    const sf::Color fieldCell(255, 255, 255);
    const sf::Color fieldBorder(255, 20, 20);

    const std::vector<sf::Color> players = {
        Color(0, 0, 0),
        Color(0, 153, 255),
        Color(255, 153, 0),
        Color(102, 255, 51),
    };
    
    std::vector<sf::Color> list_colors = {
        Palette::fieldCell,
        Palette::players[0]
    };
}


    
