#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <sstream>
#include <string>
using namespace std;

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

// Helper function to set up the text and rectangles
void setupText(sf::Text &text, const string &str, sf::Font &font, int size, sf::Color color, sf::Vector2f position);
void setupRectangle(sf::RectangleShape &rec, sf::Vector2f size, sf::Vector2f position, sf::Color outline_color, sf:: Color fill_color);
void setText (sf::Text& text, float x, float y);

class Textbox {
private:
    sf::Text textbox;
    ostringstream text;
    bool IsSelected = false;
    bool HasLimit = false;
    int Limit;

    void deleteLastcharacter();
    void inputLogic(int CharTyped);

public:
    Textbox();
    Textbox(int size, sf::Color color, bool selected);
    bool getSelected();
    string getText();
    void setFont(sf::Font &font);
    void setPosition(sf::Vector2f position);
    void setLimit(bool ToF);
    void setLimit(bool ToF, int Lim);
    void setSelected(bool Selected);
    void draw(sf::RenderWindow &window);
    void centerText ();
    void typing(sf::Event input);
};
