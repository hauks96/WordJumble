//
// Created by agirm on 06/02/2021.
//
#include <iostream>
#include "gamemanager/GameManager.h"
#include "gamemanager/GameManager.cpp"
#include <windows.h>
#include <future>
#include <thread>

int main(){

    GameManager game_manager;
    game_manager.start();
    /*
    game_manager.user.start();
    game_manager.words.fetchWord();
    std::cout << "Word is: " << game_manager.words.latest_word->word << std::endl;
    char input_buffer[128];
    std::cin >> input_buffer;

    if (strcmp("Q", input_buffer)==0){
        game_manager.user.play(*game_manager.words.latest_word,game_manager.type->name(), 0, 1, 10);
    }
    if (strcmp("W", input_buffer)==0){
        game_manager.user.word_lists(game_manager.words.availableWordLists(), game_manager.words.currentWordList(), game_manager.words.availableWordListSize());
    }
     */
    return 0;
}
