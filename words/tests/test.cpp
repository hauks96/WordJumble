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
    // Check that the wordlist is inserted properly on initialization
    if (strcmp(default_word_list, word_reader.currentWordList())!=0){
        std::cout << "ERROR: Invalid default wordlist set" << std::endl;
        error=true;
    }
    // Check that the word list counts the number of available word lists correctly
    if (word_reader.availableWordListSize()!=2){
        std::cout << "ERROR: List size should be 2" << std::endl;
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

    /* ADD HINT TEST */
    error=false;
    std::cout << "TESTING: WordReader.addHint() - ";
    int initially_correct_letters = word_reader.latest_word->initially_correct_letters;
    word_reader.addHint();
    int cnt_now_correct_letters = 0;
    for (int i=0; i<word_reader.latest_word->word_size; i++){
        if (word_reader.latest_word->correct_letters[i]){
            cnt_now_correct_letters++;
        }
    }
    if (!cnt_now_correct_letters>initially_correct_letters){
        std::cout << "ERROR: Hint didn't update number of correct letters in scrambled word" << std::endl;
        error=true;
    }
    if (!error){
        std::cout << "OK" << std::endl;
    }
    /* SWITCH WORDLIST TEST */
    std::cout << "TESTING: WordReader.switchWordlist() - ";
    word_reader.switchWordlist(1);
    // Check that the wordlist has changed to test2
    if (strcmp("test2", word_reader.currentWordList())!=0){
        std::cout << "ERROR: Invalid default wordlist set" << std::endl;
        std::cout << "Should be: " << "test2" << " But is: " << word_reader.currentWordList() << std::endl;
        error=true;
    }
    if (!error){
        std::cout << "OK" << std::endl;
    }
    return 0;
}