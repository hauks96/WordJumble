//
// Created by agirm on 09/02/2021.
//

#include "OutputManager.h"
#include "../settings/GameSettings.h"
#include <iostream>
#include <stdio.h>
#include "../words/GuessWord.h"

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
#define GAME_MODE_SCORE_ROW 1
#define LIVES_ROW 2
#define MP_ROW 3

// Starting index of inserts
#define GAME_MODE_POS 14
#define STATS_POS 58
#define MP_POS 64
#define LIVES_POS 67
#define SCORE_POS 67
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

void set_empty(char** frames){
    for (int i=0; i<SCREEN_HEIGHT; i++){
        if (i==0 || i==SCREEN_HEIGHT-1){
            strcpy(frames[i], TOP_BOTTOM_BORDER);
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

void replace_fixed(char* row_frame, char* replacement, int replacement_size, int replacement_start_index){
    for(int i=0; i<replacement_size; i++){
        row_frame[replacement_start_index+i]=replacement[i];
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

void replace_word(char** frames, GuessWord& gw){
    char split_char = ' ';
    char above_word_char = '-';
    int word_row = 6;
    int above_row = 5;
    strcpy(frames[word_row], EMPTY_LINE);
    strcpy(frames[above_row], EMPTY_LINE);
    char word_replacement[gw.word_size*2];
    char above_word_stuff[gw.word_size*2];
    for (int i=0; i<gw.word_size; i++){
        word_replacement[i*2]=gw.scrambled_word[i];
        word_replacement[i*2+1]=split_char;
        above_word_stuff[i*2]=above_word_char;
        above_word_stuff[i*2+1]=split_char;
    }
    replace_centered(frames, above_word_stuff, gw.word_size*2, above_row);
    replace_centered(frames, word_replacement, gw.word_size*2, word_row);
}

void replace_lives(char** frames, int lives){
    strcpy(frames[LIVES_ROW], LIVES);
    char buffer[2];
    int size = sprintf(buffer, "%d", lives);
    for (int i=0; i<size; i++){
        frames[LIVES_ROW][LIVES_POS+i]=buffer[i];
    }
}

void replace_game(char** frames, char* game){
    char curr_char = game[0];
    int cnt_idx = 0;
    while(curr_char!='\0' && curr_char!='\n'){
        frames[GAME_MODE_SCORE_ROW][cnt_idx+GAME_MODE_POS]=curr_char;
        cnt_idx++;
        curr_char=game[cnt_idx];
    }
    for (int i=GAME_MODE_POS+cnt_idx; i<SCORE_POS-7; i++){
        frames[GAME_MODE_SCORE_ROW][i]=GAME_MODE_SCORE[i];
    }
}

void replace_mp(char** frames, double multiplier){
    strcpy(frames[MP_ROW], MULTIPLIER);
    char buffer[4];
    int size = sprintf(buffer, "%f", multiplier);
    for (int i=0; i<4; i++){
        frames[MP_ROW][MP_POS+i]=buffer[i];
    }
}

void print_frames(char** frames){
    for (int i=0; i<SCREEN_HEIGHT; i++){
        cout << frames[i] << endl;
    }
}

int get_string_size(char* string){
    char str_char = string[0];
    int size = 0;
    while(str_char!='\n' && str_char!='\0'){
        size++;
        str_char = string[size];
    }
    return size;
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
    this->frame = new_frame;
    this->inGame=false;
}

void OutputManager::start() {
    this->inGame=false;
    /* Desired outcome example
     0 " -------------------------------------------------------------------------- "
     1 "|  GAME MODE: xxx                                             SCORE:       |"
     2 "|                                                           LIVES:         |"
     3 "|                                                           MP:            |"
     4 "|                          WELCOME TO WORD JUMBLE!                         |"
     5 "|                                                                          |"
     6 "|                                  Play (P)                                |"
     7 "|                             Switch game mode (S)                         |"
     8 "|                             Switch word list (W)                         |"
     9 "|                                Highscores (H)                            |"
    10 "|                                                                          |"
    11 "|                                  Exit (Q)                                |"
    12 "|--------------------------------------------------------------------------|"
    13 "|                           MESSAGES COME HERE                             |"
    14 " -------------------------------------------------------------------------- " */
    set_empty_default(this->frame);
    int welcome_message_row = 4;
    int play_button_row = 6;
    int switch_game_row = 7;
    int highscore_row = 9;
    int exit_row = 11;
    int wordlist_row = 8;
    char welcome[]="WELCOME TO WORD JUMBLE!";
    char play[]="Play (P)";
    char switch_game[]="Switch game mode (S)";
    char highscore[]="Highscores (H)";
    char exit[]="Exit (Q)";
    char msg[]="Enter a command to continue.";
    char word_list[]="Switch word list (W)";
    replace_centered(this->frame, welcome, 23, welcome_message_row);
    replace_centered(this->frame, play, 8, play_button_row);
    replace_centered(this->frame, switch_game, 20, switch_game_row);
    replace_centered(this->frame, highscore, 14, highscore_row);
    replace_centered(this->frame, exit, 8, exit_row);
    replace_centered(this->frame, word_list, 20, wordlist_row);
    replace_game(this->frame, this->current_game);
    this->add_message(msg, true);
}

void OutputManager::play(char* current_game_mode, GuessWord& gw, int score, double mp, int lives, bool print) {
    /*0 " -------------------------------------------------------------------------- "
      1 "|  GAME MODE:                                               SCORE: 0       |"
      2 "|                                                           LIVES: 10      |"
      3 "|                                                           MP: 1x         |"
      4 "|                              YOUR WORD IS:                               |"
      5 "|                               _ _ _ _ _ _                                |"
      6 "|                               K R O K S A                                |"
      7 "|                                                                          |"
      8 "|                                Hint (H)                                  |"
      9 "|                              Guess word (G)                              |"
     10 "|                                                                          |"
     11 "|                               Main Menu (B)                              |"
     12 "|--------------------------------------------------------------------------|"
     13 "|                           MESSAGES COME HERE                             |"
     14 " -------------------------------------------------------------------------- " */
    // If not already in game we first need to wipe the screen clean and set the defaults
    if (!this->inGame) {
        set_empty_default(this->frame);
        char title[] = "YOUR WORD IS:";
        int title_row = 4;
        replace_centered(this->frame, title, 13, title_row);
        char hint[] = "Hint (H)";
        int hint_row = 8;
        replace_centered(this->frame, hint, 8, hint_row);
        char guess_word[] = "Guess word (G)";
        int guess_word_row = 9;
        replace_centered(this->frame, guess_word, 14, guess_word_row);
        char main_menu[] = "Main Menu (B)";
        int main_menu_row = 11;
        replace_centered(this->frame, main_menu, 14, main_menu_row);
    }
    // Update stats
    replace_score(this->frame, score);
    replace_mp(this->frame, mp);
    replace_lives(this->frame, lives);
    replace_game(this->frame, current_game_mode);
    replace_word(this->frame, gw);
    this->inGame=true;
    if (print){
        print_frames(this->frame);
    }
}

void OutputManager::switch_game(GameType &game_type) {
    if (this->inGame){
        char msg[]="Cannot switch game while playing.";
        this->add_message(msg, true);
        return;
    }
    this->current_game = game_type.name();
    replace_game(this->frame, this->current_game);
    print_frames(this->frame);
}

void OutputManager::add_message(char *message, bool print) {
    strcpy(this->frame[MESSAGE_ROW], EMPTY_LINE);
    int msg_size = 0;
    char msg_char = message[0];
    // Get size of word
    while(msg_char!='\0' && msg_char!='\n'){
        msg_size++;
        msg_char = message[msg_size];
    }
    replace_centered(this->frame, message, msg_size, MESSAGE_ROW);
    if (print){
        print_frames(this->frame);
    }
}

void OutputManager::word_lists(char **word_lists, char *current_wordlist, int word_lists_size) {
    /* Desired outcome example
     0 " -------------------------------------------------------------------------- "
     1 "|   Current wordlist:                                                      |"
     2 "|                                                                          |"
     3 "|                          AVAILABLE WORD LISTS:                           |"
     4 "|                                                                          |"
     5 "|                                                                          |"
     6 "|                                                                          |"
     7 "|                                                                          |"
     8 "|                                                                          |"
     9 "|                                                                          |"
    10 "|                                                                          |"
    11 "|                                 Back (B)                                 |"
    12 "|--------------------------------------------------------------------------|"
    13 "|                       ENTER NUMBER OF DESIRED LIST                       |"
    14 " -------------------------------------------------------------------------- " */
    set_empty(this->frame);
    // Title
    this->inGame=false;
    char title[] = "AVAILABLE WORD LISTS:";
    int title_row = 3;
    replace_centered(this->frame, title, 21, title_row);
    // Word list displayed in right corner
    char curr_wl[] = "Current wordlist: ";
    int curr_wl_row = 1;
    replace_fixed(this->frame[curr_wl_row], curr_wl, 18, 4);
    int str_size = get_string_size(current_wordlist);
    replace_fixed(this->frame[curr_wl_row], current_wordlist, str_size, 22);
    // Back btn
    char back[] = "Back (B)";
    int back_row = 11;
    replace_centered(this->frame, back, 8, back_row);
    // Message
    char msg[] = "ENTER NUMBER OF DESIRED LIST TO SELECT IT";
    replace_centered(this->frame,msg, get_string_size(msg), MESSAGE_ROW);

    int list_start_index_left = 10;

    // first 4 are default and fixed so just print them
    for (int i=0; i<4; i++){
        cout << this->frame[i] << endl;
    }
    // Print each list item
    for (int i=0; i<word_lists_size; i++){
        char temp_frame[] = EMPTY_LINE;
        char buffer[5];
        int size_num = sprintf(buffer, "%d. ", i+1);
        replace_fixed(temp_frame, buffer, size_num, list_start_index_left);
        replace_fixed(temp_frame, word_lists[i], get_string_size(word_lists[i]), list_start_index_left+size_num);
        cout << temp_frame << endl;
    }
    if (word_lists_size<7){
        int extra_rows = 7-word_lists_size;
        for (int i=0; i<extra_rows; i++){
            cout << EMPTY_LINE << endl;
        }
    }
    for (int i=11; i<SCREEN_HEIGHT; i++){
        cout << this->frame[i] << endl;
    }
}

void OutputManager::gameOver() {
    int start_row = 5;
    int end_row_plus_1 = 11;
    strcpy(this->frame[4], EMPTY_LINE);
    char title[]="GAME OVER!";
    replace_centered(this->frame, title, 10, 4);
    for (int i=start_row; i<end_row_plus_1; i++){
        strcpy(this->frame[i], EMPTY_LINE);
    }
}

void OutputManager::updateLives(int lives, bool print) {
    replace_lives(this->frame, lives);
    if (print){
        print_frames(this->frame);
    }
}
void OutputManager::updateMultiplier(double mp) {
    replace_mp(this->frame, mp);
    print_frames(this->frame);
}