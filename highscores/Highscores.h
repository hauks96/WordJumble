//
// Created by agirm on 11/02/2021.
//

#ifndef HW2_HIGHSCORES_H
#define HW2_HIGHSCORES_H


class Highscores {
    friend char* getIntAsString(int number);
    friend int get_string_size(char* string);
    friend int getStringAsNumber(char* some_string);
    // All these methods just get a certain column from a file
    friend char* getScore(char* line);
    friend char* getWordlist(char* line);
    friend char* getCorrectWords(char* line);
    friend char* getCharsCorrected(char* line);
    // Gets a specific column from a line read in the word file (delimiter is comma)
    friend char* getLineBufferDelimited(char* line, int delimiter);
    // Create a line to store in the highscore file
    friend char* createLine(int score, char* wordlist, int corr_words, int corr_char);
public:
    // Add a new highscore to the highscore file
    void addHighscore(int score, char* username, char* wordlist, int correct_words, int correct_chars);
    // Get x highscores from the file
    char*** getHighscores(int howMany, bool all);
    // Get the count of the highscores that are in the highscore file
    int numberOfHighscores();
    // initialize highscores
    void init_highscores(char* filename);
private:
    char* filename;
    int number_of_highscores;
};


#endif //HW2_HIGHSCORES_H
