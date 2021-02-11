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
    std::cout << "SIZE OF HIGHSCORES: " << highscores.numberOfHighscores() << std::endl;
    char*** highscores_gotten = highscores.getHighscores(-1, true);
    for (int i=0; i<highscores.numberOfHighscores(); i++){
        std::cout << "Score: " << highscores_gotten[i][0] << " Username: " << highscores_gotten[i][1] << std::endl;
    }
    char username[]="Palli";
    char wordlist[]="Some wordlist";
    int score = 140;
    int correct_words = 60;
    int correct_chars = 150;
    highscores.addHighscore(score, username, wordlist, correct_words, correct_chars);
    std::cout << "HIGHSCORE COUNT " << highscores.numberOfHighscores() << std::endl;
    return 0;
}
