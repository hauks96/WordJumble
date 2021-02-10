//
// Created by agirm on 09/02/2021.
//

#include "../WordReader.h"
#include "../WordReader.cpp"
#include <iostream>
int main(){
    WordReader word_reader;
    char default_word_list[] = "test";

    /* INITIALIZATION TESTS */
    std::cout << "TESTING: WordReader.init_word_reader() - ";
    word_reader.init_word_reader(default_word_list);
    bool error = false;
    // Check that the wordlist is inserted properly
    if (strcmp(default_word_list, word_reader.currentWordList())!=0){
        std::cout << "ERROR: Invalid default wordlist set" << std::endl;
        error=true;
    }
    // Check that the word list counts the number of available word lists correctly
    if (word_reader.availableWordListSize()!=1){
        std::cout << "ERROR: List size should be 1" << std::endl;
        std::cout << "Received word list size: " << word_reader.availableWordListSize() << std::endl;
        error=true;
    }

    if (!error){
        std::cout << "OK" << std::endl;
    }

    /* FETCH WORD TESTS */
    error=false;
    std::cout << "TESTING: WordReader.fetchWord() - ";
    word_reader.fetchWord();
    // Check that the word is 'testing'
    if (strcmp("testing", word_reader.latest_word->word)!=0){
        std::cout << "ERROR" << std::endl;
        error=true;
    }
    // Check that all characters in the scrambled word are in the normal word
    for (int i=0; i<word_reader.latest_word->word_size; i++){
        int char_cnt_word = 0;
        int char_cnt_scrambled = 0;
        char curr_char = word_reader.latest_word->word[i];
        for (int j=0; j<word_reader.latest_word->word_size; j++){
            if (word_reader.latest_word->word[j]==curr_char){
                char_cnt_word++;
            }
            if (word_reader.latest_word->scrambled_word[j]==curr_char){
                char_cnt_scrambled++;
            }
        }
        if (char_cnt_word!=char_cnt_scrambled){
            std::cout << "ERROR: Scrambled word does not contain all characters from normal word" << std::endl;
            std::cout << "Normal word: " << word_reader.latest_word->word << " Scrambled word: " << word_reader.latest_word->scrambled_word << std::endl;
            error=true;
            break;
        }
    }
    if (!error){
        std::cout << "OK" << std::endl;
    }

    return 0;
}