//
// Created by agirm on 08/02/2021.
//

#ifndef HW2_WORDREADER_H
#define HW2_WORDREADER_H
#include "GuessWord.h"

class WordReader {
    friend std::ifstream& get_filestream(WordReader& self, char* filename);
    friend void load_file_presets(WordReader& self);
    friend char* read_line(std::ifstream& f_in, char* filename, int line_number);
    friend char* read_line_number_x(WordReader& self, int line_number, int* line_length);
    friend void scramble_helper(char* word, char*scrambled, int line_size);
    friend void swap_correct_char(GuessWord& guessword, int index);
    friend void update_correct_words(GuessWord& wr);
    friend void swap(char* a, char* b);

public:
    void init_word_reader(char* default_wordlist);
    // Get the name of the current wordlist
    char* currentWordList() const;
    // Get the available word lists
    char** availableWordLists() const;
    // Get size of available word list
    int availableWordListSize() const;
    // Get a single GuessWord
    void fetchWord();
    // Add a hint to the scrambled word
    void addHint();
    // Reset to default
    void reset();
    // The last fetched guess word. Gets deleted when a new one is requested. Initially null
    GuessWord* latest_word;
private:
    int* read_lines; // Array containing indexes of the lines that have already been read
    int read_lines_size; // The capacity of the read_lines array
    int read_lines_content_size; // The size of the content in read_lines array
    int file_line_count; // Size of the current wordlist in lines
    char* current_wordlist; // The word list file currently in use
    char** available_word_lists; // The available word lists
    int available_word_lists_size; // Size of the available word lists
};


#endif //HW2_WORDREADER_H
