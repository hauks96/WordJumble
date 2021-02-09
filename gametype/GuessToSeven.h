//
// Created by agirm on 07/02/2021.
//

#ifndef HW2_GUESSTOSEVEN_H
#define HW2_GUESSTOSEVEN_H
#include "GameType.h"
#include "../score/Score.h"
#include "../timer/Timer.h"
#include <cstring>

class GuessToSeven: public GameType {
public:
    GuessToSeven();
    bool checkGameOver(Score& score){
        if (score.guessed_words == 7 || score.points == 0){
            return true;
        }
        return false;
    }
    char* name() const{
        return this->game_name;
    }
private:
    char* game_name;
};

GuessToSeven::GuessToSeven() {
    char temp[] = "Guess seven words";
    char* init_game_name = new char[18];
    strcpy(init_game_name, temp);
    this->game_name = init_game_name;
}

#endif //HW2_GUESSTOSEVEN_H
