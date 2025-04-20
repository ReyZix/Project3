#include "Frontend.h"
#include "Textbox.h"
#include "Backend.h"
#include "Games.h"
#include "Button.h"
#include <chrono>

#include <SFML/Graphics.hpp>

#include <string>


using namespace std;
//push
void runFrontend() {


    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "DSA_PROJECT");

    sf::Font font;
    font.loadFromFile("Font/times.ttf");



    // Title
    sf::Text titleText;
    setupText(titleText, "MAIN MENU", font, 24, sf::Color::Black, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 - 65));
    setText(titleText, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 - 65);



    sf::RectangleShape titleOutline;
    setupRectangle(titleOutline, sf::Vector2f(1004, 100), sf::Vector2f(WINDOW_WIDTH / 9 - 25,
        WINDOW_HEIGHT / 6 - 100), sf::Color::Black, sf::Color::Transparent);

    // Instructions

    sf::Text instructionsText;
    setupText(instructionsText, "Start by selecting the sorting method you want to use. Then, enter the name of "
        "the game to find another game with similar features", font, 16, sf::Color::Black, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 - 25));
    setText(instructionsText, WINDOW_WIDTH / 2 + 10, WINDOW_HEIGHT / 6 - 25);

    // Input
    sf::Text enterText;
    setupText(enterText, "ENTER GAME'S NAME", font, 24, sf::Color::Black, sf::Vector2f(WINDOW_WIDTH / 4.5 + 90, WINDOW_HEIGHT / 3.5 - 50));
    setText(enterText, WINDOW_WIDTH / 4.5 + 90, WINDOW_HEIGHT / 3.5 - 50);

    sf::RectangleShape enterOutline;
    setupRectangle(enterOutline, sf::Vector2f(487.5, 250), sf::Vector2f(WINDOW_WIDTH / 9 - 25,
        WINDOW_HEIGHT / 3.5 - 75), sf::Color::Black, sf::Color::Transparent);

    // Recommended output
    string recommendedGames;
    string actualGame;

    sf::Text recommendedText;
    setupText(recommendedText, "RECOMMENDED GAME", font, 24, sf::Color::Black, sf::Vector2f(WINDOW_WIDTH / 1.25 - 95, WINDOW_HEIGHT / 3.5 - 50));
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
                        if (userInput.empty())
                        {
                            recommendedGames = "";
                            performanceOutput = "";
                        }
                        else if (!userInput.empty() && (mergeSortButton.getSelected() || quickSortButton.getSelected()))
                        {
                            // Load the game dataset
                            vector<Game> games = loadGamesFromCSV("video_games.csv");
                            //cout << "Loaded games: " << games.size() << endl;
                            // debugging bc recommendations weren't working


                            // Start timing
                            using namespace std::chrono;
                            auto start = high_resolution_clock::now();

                            // Sort the games (we're just measuring performance, not using the result here)
                            vector<Game> sortedGames;
                            if (mergeSortButton.getSelected())
                            {
                                sortedGames = mergeSort(games, [](const Game& a, const Game& b)
                                {
                                    return a.review_score > b.review_score;
                                });
                            }
                            else
                            {
                                sortedGames = quickSort(games, [](const Game& a, const Game& b)
                                {
                                    return a.review_score > b.review_score;
                                });
                            }

                            // End timing and record duration
                            auto end = high_resolution_clock::now();
                            auto duration = duration_cast<microseconds>(end - start).count();

                            // Update performance output
                            performanceOutput = (mergeSortButton.getSelected() ? "Merge Sort" : "Quick Sort");
                            performanceOutput += " took " + to_string(duration) + " microseconds.";

                            // Find and recommend similar game

                            auto normalize = [](string str) {
                                transform(str.begin(), str.end(), str.begin(), ::tolower);
                                str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
                                return str;
                            };

                            // Search for the game
                            auto it = find_if(games.begin(), games.end(), [&](const Game& g) {
                                return normalize(g.title) == normalize(userInput);
                            });


                            if (it != games.end())
                            {
                                Game recommended = findMostSimilarGame(*it, games);
                                recommendedGames = "We recommend:\n";
                                actualGame = recommended.title;
                            }
                            else
                            {
                                actualGame = "";
                                recommendedGames = "Game not found. Please try again.";
                            }
                        }
                        userInputTextbox.setSelected(false);
                    }
                    break;
            }
        }

        sf::Text recommendedGamesText(recommendedGames, font, 20);
        recommendedGamesText.setFillColor(sf::Color::Black);
        setText(recommendedGamesText, WINDOW_WIDTH / 1.25 - 95, WINDOW_HEIGHT / 3.5 + 50);

        sf::Text actualGameText(actualGame, font, 20);
        actualGameText.setFillColor(sf::Color::Black);
        setText(actualGameText, WINDOW_WIDTH/ 1.25 - 95, WINDOW_HEIGHT / 3.5 + 65);

        sf::Text performanceOutputText(performanceOutput, font, 30);
        performanceOutputText.setFillColor(sf::Color::Black);
        setText(performanceOutputText, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 200);

        // Draw everything
        window.clear(sf::Color(134, 151, 196, 255));
        window.draw(titleText);
        window.draw(titleOutline);
        window.draw(instructionsText);
        window.draw(enterText);
        window.draw(enterOutline);
        window.draw(recommendedText);
        window.draw(recommendedOutline);
        window.draw(recommendedRec);
        window.draw(recommendedGamesText);
        window.draw(actualGameText);
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
