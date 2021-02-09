//
// Created by agirm on 09/02/2021.
//

#include "OutputManager.h"
#include "../settings/GameSettings.h"
#include <iostream>
#include <stdio.h>
#define SCREEN_WIDTH 76 // Width in characters
#define SCREEN_HEIGHT 15 // height including top and bottom border
// Defaults to insert into
#define TOP_BOTTOM_BORDER " --------------------------------------------------------------------------- "
#define EMPTY_LINE        "|                                                                           |"
#define GAME_MODE_SCORE   "|  GAME MODE:                                               SCORE:          |"
#define LIVES             "|                                                           LIVES:          |"
#define MULTIPLIER        "|                                                           MP:             |"
#define MESSAGE_SEPARATOR "|---------------------------------------------------------------------------|"

// Row numbers of each element (index)
#define MESSAGE_ROW 13
#define GAME_MODE_SCORE_ROW 2
#define LIVES_ROW 3
#define MP_ROW 4

// Starting index of inserts
#define GAME_MODE_POS 13
#define STATS_POS 58
#define MP_POS 61
#define LIVES_POS 64
#define SCORE_POS 64
using namespace std;

void set_empty_default(char** frames){
    for (int i=0; i<SCREEN_HEIGHT; i++){
        // Set the top and bottom borders
        if (i==0 || i==SCREEN_HEIGHT-1){
            strcpy(frames[i], TOP_BOTTOM_BORDER);
        }
            // Set all the other borders
        else if (i==GAME_MODE_SCORE_ROW){
            strcpy(frames[i], GAME_MODE_SCORE);
        }
        else if (i==LIVES_ROW){
            strcpy(frames[i], LIVES);
        }
        else if (i==MP_ROW){
            strcpy(frames[i], MULTIPLIER);
        }
        else if (i==MESSAGE_ROW-1){
            strcpy(frames[i], MESSAGE_SEPARATOR);
        }
        else {
            strcpy(frames[i], EMPTY_LINE);
        }
    }
}

void replace_centered(char** frames, char* replacement, int replacement_size, int row){
    if (row>SCREEN_HEIGHT-1){
        cout << "WARNING: Screen height exceeded in replacement." << endl;
        return;
    }
    strcpy(frames[row], EMPTY_LINE);

    int center = (int) SCREEN_WIDTH/2;
    int start_pos = center - (int)(replacement_size/2);
    for (int i=0; i<replacement_size; i++){
        frames[row][start_pos+i]=replacement[i];
    }

}

void replace_score(char** frames, int score){
    char buffer [10];
    int size = sprintf(buffer, "%d", score);
    for (int i=0; i<size; i++){
        frames[GAME_MODE_SCORE_ROW][SCORE_POS+i]=buffer[i];
    }
    for (int i=0; i<(SCREEN_WIDTH-2)-(SCORE_POS+size); i++){
        frames[GAME_MODE_SCORE_ROW][SCORE_POS+size+i] = ' ';
    }
}

void replace_game(char** frames, char* game){
    char temp_score_save[SCREEN_WIDTH];
    strcpy(temp_score_save, frames[GAME_MODE_SCORE_ROW]);
    char curr_char = game[0];
    int cnt_idx = 0;
    while(curr_char!='\0' && curr_char!='\n'){
        frames[GAME_MODE_SCORE_ROW][cnt_idx+GAME_MODE_POS]=curr_char;
        cnt_idx++;
        curr_char=game[cnt_idx];
    }
    for (int i=GAME_MODE_POS+cnt_idx; i<SCREEN_WIDTH; i++){
        frames[GAME_MODE_SCORE_ROW][i]=temp_score_save[i];
    }
}

void replace_mp(char** frames, double multiplier){
    strcpy(frames[MP_ROW], MULTIPLIER);
    char buffer[4];
    int size = sprintf(buffer, "%f", multiplier);
}

void OutputManager::_init_output_manager(GameType& game_type) {
    this->current_game = game_type.name();
    char** new_frame = new char*[SCREEN_HEIGHT];
    for (int i=0; i<SCREEN_HEIGHT; i++){
        new_frame[i]= new char[SCREEN_WIDTH];
        // Set the top and bottom borders
        if (i==0 || i==SCREEN_HEIGHT-1){
            strcpy(new_frame[i], TOP_BOTTOM_BORDER);
        }
        // Set all the other borders
        else if (i==GAME_MODE_SCORE_ROW){
            strcpy(new_frame[i], GAME_MODE_SCORE);
        }
        else if (i==LIVES_ROW){
            strcpy(new_frame[i], LIVES);
        }
        else if (i==MP_ROW){
            strcpy(new_frame[i], MULTIPLIER);
        }
        else if (i==MESSAGE_ROW-1){
            strcpy(new_frame[i], MESSAGE_SEPARATOR);
        }
        else {
            strcpy(new_frame[i], EMPTY_LINE);
        }
    }

}

void OutputManager::start() {
    // Desired outcome example
    cout << " -------------------------------------------------------------------------- " << endl;
    cout << "|  GAME MODE:                                               SCORE: 0       |" << endl;
    cout << "|                                                           LIVES: 10      |" << endl;
    cout << "|                                                           MP: 1x         |" << endl;
    cout << "|                          WELCOME TO WORD JUMBLE!                         |" << endl;
    cout << "|                                                                          |" << endl;
    cout << "|                                  Play (P)                                |" << endl;
    cout << "|                             Switch game mode (S)                         |" << endl;
    cout << "|                                Highscores (H)                            |" << endl;
    cout << "|                                                                          |" << endl;
    cout << "|                                                                          |" << endl;
    cout << "|                                  Exit (Q)                                |" << endl;
    cout << "|--------------------------------------------------------------------------|" << endl;
    cout << "|                           MESSAGES COME HERE                             |" << endl;
    cout << " -------------------------------------------------------------------------- " << endl;
}

void OutputManager::switch_game(GameType &game_type) {
    this->current_game = game_type.name();
    replace_game(this->frame, this->current_game);
}
