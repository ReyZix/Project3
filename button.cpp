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
