//
// Created by agirm on 11/02/2021.
//
#include "../Highscores.h"
#include "../Highscores.cpp"
#include <iostream>
using namespace std;
int main(){
    Highscores highscores;
    bool error = false;
    cout << "TESTING: Get highscores - ";
    char*** highscores_gotten = highscores.getHighscores(-1, true);

    for (int i=0; i<highscores.numberOfHighscores(); i++){
        std::cout << "Score: " << highscores_gotten[i][0] << " Username: " << highscores_gotten[i][1] << std::endl;
    }
    return 0;
}
