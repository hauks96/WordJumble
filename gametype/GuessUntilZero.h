#ifndef HW2_GUESSUNTILZERO_H
#define HW2_GUESSUNTILZERO_H
#include "GameType.h"
#include "../score/Score.h"
#include "../timer/Timer.h"
#include <cstring>

class GuessUntilZero: public GameType{
public:
    GuessUntilZero();
    ~GuessUntilZero(){
        delete this->game_name;
    }
    bool checkGameOver(Score& score){
        if (score.points == 0){
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


GuessUntilZero::GuessUntilZero() {
    char temp[14] = "Guess to zero";
    char* init_game_name = new char[14];
    strcpy(init_game_name, temp);
    this->game_name = init_game_name;
}


#endif //HW2_GUESSUNTILZERO_H
