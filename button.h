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

class recButton {
private:
    sf::RectangleShape button;
    sf::Text text;
public:
    recButton();
    recButton(string t, sf::Vector2f size, sf::Color bgColor, sf::Color textColor, sf::Font& font);
    void setBackgroundColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setPosition(sf::Vector2f pos);
    bool isMouseOver(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
