//
//

#ifndef GAMES_H
#define GAMES_H
#include<string>
#include<iostream>
using namespace std;
struct Game {
    string title;
    string platform;
    string publisher;
    string genre;
    string esrb_rating;
    bool online_play;
    int release_year;
    int review_score;
    int avgPlayTime;
};


#endif //GAMES_H
