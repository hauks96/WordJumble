//
// Created by agirm on 09/02/2021.
//

#ifndef HW2_OUTPUTMANAGER_H
#define HW2_OUTPUTMANAGER_H
#include "../gametype/GameType.h"
// For each
class OutputManager {
    // Add a string to the center of a given row in the frame
    friend void replace_centered(char** frames, char* replacement, int replacement_size, int row);
    // Update the score in the frame
    friend void replace_score(char** frames, int score);
    // Update the current game
    friend void replace_game(char** frames, char* game);
    // Update the multiplier
    friend void replace_mp(char** frames, double multiplier);
    // Update the lives in the frame
    friend void replace_lives(char** frames, int lives);
    // Set the empty default frame
    friend void set_empty_default(char** frames);
public:
    // initialize the class with default values
    void _init_output_manager(GameType& game_type);
    // Prints the start screen
    void start();
    // Prints the quit message
    void end();
    // Prints the in game view
    void play(char* scrambled_word, int score, double mp, int lives);
    // Prints a message with the current frame
    void add_message(char* message);
    // Switch game
    void switch_game(GameType& game_type);
private:
    void reset_frames();
    char** frame;       // The current display
    char* current_game; // String defines the name of the current game
    int idx_start_score;
    int idx_start_lives;
    int idx_start_multiplier;
};

#endif //HW2_OUTPUTMANAGER_H
