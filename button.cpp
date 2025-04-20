#include "Button.h"

// Button Methods

Button::Button() {}

Button::Button(float x, float y, const string& text, sf::Font& font) {
    // Outer circle
    outerCircle.setRadius(10);
    outerCircle.setPosition(x, y + 3);
    outerCircle.setFillColor(sf::Color::White);
    outerCircle.setOutlineColor(sf::Color::Black);
    outerCircle.setOutlineThickness(2);

    // Inner circle
    innerCircle.setRadius(5);
    innerCircle.setPosition(x + 5, y + 8);
    innerCircle.setFillColor(sf::Color::Black);

    // Type of sort
    typeOfSort.setFont(font);
    typeOfSort.setString(text);
    typeOfSort.setCharacterSize(24);
    typeOfSort.setFillColor(sf::Color::Black);
    typeOfSort.setPosition(x + 25, y - 5);

    // Click area
    float width = typeOfSort.getLocalBounds().width + 30;
    float height = max(typeOfSort.getLocalBounds().height, outerCircle.getGlobalBounds().height);
    clickingArea = sf::FloatRect(x, y, width, height);

    isSelected = false;
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(outerCircle);
    if (isSelected) {
        window.draw(innerCircle);
    }
    window.draw(typeOfSort);
}

bool Button::checkIsSelected(sf::Vector2f mousePosition) {
    if (clickingArea.contains(mousePosition)) {
        isSelected = true;
        return true;
    }
    return false;
}

void Button::deselect() {
    isSelected = false;
}

bool Button::getSelected() {
    return isSelected;
}

string Button::getTypeOfSort() {
    return typeOfSort.getString();
}

// Rectangular Button Methods

recButton::recButton() {}

recButton::recButton(string t, sf::Vector2f size, sf::Color bgColor, sf::Color textColor, sf::Font& font) {
    text.setString(t);
    text.setFont(font);
    text.setColor(textColor);
    text.setCharacterSize(24);

    button.setSize(size);
    button.setFillColor(bgColor);
    button.setOutlineColor(textColor);
    button.setOutlineThickness(5);
}

void recButton::setBackgroundColor(sf::Color color) {
    button.setFillColor(color);
}

void recButton::setTextColor(sf::Color color) {
    text.setColor(color);
}

void recButton::setPosition(sf::Vector2f pos) {
    button.setPosition(pos);

    float xpos = (pos.x + button.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2);
    float ypos = (pos.y + button.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2);
    text.setPosition({xpos - 5, ypos - 12});
}

bool recButton::isMouseOver(sf::RenderWindow& window) {
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    float btnX = button.getPosition().x;
    float btnY = button.getPosition().y;

    float btnXWidth = button.getPosition().x + button.getLocalBounds().width;
    float btnYHeight = button.getPosition().y + button.getLocalBounds().height;

    if (mouseX < btnXWidth && mouseX > btnX && mouseY < btnYHeight && mouseY > btnY) {
        return true;
    }
    return false;
}

void recButton::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}
