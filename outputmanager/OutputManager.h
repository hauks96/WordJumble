#ifndef HW2_OUTPUTMANAGER_H
#define HW2_OUTPUTMANAGER_H
#include "../gametype/GameType.h"

class OutputManager {
    // Add a string to the center of a given row in the frame
    friend void replace_centered(char** frames, char* replacement, int replacement_size, int row);
    // Add a string given a position
    friend void replace_fixed(char* row_frame, char* replacement, int replacement_size, int replacement_start_index);
    // Replace fixed with a max
    friend void replace_fixed_with_max(char* row_frame, char* replacement, int replacement_size, int replacement_start_index, int max_index);
    // Update the score in the frame
    friend void replace_score(char** frames, int score);
    // Update the current game
    friend void replace_game(char** frames, char* game);
    // Update game mode
    friend void replace_word(GuessWord& gw, char** frames);
    // Update the multiplier
    friend void replace_mp(char** frames, double multiplier);
    // Update the lives in the frame
    friend void replace_lives(char** frames, int lives);
    // create highscore table row
    friend char** highscore_rows(char*** highscores_array, int number_to_show);
    // Set the empty default frame
    friend void set_empty_default(char** frames);
    // Set completely empty
    friend void set_empty(char** frames);
    // Prints the frame
    friend void print_frame(char** frames);
public:
    // initialize the class with default values
    void init_output_manager(GameType& game_type);
    // Prints the start screen
    void start(bool print, bool defaultMessage);
    // Prints the in game view
    void play(char* current_game_mode, GuessWord& gw, int score, double mp, int lives, bool print);
    // Print game over screen
    void gameOver();
    // Updates with new lives
    void updateLives(int lives, bool print);
    // Updates with new multiplier
    void updateMultiplier(double mp);
    // Prints a message with the current frame
    void add_message(char* message, bool print);
    // Switch game
    void switch_game(GameType& game_type);
    // Switch wordlist
    void word_lists(char** word_lists, char* current_wordlist, int word_lists_size, char* msg);
    // Highscores menu
    void highscores(char*** highscores_array, int max_number, int number_to_show, bool is_init);
    // print current
    void print();
private:
    void reset_frames();
    bool inGame;
    char** frame;       // The current display
    char* current_game; // String defines the name of the current game
};

#endif //HW2_OUTPUTMANAGER_H
