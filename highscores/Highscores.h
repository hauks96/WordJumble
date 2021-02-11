//
// Created by agirm on 11/02/2021.
//

#ifndef HW2_HIGHSCORES_H
#define HW2_HIGHSCORES_H


class Highscores {
    friend char* getIntAsString(int number);
    friend int get_string_size(char* string);
    friend int getStringAsNumber(char* some_string);
    friend char* getScore(char* line);
    friend char* getWordlist(char* line);
    friend char* getCorrectWords(char* line);
    friend char* getCharsCorrected(char* line);
    friend char* getLineBufferDelimited(char* line, int delimiter);
    friend char* createLine(int score, char* wordlist, int corr_words, int corr_char);
public:
    void addHighscore(int score, char* username, char* wordlist, int correct_words, int correct_chars);
    char*** getHighscores(int howMany, bool all);
    int numberOfHighscores();
    void init_highscores(char* filename);
private:
    char* filename;
    int number_of_highscores;
};


#endif //HW2_HIGHSCORES_H
