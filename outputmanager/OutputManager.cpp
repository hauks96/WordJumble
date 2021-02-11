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
#define HIGHSCORE_ROW     "| Nr |  Score   |     User    |     Wordlist    |    Words    |   Letters   |"
#define HIGHSCORE_EMPTY   "|    |          |             |                 |             |             |"
// Positions for highscore table
#define NR_START_POS 2
#define NR_MAX_POS 5
#define SCORE_START_POS 7
#define SCORE_MAX_POS 15
#define USER_START_POS 18
#define USER_MAX_POS 30
#define WL_START_POS 32
#define WL_MAX_POS 48
#define WORDS_START_POS 50
#define WORDS_MAX_POS 62
#define LETTERS_START_POS 64
#define LETTERS_MAX_POS 75
#define NR_OF_COLUMNS 5

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
    /* Clear the display */
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
    // Replace a frames content in the center with a given string
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
    // Replace a given position in a frame with a new string
    for(int i=0; i<replacement_size; i++){
        row_frame[replacement_start_index+i]=replacement[i];
    }
}

void replace_score(char** frames, int score){
    // convert number to char array
    char buffer [10];
    int size = sprintf(buffer, "%d", score);
    // Insert into frame layout at a given position
    for (int i=0; i<size; i++){
        frames[GAME_MODE_SCORE_ROW][SCORE_POS+i]=buffer[i];
    }
    for (int i=0; i<(SCREEN_WIDTH-2)-(SCORE_POS+size); i++){
        frames[GAME_MODE_SCORE_ROW][SCORE_POS+size+i] = ' ';
    }
}

void replace_word(char** frames, GuessWord& gw){
    // Some defaults you don't need to worry about
    char split_char = ' ';
    char above_word_char = '-';
    int word_row = 6;
    int above_row = 5;
    // initialize default
    strcpy(frames[word_row], EMPTY_LINE);
    strcpy(frames[above_row], EMPTY_LINE);
    /* create arrays double the size of the word to
     * display it with whitespaces between characters */
    char word_replacement[gw.word_size*2];
    char above_word_stuff[gw.word_size*2];
    for (int i=0; i<gw.word_size; i++){
        word_replacement[i*2]=gw.scrambled_word[i];
        word_replacement[i*2+1]=split_char;
        above_word_stuff[i*2]=above_word_char;
        above_word_stuff[i*2+1]=split_char;
    }
    // replace frame at given position with the created strings
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
    // Get the size of a string
    char str_char = string[0];
    int size = 0;
    while(str_char!='\n' && str_char!='\0'){
        size++;
        str_char = string[size];
    }
    return size;
}

void replace_fixed_with_max(char* row_frame, char* replacement, int replacement_size, int replacement_start_index, int max_index){
    // Replace a strings content at a given position
    for(int i=0; i<replacement_size; i++){
        // Stop inserting into frame if the max index is exceeded
        if (i+replacement_start_index>max_index){
            break;
        }
        // insert into the frame at desired position
        row_frame[replacement_start_index+i]=replacement[i];
    }
}

char** highscore_rows(char*** highscores_array,  int number_to_show){
    /* Create the desired row layout with the highscore data */
    char** rows = new char*[number_to_show];
    for (int i=0; i<number_to_show; i++){
        // The current row we are creating
        char* curr_row = new char[SCREEN_WIDTH];
        // The data set for the current row
        char** row_cols = highscores_array[i];
        // Initialize an empty highscore table row
        strcpy(curr_row, HIGHSCORE_EMPTY);
        // Convert int to string
        char buffer [10];
        int size_num = sprintf(buffer, "%d", i+1);
        // Insert all the data elements into the row layout
        replace_fixed_with_max(curr_row, buffer, size_num, NR_START_POS, NR_MAX_POS);
        replace_fixed_with_max(curr_row, row_cols[0], get_string_size(row_cols[0]), SCORE_START_POS, SCORE_MAX_POS);
        replace_fixed_with_max(curr_row, row_cols[1], get_string_size(row_cols[1]), USER_START_POS, USER_MAX_POS);
        replace_fixed_with_max(curr_row, row_cols[2], get_string_size(row_cols[2]), WL_START_POS, WL_MAX_POS);
        replace_fixed_with_max(curr_row, row_cols[3], get_string_size(row_cols[3]), WORDS_START_POS, WORDS_MAX_POS);
        replace_fixed_with_max(curr_row, row_cols[4], get_string_size(row_cols[4]), LETTERS_START_POS, LETTERS_MAX_POS);
        rows[i]=curr_row;
    }

    // Delete the array after use
    for (int i=0; i<number_to_show; i++){
        for (int j=0; j<NR_OF_COLUMNS; j++){
            delete highscores_array[i][j];
        }
        delete highscores_array[i];
    }
    return rows;
}

void OutputManager::init_output_manager(GameType& game_type) {
    this->current_game = game_type.name();
    char** new_frame = new char*[SCREEN_HEIGHT];
    /* Construct the default layout */
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
    /* Construct the default layout */
    set_empty_default(this->frame);
    // Some hardcoded default positions for the elements shown on screen
    int welcome_message_row = 4;
    int play_button_row = 6;
    int switch_game_row = 7;
    int highscore_row = 9;
    int exit_row = 11;
    int wordlist_row = 8;
    // The displayed messages on the corresponding indexes
    char welcome[]="WELCOME TO WORD JUMBLE!";
    char play[]="Play (P)";
    char switch_game[]="Switch game mode (S)";
    char highscore[]="Highscores (H)";
    char exit[]="Exit (Q)";
    char msg[]="Enter a command to continue.";
    char word_list[]="Switch word list (W)";
    // Insert the displayed elements into out frames
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
        // Construct the layout with some helper functions
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
    // Update stats on screen
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

void OutputManager::word_lists(char **word_lists, char *current_wordlist, int word_lists_size, char* msg) {
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
    // Clean the screen
    set_empty(this->frame);

    /* Construct the layout with the helper functions */

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
    replace_centered(this->frame, msg, get_string_size(msg), MESSAGE_ROW);

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
    // If wordlist would exceed screen size print them as extras
    if (word_lists_size<7){
        int extra_rows = 7-word_lists_size;
        for (int i=0; i<extra_rows; i++){
            cout << EMPTY_LINE << endl;
        }
    }
    // If there are remaining spaces left to fill the default screen size we add some paddings
    for (int i=10; i<SCREEN_HEIGHT; i++){
        cout << this->frame[i] << endl;
    }
}

void OutputManager::highscores(char*** highscores_array, int max_number, int number_to_show, bool is_init){
    /* Desired outcome example
     0 " -------------------------------------------------------------------------- "
     1 "|                                HIGHSCORES                                |"
     2  |                    ENTER AMOUNT OF HIGHSCORES TO VIEW. MAX IS XXXX       |
     3  |--------------------------------------------------------------------------|
     4 "| Nr |  Score   |     User    |     Wordlist    |    Words    |   Letters  |"
     5 "|                                                                          |"
    11 "|                                  Back (B)                                |"
    12 "|--------------------------------------------------------------------------|"
    13 "|                    ENTER AMOUNT OF HIGHSCORES TO VIEW. MAX IS XXXX       |"
    14 " -------------------------------------------------------------------------- " */
    if (is_init){
        // Wipe the screen
        set_empty(this->frame);
        // Add the default layout

        // Title
        char title[] = "HIGHSCORES";
        replace_centered(this->frame, title, get_string_size(title), 1);
        strcpy(this->frame[3], MESSAGE_SEPARATOR);
        strcpy(this->frame[4], HIGHSCORE_ROW);

        /* Create a new message */
        char msg[] = "Enter amount of highscores to view. [Max: ";
        int size_msg = get_string_size(msg);
        // get the number as string
        char buffer [10];
        int size_num = sprintf(buffer, "%d", max_number);
        char new_msg[size_msg+size_num+2];
        // Join the two strings
        strcpy(new_msg, msg);
        for (int i=0; i<size_num; i++){
            if (i==size_num-1){
                new_msg[i+size_msg]=buffer[i];
                new_msg[i+1+size_msg]=']';
                new_msg[i+2+size_msg]='\0';
                break;
            }
        }
        replace_centered(this->frame, new_msg, get_string_size(new_msg), 2);

        // Add back btn
        char back[] = "Back (BACK)";
        replace_centered(this->frame, back, 11, 11);

        // If there's no highscores to print, print the default layout and return
        if (number_to_show==0 || highscores_array== nullptr){
            print_frames(this->frame);
            return;
        }
    }

    // Print the highscore default frames up to index 5
    char** highscores_frames = highscore_rows(highscores_array, number_to_show);
    for (int i=0; i<5; i++){
        cout << this->frame[i] << endl;
    }
    // Print the highscores
    for (int i=0; i<number_to_show; i++){
        cout << highscores_frames[i] << endl;
    }
    // Print the remaining default frames
    for (int i=10; i<SCREEN_HEIGHT; i++){
        cout << this->frame[i] << endl;
    }

    // Delete the array after use
    for (int i=0; i<number_to_show; i++){
        delete highscores_frames[i];
    }
    delete highscores_frames;
}

void OutputManager::gameOver() {
    // Some hardcoded indexes that you don't have to worry about :P
    int start_row = 5;
    int end_row_plus_1 = 11;
    // Insert game over message
    strcpy(this->frame[4], EMPTY_LINE);
    char title[]="GAME OVER!";
    replace_centered(this->frame, title, 10, 4);

    // Wipe fields clean that are not supposed to be in the game over layout
    for (int i=start_row; i<end_row_plus_1; i++){
        strcpy(this->frame[i], EMPTY_LINE);
    }
    print_frames(this->frame);
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

void OutputManager::print() {
    print_frames(this->frame);
}