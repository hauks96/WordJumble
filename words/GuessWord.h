//
// Created by agirm on 08/02/2021.
//

#ifndef HW2_GUESSWORD_H
#define HW2_GUESSWORD_H
#include <iostream>
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
        for (int i=0; i<word_size; i++){
            if (word[i]!=correct_letters[i]){
                return false;
            }
            if (i==word_size-1 && guessed_word[i+1]!='\0'){
                return false;
            }
        }
        return true;
    }
};
#endif //HW2_GUESSWORD_H
