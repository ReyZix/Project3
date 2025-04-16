#include "Textbox.h"

// Helper Functions

void setupText(sf::Text &text, const string &str, sf::Font &font, int size, sf::Color color, sf::Vector2f position) {
    text.setString(str);
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);
    text.setPosition(position);
}

void setupRectangle(sf::RectangleShape &rec, sf::Vector2f size, sf::Vector2f position, sf::Color outline_color, sf:: Color fill_color) {
    rec.setSize(size);
    rec.setOutlineThickness(5);
    rec.setOutlineColor(outline_color);
    rec.setFillColor(fill_color);
    rec.setPosition(position);
}

void setText (sf::Text& text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x,y));
}

// Textbox Methods

Textbox::Textbox() {}

Textbox::Textbox(int size, sf::Color color, bool selected) {
    textbox.setCharacterSize(size);
    textbox.setColor(color);
    IsSelected = selected;
    textbox.setString(selected ? "|" : "");
}

void Textbox::deleteLastcharacter() {
    string t = text.str();
    string newText = "";
    for(int i = 0; i < t.length() - 1; i++) {
        newText += t[i];
    }
    text.str("");
    text << newText;
    textbox.setString(text.str());
}

void Textbox::inputLogic(int CharTyped) {
    if(CharTyped != ENTER_KEY && CharTyped != ESCAPE_KEY && CharTyped != DELETE_KEY) {
        text << static_cast<char>(CharTyped);
    } else if (CharTyped == DELETE_KEY) {
        if(text.str().size() > 0) {
            deleteLastcharacter();
        }
    }
    textbox.setString(text.str() + "|");
}

bool Textbox::getSelected() {
    return IsSelected;
}

string Textbox::getText() {
    return text.str();
}

void Textbox::setFont(sf::Font &font) {
    textbox.setFont(font);
}

void Textbox::setPosition(sf::Vector2f position) {
    textbox.setPosition(position);
}

void Textbox::setLimit(bool ToF) {
    HasLimit = ToF;
}

void Textbox::setLimit(bool ToF, int Lim) {
    HasLimit = ToF;
    Limit = Lim - 1;
}

void Textbox::setSelected(bool Selected) {
    IsSelected = Selected;
    if(!IsSelected) {
        string t = text.str();
        string newText = "";
        for(int i = 0; i < t.length(); i++) {
            newText += t[i];
        }
        textbox.setString(newText);
    }
}

void Textbox::draw(sf::RenderWindow &window) {
    window.draw(textbox);
}

void Textbox::centerText () {
    sf::FloatRect bounds = textbox.getGlobalBounds();
    textbox.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Textbox::typing(sf::Event input) {
    if(IsSelected) {
        int CharTyped = input.text.unicode;
        if(CharTyped < 128) {
            if(HasLimit) {
                if(text.str().size() >= Limit) {
                    inputLogic(CharTyped);
                } else if (text.str().size() > Limit && CharTyped == DELETE_KEY) {
                    deleteLastcharacter();
                }
            } else {
                inputLogic(CharTyped);
            }
        }
        centerText();
    }
}
