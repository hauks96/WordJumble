//
// Created by agirm on 06/02/2021.
//

#ifndef HW2_GAMEMANAGER_H
#define HW2_GAMEMANAGER_H

#include "../score/Score.h"
#include "../timer/Timer.h"
#include "../settings/GameSettings.h"
#include "../gametype/GameType.h"
#include "../gametype/GuessUntilZero.h"
#include "../gametype/GuessToSeven.h"
#include "../words/WordReader.h"
#include "../inputmanager/OutputManager.h"
#include "../inputmanager/OutputManager.cpp"
class GameManager {

public:
    GameManager();
    GameSettings settings;
    OutputManager user;
    WordReader words;
    GameType* type;
    Score score;
    Timer time;
    // Guess the current word
    void guess();
    // Get a hint on the current word
    void getHint();
    // Switch to a different game mode
    void switchGameMode();
    // Start the program
    void start();
    // Quit the program
    void end();
    // Restart the game
    void restart();
    // Play a game
    void play();
};


#endif //HW2_GAMEMANAGER_H
