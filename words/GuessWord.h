#ifndef HW2_GUESSWORD_H
#define HW2_GUESSWORD_H
#include <iostream>
#include <cstring>
struct GuessWord {
    char* word; // The correct word
    char* scrambled_word; // The scrambled version of the correct word
    bool* correct_letters; // Contains true in all fields that are correct in the scrambled word
    int word_size;
    int initially_correct_letters;
    bool isEqual(char* guessed_word){
        if (word_size==0 || word== nullptr){
            std::cout << "WARNING: Evaluating if word is guessed but no word initialized." << std::endl;
            return false;
        }
        if (strcmp(guessed_word, this->word)==0){
            return true;
        }
        return false;
    }
};
#endif //HW2_GUESSWORD_H
