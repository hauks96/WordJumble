//
// Created by agirm on 06/02/2021.
//
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "GameManager.h"
#include "../score/Score.h"
#include "../score/Score.cpp"
#include "../timer/Timer.h"
#include "../timer/Timer.cpp"
#include "../settings/GameSettings.h"
#include "../settings/GameSettings.cpp"
#include "../gametype/GuessToSeven.h"
#include "../gametype/GuessUntilZero.h"
#include "../gametype/GameType.h"
#include "../words/WordReader.h"
#include "../words/WordReader.cpp"
#include "../words/GuessWord.h"
#include "../outputmanager/OutputManager.h"
#include "../outputmanager/OutputManager.cpp"

GameManager::GameManager() {
    this->score.init_score(this->settings);
    this->words.init_word_reader(this->settings.default_wordlist);
    GameType* init_type = new GuessUntilZero();
    this->type = init_type;
    this->user.init_output_manager(*init_type);
    this->game_over = false;
}

void GameManager::start() {
    this->user.start();
    char input_string[256];
    while(true){
        std::cin >> input_string;
        if (strcmp(input_string, "P")==0){
            this->play();
            if (this->game_over){
                // Wait for user to want to go back to main menu
                while(true){
                    std::cin >> input_string;
                    if (strcmp(input_string, "B")!=0){
                        char msg[]="Command not recognized!";
                        this->user.add_message(msg, true);
                    }
                    else{
                        break;
                    }
                }
            }
            // Go back to start menu
            this->user.start();
            this->game_over=false;
        }
        // Exit game
        else if (strcmp(input_string, "Q")==0){
            return;
        }
        // Switch game mode
        else if (strcmp(input_string, "S")==0){
            this->switchGameMode();
        }
        // Set a new wordlist
        else if (strcmp(input_string, "W")==0){
            this->selectWordList();
            this->user.start();
        }
        // Go to highscores...

        // Command not recognized
        else{
            char msg[]="Command not recognized!";
            this->user.add_message(msg, true);
        }
    }
}

bool checkGameOver(GameManager& gm){
    bool game_over = gm.type->checkGameOver(gm.score);
    if (game_over){
        gm.score.reset();
        gm.time.reset_time();
        gm.words.reset();
        return true;
    }
    return false;
}

void GameManager::play(){
    if (this->score.getCurrentPoints()<=0){
        std::cout << "WARNING: Less than zero lives left." << std::endl;
        std::runtime_error("Less than 0 lives left when play was called");
    }
    this->time.start_time();
    this->words.fetchWord();
    this->user.play(this->type->name(), *this->words.latest_word, this->score.getCurrentScore(), this->score.getCurrentMultiplier(), this->score.getCurrentPoints(), true);

    char input_string[256];
    while(true){
        std::cin >> input_string;
        if (strcmp("B", input_string)==0){
            // Add to highscores
            // this->highscores.add(this->score.getCurrentScore());
            this->score.reset();
            this->time.reset_time();
            this->words.reset();
            return; // Return to start method
        }
        // Get a guess word from user
        else if (strcmp("G", input_string)==0){
            this->guess();
            if (this->game_over){
                return;
            }
        }
        // Give user a hint
        else if (strcmp(input_string, "H")==0){
            this->getHint();
        }
        // Command not recognized
        else {
            char msg[]= "Command not recognized!";
            this->user.add_message(msg, true);
        }
    }
}

void GameManager::nextWord() {
    if (this->score.getCurrentPoints()<=0){
        std::cout << "WARNING: Less than zero lives left." << std::endl;
        std::runtime_error("Less than 0 lives left when play was called");
    }
    if (!this->words.remainingWords()){
        return;
    }
    this->time.reset_time();
    this->words.fetchWord();
    this->time.start_time();
    this->user.play(this->type->name(), *this->words.latest_word, this->score.getCurrentScore(), this->score.getCurrentMultiplier(), this->score.getCurrentPoints(), true);
}

void GameManager::switchGameMode() {
    char guess_seven[] = "Guess seven words";
    char guess_zero[] = "Guess to zero";
    if (strcmp(this->type->name(), guess_seven)==0){
        delete this->type;
        this->type = new GuessUntilZero();
        char msg[] = "Game mode switched!";
        this->user.add_message(msg, false);
        this->user.switch_game(*this->type);
    }
    else if (strcmp(this->type->name(),guess_zero)==0){
        delete this->type;
        this->type = new GuessToSeven();
        char msg[] = "Game mode switched!";
        this->user.add_message(msg, false);
        this->user.switch_game(*this->type);
    }
    else {
        std::cout << "WARNING: Game type did not match any predefined game modes." << std::endl;
        std::runtime_error("Game type not found");
    }
}

void GameManager::selectWordList() {
    char msg[] = "Enter number of desired wordlist to select it.";
    this->user.word_lists(this->words.availableWordLists(), this->words.currentWordList(), this->words.availableWordListSize(), msg);
    char input_string[256];
    while(true){
        std::cin >> input_string;
        if (strcmp(input_string, "B")==0){
            return;
        }
        else if ((atoi (input_string))<this->words.availableWordListSize()+1){
            int idx = (atoi (input_string))-1;
            this->words.switchWordlist(idx);
            char msg[]="Word list switched!";
            this->user.word_lists(this->words.availableWordLists(), this->words.currentWordList(), this->words.availableWordListSize(), msg);
        }
        else {
            char msg[] = "Command not recognized!";
            this->user.word_lists(this->words.availableWordLists(), this->words.currentWordList(), this->words.availableWordListSize(), msg);
        }
    }
}

void GameManager::getHint() {
    if (strcmp(this->words.latest_word->scrambled_word, this->words.latest_word->word)==0){
        char msg[] = "Word is already correct you egg!";
        this->user.add_message(msg, true);
        return;
    }
    // If a new hint would end game don't add the hint
    if (this->score.getCurrentPoints()==1){
        char msg[]="Only one live left! Cannot add a new hint.";
        this->user.add_message(msg, true);
        return;
    }
        // Add hint
    else {
        char msg[]="Hint added!";
        this->user.add_message(msg, false);
        this->score.decreasePoints(1);
        this->words.addHint();
        this->user.play(this->type->name(), *this->words.latest_word, this->score.getCurrentScore(), this->score.getCurrentMultiplier(), this->score.getCurrentPoints(), true);
    }
}

void GameManager::guess() {
    char guess_msg[] = "Enter your guess!";
    this->user.add_message(guess_msg, true);
    char input_string[256];
    std::cin >> input_string;
    // If the word was correct
    if (this->words.latest_word->isEqual(input_string)){
        this->score.updateScore(*this->words.latest_word, this->time);
        this->user.play(this->type->name(), *this->words.latest_word, this->score.getCurrentScore(), this->score.getCurrentMultiplier(), this->score.getCurrentPoints(), false);
        bool game_over = checkGameOver(*this);
        char msg[] = "CORRECT!";
        this->user.add_message(msg, false);
        if (game_over){
            this->user.add_message(msg, false);
            this->user.gameOver();
            this->game_over=true;
            return;
        }
        else if (!this->words.remainingWords()){
            char msg[] = "No more words in wordlist!";
            this->user.add_message(msg, false);
            this->user.gameOver();
            this->score.reset();
            this->time.reset_time();
            this->words.reset();
            this->game_over=true;
            return;
        }
        nextWord();
        return;
    }
        // If the word was incorrect
    else {
        this->score.decreasePoints(1);
        this->user.updateLives(this->score.getCurrentPoints(), false);
        char msg[] = "INCORRECT!";
        this->user.play(this->type->name(), *this->words.latest_word, this->score.getCurrentScore(), this->score.getCurrentMultiplier(), this->score.getCurrentPoints(), false);
        this->user.add_message(msg, false);
        bool game_over = checkGameOver(*this);
        if (game_over){
            this->user.gameOver();
            this->game_over=true;
            return;
        }else{
            this->user.add_message(msg, true);
        }
    }
}