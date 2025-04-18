#include "backend.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

//EVERYTHING WITH SKIP WE WILL GO BACK TO AND DECIDE!!!!

using namespace std;

vector<Game> loadGamesFromCSV(const string& filePath) {
    vector<Game> games;
    ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return games;
    }

    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Game g;

        getline(ss, g.title, ',');
        getline(ss, token, ','); // skip handheld
        getline(ss, token, ','); // skip max players
        getline(ss, token, ','); // skip multiplatform

        getline(ss, token, ','); // online play
        g.online_play = (token == "True" || token == "true");

        getline(ss, g.genre, ','); // genre
        getline(ss, token, ','); // skip licensed
        getline(ss, g.publisher, ','); // publisher
        getline(ss, token, ','); // skip sequel

        getline(ss, token, ','); // review score
        try {
            g.review_score = stoi(token);
        } catch (...) {
            g.review_score = 0;
        }

        getline(ss, token, ','); // skip sales
        getline(ss, token, ','); // skip used price
        getline(ss, g.platform, ','); // platform
        getline(ss, g.esrb_rating, ','); // esrb
        getline(ss, token, ','); // skip re-release

        getline(ss, token, ','); // release year
        try {
            g.release_year = stoi(token);
        } catch (...) {
            g.release_year = 0;
        }

        for (int i = 0; i < 4; ++i) getline(ss, token, ','); // skip to avg playtime

        getline(ss, token, ','); // avg playtime
        try {
            g.avgPlayTime = static_cast<int>(stof(token));
        } catch (...) {
            g.avgPlayTime = 0;
        }

        games.push_back(g);
    }

    return games;
}

//Merge Sort
vector<Game> mergeSort(const vector<Game>& games, bool(*comp)(const Game&, const Game&)) {
    if (games.size() <= 1)
        return games;

    size_t mid = games.size() / 2;
    vector<Game> left(games.begin(), games.begin() + mid);
    vector<Game> right(games.begin() + mid, games.end());

    left = mergeSort(left, comp);
    right = mergeSort(right, comp);

    vector<Game> merged;
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (comp(left[i], right[j]))
            merged.push_back(left[i++]);
        else
            merged.push_back(right[j++]);
    }
    while (i < left.size()) merged.push_back(left[i++]);
    while (j < right.size()) merged.push_back(right[j++]);

    return merged;
}

//quicksort helper
void quickSortHelper(vector<Game>& games, int low, int high, bool(*comp)(const Game&, const Game&)) {
    if (low >= high) return;

    Game pivot = games[high];
    int i = low;

    for (int j = low; j < high; ++j) {
        if (comp(games[j], pivot)) {
            swap(games[i], games[j]);
            i++;
        }
    }
    swap(games[i], games[high]);

    quickSortHelper(games, low, i - 1, comp);
    quickSortHelper(games, i + 1, high, comp);
}

vector<Game> quickSort(const vector<Game>& games, bool(*comp)(const Game&, const Game&)) {
    vector<Game> sorted = games;
    quickSortHelper(sorted, 0, sorted.size() - 1, comp);
    return sorted;
}

// This function compares the input game with every other game in the dataset
// and returns the game that is most similar based on shared attributes.
// The more matching characteristics (publisher, genre, etc.), the higher the similarity score.
Game findMostSimilarGame(const Game& target, const vector<Game>& games)
{
    int bestScore = -1; // Keeps track of the highest similarity score
    Game mostSimilar;   // Stores the best current match

    for (const auto& game : games)
    {
        if (game.title == target.title)
        {
          continue; // Skip comparing the game to itself
        }

        int score = 0;

        // Add points for sharing publisher (strong indicator of style/game quality)
        if (game.publisher == target.publisher)
        {
            score += 3;
        }

        // Add points for matching ESRB rating
        if (game.esrb_rating == target.esrb_rating)
        {
            score += 2;
        }

        // Add points for matching genre
        if (game.genre == target.genre)
        {
            score += 2;
        }

        // Add a point if both support or don't support online play
        if (game.online_play == target.online_play)
        {
            score += 1;
        }

        // Add a point if the review scores are close (within 1 point)
        if (abs(game.review_score - target.review_score) <= 1)
        {
            score += 1;
        }

        // Update best match if this game has a higher score
        if (score > bestScore)
        {
            bestScore = score;
            mostSimilar = game;
        }
    }
    return mostSimilar;
}
