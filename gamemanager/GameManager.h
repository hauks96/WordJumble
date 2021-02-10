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
#include "../outputmanager/OutputManager.h"
class GameManager {
    //friend void in_game_input(GameManager& gm);
    friend bool checkGameOver(GameManager& gm);
public:
    GameManager();
    GameSettings settings;
    OutputManager user;
    WordReader words;
    GameType* type;
    Score score;
    Timer time;
    // Switch to a different game mode (start menu)
    void switchGameMode();
    // Start menu
    void start();
    // Goodbye message
    void end();
    // Guess the current word (in game)
    void guess();
    // Get a hint on the current word (in game)
    void getHint();
    // Play a game (in game)
    void play();
    // Get the next word
    void nextWord();
    // Restart the game (restart current game mode)
    void restart();
    // Word Lists (word list menu)
    void selectWordList();
    // View highscores (highscore menu)
    void highscores();
private:
    bool game_over;

};


#endif //HW2_GAMEMANAGER_H
