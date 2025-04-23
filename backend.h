//
//

#ifndef BACKEND_H
#define BACKEND_H
#include "games.h"
#include<string>
#include<vector>

vector<Game> loadGamesFromCSV(const string& filePath);
vector<Game> mergeSort(const vector<Game>& games, bool(*comp)(const Game&, const Game&));
vector<Game> quickSort(const vector<Game>& games, bool(*comp)(const Game&, const Game&));
vector<Game> findTopSimilarGames(const Game& target, const vector<Game>& games, int topN = 3);


#endif //BACKEND_H
