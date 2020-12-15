#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

namespace Palette {
    const sf::Color fieldBg(180, 180, 180);
    const sf::Color fieldCell(255, 255, 255);
    const std::vector<sf::Color> players = {
        Color(60, 60, 255)
    };
    const sf::Color fieldBorder(255, 80, 80);
}


std::vector<sf::Color> list_colors = {
    Palette::fieldCell,
    Palette::players[0]
};
    
