//
// Created by agirm on 07/02/2021.
//
#include "GameSettings.h"
#include "../score/Score.h"
#include <iostream>
#include <cstring>

#define DEFAULT_WORD_FILE "programming"
#define HIGHSCORE_FILE "highscores.txt"
#define DEFAULT_WORD_FILE_NAME_SIZE 12
#define STARTING_POINTS 10 // Lives
#define SCORE_PER_CHARACTER 100 // Each character gives a score of 100
#define SCORE_TIME_MULTIPLIER 0.5 // Fast answer multiplier - goes back to 1 on surpassing time limit for a word
#define SCORE_MULTIPLIER_TIME_LIMIT 20 //
#define GUESSED_WORD_BASE_SCORE 500 // Base score for guessing a word

// Defining the private method - I did this before I knew what a friend is so and I'm too lazy to change it :)
struct GameSettings::Loader {
    static void load_settings(GameSettings& self){
        char temp[] = DEFAULT_WORD_FILE;
        char* init_default_wordlist = new char[12];
        strcpy(init_default_wordlist, temp);
        self.default_wordlist = init_default_wordlist;
        self.starting_points = STARTING_POINTS;
        self.score_mp_time_limit = SCORE_MULTIPLIER_TIME_LIMIT;
        self.score_per_time_mp = SCORE_TIME_MULTIPLIER;
        self.score_per_correct_char = SCORE_PER_CHARACTER;
        self.word_base_score = GUESSED_WORD_BASE_SCORE;
        char temp_hs[]=HIGHSCORE_FILE;
        char* init_default_highscore = new char[20];
        strcpy(init_default_highscore, temp_hs);
        self.highscore_file = init_default_highscore;
    }
};

GameSettings::GameSettings() {
    Loader::load_settings(*this);
}

