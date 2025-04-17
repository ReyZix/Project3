#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Button {
private:
    sf::CircleShape outerCircle;
    sf::CircleShape innerCircle;
    sf::Text typeOfSort;
    sf::FloatRect clickingArea;
    bool isSelected;
public:
    Button();
    Button(float x, float y, const string& text, sf::Font& font);
    void draw(sf::RenderWindow& window);
    bool checkIsSelected(sf::Vector2f mousePosition);
    void deselect();
    bool getSelected();
    string getTypeOfSort();
};
