//
// Created by agirm on 11/02/2021.
//

#ifndef HW2_HIGHSCORES_H
#define HW2_HIGHSCORES_H


class Highscores {
    friend int getScore(char* line);
    friend char* getWordlist(char* line);
    friend int getCorrectWords(char* line);
    friend int getCharsCorrected(char* line);
    friend char* getLineBufferDelimited(char* line, int delimiter);
    friend char* createLine(int score, char* wordlist, int corr_words, int corr_char);
public:
    char** getHighscores(int howMany);
    char** getAllHighscores();
};


#endif //HW2_HIGHSCORES_H
