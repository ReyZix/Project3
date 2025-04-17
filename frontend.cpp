#include "Frontend.h"
#include "Textbox.h"
#include "Backend.h"
#include "Games.h"
#include "Button.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

void runFrontend() {
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "DSA_PROJECT");

    sf::Font font;
    font.loadFromFile("Font/times.ttf");

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
    Textbox userInputTextbox(20, sf::Color::Black, false);
    userInputTextbox.setFont(font);
    userInputTextbox.setPosition(sf::Vector2f(WINDOW_WIDTH / 4.5 + 85, WINDOW_HEIGHT / 3.5 + 10));

    sf::RectangleShape userInputBox;
    setupRectangle(userInputBox, sf::Vector2f(420.5, 50), sf::Vector2f(WINDOW_WIDTH / 4.5 - 125,
        WINDOW_HEIGHT / 3.5 - 10), sf::Color::Black, sf::Color(237, 232, 245, 255));

    // Merge sort button
    Button mergeSortButton(WINDOW_WIDTH / 4.5 - 125, WINDOW_HEIGHT / 3.5 + 75, "Merge Sort", font);
    Button quickSortButton(WINDOW_WIDTH / 4.5 - 125, WINDOW_HEIGHT / 3.5 + 100, "Quick Sort", font);

    // Main window loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    userInputTextbox.typing(event);
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x,event.mouseButton.y);
                        // Clicking the textbox
                        if (userInputBox.getGlobalBounds().contains(mousePosition)) {
                            userInputTextbox.setSelected(true);
                        } else {
                            userInputTextbox.setSelected(false);
                        }
                        // Clicking button
                        if (mergeSortButton.checkIsSelected(mousePosition)) {
                            quickSortButton.deselect();
                        } else if (quickSortButton.checkIsSelected(mousePosition)) {
                            mergeSortButton.deselect();
                        }
                    }
                    break;
                case sf::Event::KeyPressed:
                    // Pressing enter after typing the game name
                    if (event.key.code == sf::Keyboard::Enter && userInputTextbox.getSelected()) {
                        string userInput = userInputTextbox.getText();
                        // Make sure nothing is printed if nothing is entered
                        if (userInput.empty()) {
                            recommendedGames = "";
                            performanceOutput = "";
                        } else { // Call backend and time how long it takes for the alg to run
                            recommendedGames = "The recommended games goes here";
                            performanceOutput = "The performance of the algs goes here";
                        }
                        userInputTextbox.setSelected(false);
                        cout << userInput << endl;
                        cout << "Merge Sort: " << mergeSortButton.getSelected() << endl;
                        cout << "Quick Sort: " << quickSortButton.getSelected() << endl;
                    }
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
        userInputTextbox.draw(window);
        mergeSortButton.draw(window);
        quickSortButton.draw(window);
        window.display();
    }
}
