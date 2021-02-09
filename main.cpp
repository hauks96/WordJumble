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
    /*
    std::cout << game_manager.score.points << std::endl;
    game_manager.time.reset_time();
    std::cout << "Game type: " << game_manager.type->name() << std::endl;
    std::cout << "Current wordlist: " << game_manager.words.currentWordList() << std::endl;
    const char** wordlists = game_manager.words.availableWordLists();
    std::cout << "Available size: " << game_manager.words.availableWordListSize() << std::endl;
    for (int i=0; i<2; i++){
        if (i==1){
            std::cout << wordlists[i] << std::endl;
        }
        else{
            std::cout << wordlists[i] << ", ";
        }
    }
    game_manager.words.fetchWord();
    std::cout << "The word is: " << (game_manager.words.latest_word->word) << std::endl;
    std::cout << "The scrambled word is: " << (game_manager.words.latest_word->scrambled_word) << std::endl;
    game_manager.words.addHint();
    std::cout << "The scrambled word is: " << (game_manager.words.latest_word->scrambled_word) << std::endl;
    game_manager.words.addHint();
    std::cout << "The scrambled word is: " << (game_manager.words.latest_word->scrambled_word) << std::endl;
    game_manager.words.addHint();
    std::cout << "The scrambled word is: " << (game_manager.words.latest_word->scrambled_word) << std::endl;
    game_manager.words.addHint();
    std::cout << "The scrambled word is: " << (game_manager.words.latest_word->scrambled_word) << std::endl;
    game_manager.words.addHint();
    std::cout << "The scrambled word is: " << (game_manager.words.latest_word->scrambled_word) << std::endl;
    game_manager.words.addHint();
    std::cout << "The scrambled word is: " << (game_manager.words.latest_word->scrambled_word) << std::endl;
     */
    game_manager.user.start();
    char input_buffer[128];
    std::cin >> input_buffer;
    if (strcmp("Q", input_buffer)==0){

    }
    return 0;
}
