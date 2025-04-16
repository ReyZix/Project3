#include "frontend.h"
#include "backend.h"
#include "games.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

// Helper functions

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

void runFrontend() {
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "DSA_PROJECT");

    sf::Font font;
    font.loadFromFile("DSA_PROJECT/times.ttf");

    // Title
    sf::Text titleText;
    setupText(titleText, "MAIN MENU", font, 24, sf::Color::Black, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 - 50));
    setText(titleText, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 - 50);

    sf::RectangleShape titleOutline;
    setupRectangle(titleOutline, sf::Vector2f(1004, 100), sf::Vector2f(WINDOW_WIDTH / 9 - 25,
        WINDOW_HEIGHT / 6 - 100), sf::Color::Black, sf::Color::Transparent);

    // Input
    sf::Text enterText;
    setupText(enterText, "ENTER GAME'S NAME", font, 24, sf::Color::Black, sf::Vector2f(WINDOW_WIDTH / 4.5 + 90, WINDOW_HEIGHT / 3.5 - 50));
    setText(enterText, WINDOW_WIDTH / 4.5 + 90, WINDOW_HEIGHT / 3.5 - 50);

    sf::RectangleShape enterOutline;
    setupRectangle(enterOutline, sf::Vector2f(487.5, 250), sf::Vector2f(WINDOW_WIDTH / 9 - 25,
        WINDOW_HEIGHT / 3.5 - 75), sf::Color::Black, sf::Color::Transparent);

    // Recommended output
    string recommendedGames;

    sf::Text recommendedText;
    setupText(recommendedText, "RECOMMENDED GAMES", font, 24, sf::Color::Black, sf::Vector2f(WINDOW_WIDTH / 1.25 - 95, WINDOW_HEIGHT / 3.5 - 50));
    setText(recommendedText, WINDOW_WIDTH / 1.25 - 95, WINDOW_HEIGHT / 3.5 - 50);

    sf::RectangleShape recommendedOutline;
    setupRectangle(recommendedOutline, sf::Vector2f(487.5, 250), sf::Vector2f(WINDOW_WIDTH / 2 + 25,
        WINDOW_HEIGHT / 3.5 - 75), sf::Color::Black, sf::Color::Transparent);

    sf::RectangleShape recommendedRec;
    setupRectangle(recommendedRec, sf::Vector2f(420.5, 150), sf::Vector2f(WINDOW_WIDTH / 2 + 55, WINDOW_HEIGHT / 3.5 - 15), sf::Color::Black, sf::Color(237, 232, 245, 255));

    // Performance output
    string performanceOutput;

    sf::Text performanceLabel;
    setupText(performanceLabel, "SORTING ALGORITHM PERFORMANCE", font, 24, sf::Color::Black, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 1.75));
    setText(performanceLabel, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 1.75);

    sf::RectangleShape performanceOutline;
    setupRectangle(performanceOutline, sf::Vector2f(1004, 325), sf::Vector2f(WINDOW_WIDTH / 9 - 25,
        WINDOW_HEIGHT / 2 + 25), sf::Color::Black, sf::Color::Transparent);

    sf::RectangleShape performanceRec;
    setupRectangle(performanceRec, sf::Vector2f(935, 200), sf::Vector2f(WINDOW_WIDTH / 4.5 - 125,
        WINDOW_HEIGHT / 2 + 100), sf::Color::Black, sf::Color(237, 232, 245, 255));

    // Textbox
    sf::RectangleShape userInputBox;
    setupRectangle(userInputBox, sf::Vector2f(420.5, 50), sf::Vector2f(WINDOW_WIDTH / 4.5 - 125,
        WINDOW_HEIGHT / 3.5 - 10), sf::Color::Black, sf::Color(237, 232, 245, 255));

    // Main window loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        sf::Text recommendedGamesText(recommendedGames, font, 20);
        recommendedGamesText.setFillColor(sf::Color::Black);
        setText(recommendedGamesText, WINDOW_WIDTH / 1.25 - 95, WINDOW_HEIGHT / 3.5);

        sf::Text performanceOutputText(performanceOutput, font, 20);
        performanceOutputText.setFillColor(sf::Color::Black);
        setText(performanceOutputText, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 125);

        // Draw everything
        window.clear(sf::Color(134, 151, 196, 255));
        window.draw(titleText);
        window.draw(titleOutline);
        window.draw(enterText);
        window.draw(enterOutline);
        window.draw(recommendedText);
        window.draw(recommendedOutline);
        window.draw(recommendedRec);
        window.draw(recommendedGamesText);
        window.draw(performanceLabel);
        window.draw(performanceOutline);
        window.draw(performanceRec);
        window.draw(performanceOutputText);
        window.draw(userInputBox);
        window.display();
    }
}
