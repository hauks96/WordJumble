//
// Created by agirm on 08/02/2021.
//

#include "WordReader.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "GuessWord.h"
#define MAX_FILENAME 64
#define MAX_LINE_LENGTH 256

// Swap a with b in an array
void swap(char* a, char* b){
    int temp_a = *a;
    *a = *b; // Set val of a as b
    *b = temp_a; // Set val of b as a
}

void scramble_helper(char* word, char*scrambled_word, int line_size){
    std::srand(std::time(nullptr)); // use time as random seed
    int rand_idx;
    for (int i=line_size-1; i>0; i--){
        rand_idx = rand() % (i+1);
        swap(&scrambled_word[i], &scrambled_word[rand_idx]);
    }
    bool equal = true;
    // Scramble until the arrays are not equal
    while(true){
        for (int i=0; i<line_size; i++){
            if(line_size<=2){
                break;
            }
            if (word[i]!=scrambled_word[i]){
                equal=false;
                break;
            }
        }
        if(equal){
            scramble_helper(word, scrambled_word, line_size);
            break;
        }
        else{
            break;
        }
    }

}

// Scramble a word and return it as a new array
char* scramble_word(char* word, int line_size){
    char* scrambled_word = new char[line_size+1];
    strcpy(scrambled_word, word);

    scramble_helper(word, scrambled_word, line_size);

    bool has_one_correct = false;
    for (int i=0; i<line_size; i++){
        if (word[i]==scrambled_word[i]){
            has_one_correct=true;
        }
    }
    // If the scrambled word doesn't already have one correct character
    if (!has_one_correct){
        std::cout << "Didn't have one correct." << std::endl;
        // Add one correct character
        int rand_correct_char = rand() % (line_size); // length-1 for idx
        char scrambled_char = scrambled_word[rand_correct_char];

        // find the correct char position in array
        for (int i=0; i<line_size; i++){
            if (scrambled_char==word[i]){
                swap(&scrambled_word[i], &scrambled_word[rand_correct_char]);
            }
        }

    }
    return scrambled_word;
}

// Get a filestream with a given file name
std::ifstream* get_filestream(char* filename){
    char temp_filename[MAX_FILENAME];
    int cnt = 0;
    // Add .txt to the name of the file
    while(true) {
        char curr_char = filename[cnt];
        if (curr_char == '\0') {
            temp_filename[cnt] = '.';
            temp_filename[cnt + 1] = 't';
            temp_filename[cnt + 2] = 'x';
            temp_filename[cnt + 3] = 't';
            temp_filename[cnt + 4] = '\0';
            break;
        }
        temp_filename[cnt] = curr_char;
        if (cnt + 5 > MAX_FILENAME - 1) {
            std::cout << "WARNING: Filename exceeded the limit of " << MAX_FILENAME
                      << " characters. Cannot read file" << std::endl;
            throw std::runtime_error("Filename too large.");
        }
        cnt++;
    }
    // Try to open the file
    std::ifstream* f_in = new std::ifstream();
    f_in->open(temp_filename, std::ios::in);
    if (!f_in->is_open()){
        std::cout << "WARNING: File with name " << temp_filename << " is not located in the words directory or does not exist." << std::endl;
        throw std::runtime_error("File does not exist.");
    }
    return f_in;
}

// Get the line count and from a file and make sure all lines are in bounds of max buffer size
void load_file_presets(WordReader& self){
    std::ifstream* f_in_prt = get_filestream(self.current_wordlist);
    std::ifstream& f_in = *f_in_prt;
    int cnt_lines=0;
    int cnt;
    unsigned char line_buffer[MAX_LINE_LENGTH];
    char char_buffer[1];
    while(true){
        // Stop if end of file
        if (f_in.eof()){
            break;
        }
        // Read one line and count number of characters
        cnt=0;
        while(true){
            if (f_in.eof()){
                break;
            }
            if (cnt>=MAX_LINE_LENGTH){
                std::cout << "Max line length of " << MAX_LINE_LENGTH << " exceeded in file " << self.current_wordlist << " in line " << cnt_lines << std::endl;
                throw std::runtime_error("Max line length exceeded.");
            }
            f_in.read(char_buffer, 1);
            if (char_buffer[0]=='\n' || char_buffer[0]=='\0'){
                break;
            }
            cnt++;
        }
        // Count total number of lines
        cnt_lines++;
    }
    self.file_line_count = cnt_lines;
    f_in.close();
    delete f_in_prt;
}

// Read a line of the current file in use
char* read_line(std::ifstream& f_in, char* filename, int line_number){
    char char_buffer[1];
    char temp_line[MAX_LINE_LENGTH];
    temp_line[0]='\0';
    int cnt = 0;
    while(true){
        if (f_in.eof()){
            if (temp_line[0]=='\0' || temp_line[0]=='\n'){
                return nullptr;
            }
            else {
                temp_line[cnt-1]='\0';
                break;
            }
        }
        if (cnt>=MAX_LINE_LENGTH){
            std::cout << "Max line length of " << MAX_LINE_LENGTH << " exceeded in file " << filename << " in line " << line_number << std::endl;
            throw std::runtime_error("Max line length exceeded.");
        }
        f_in.read(char_buffer, 1);
        if (char_buffer[0]=='\n' || char_buffer[0]=='\0'){
            temp_line[cnt]='\0';
            cnt++;
            break;
        }
        temp_line[cnt]=char_buffer[0];
        cnt++;
    }
    char* line = new char[cnt+1];
    strcpy(line, temp_line);
    return line;
}

// Read a specific line in the currently selected word file
char* read_line_number_x(char* current_wordlist, int line_number, int* line_length){
    std::cout << "Line number: " << line_number << std::endl;
    std::ifstream* f_in_prt = get_filestream(current_wordlist);
    std::ifstream& f_in = *f_in_prt;
    int line_ctn = 0;
    int line_size = 0;
    char line_buffer[MAX_LINE_LENGTH];
    char char_buffer[1];
    while(true){
        // If the next line to read is the one we are looking for
        if (line_ctn==line_number){
            while(true){
                // If we're at end of line create new array and return it
                if (char_buffer[0]=='\0' || char_buffer[0]=='\n' || f_in.eof()){
                    char_buffer[line_size]='\0';
                    char* new_line = new char[line_size+1];
                    for (int j=0; j<line_size; j++){
                        new_line[j]=line_buffer[j];
                    }
                    line_length[0]=line_size-1;
                    f_in.close();
                    delete f_in_prt;
                    return new_line;
                }
                // Not at end of line yet so we add char to line
                f_in.read(char_buffer, 1);
                line_buffer[line_size]=char_buffer[0];
                line_size++;
            }
        }
        // read lines until we are at the desired line
        f_in.getline(line_buffer, MAX_LINE_LENGTH);
        line_ctn++;
    }
    std::cout << "Unexpected error while trying to fetch new word." << std::endl;
    throw std::runtime_error("Unable to fetch word");
}

// Initialize the word reader class
void WordReader::init_word_reader(char* default_wordlist) {
    int* init_read_lines = new int[20];
    this->read_lines = init_read_lines;
    this->read_lines_size = 20;
    this->read_lines_content_size = 0;
    this->current_wordlist = default_wordlist;
    this->latest_word = nullptr;

    char filename[]="word_lists";
    int num_lines[1];
    std::ifstream* f_in_prt = get_filestream(filename); // Must be deleted
    std::ifstream& f_in = *f_in_prt; // Automatically removed when method returns
    const char ** word_lists = new const char* [num_lines[0]];
    int line_cnt = 0;
    // adding the file names to the word_lists array
    while(true){
        if (f_in.eof()){
            break;
        }
        char* line=read_line(f_in, filename, line_cnt+1);
        if (line == nullptr){
            break;
        }
        word_lists[line_cnt]=line;
        if (!f_in.eof()){
            line_cnt++;
        }
    }
    this->available_word_lists = word_lists;
    this->available_word_lists_size = line_cnt+1;
    f_in.close();
    delete f_in_prt;
    load_file_presets(*this);
}

// Get the word list currently in use
char * WordReader::currentWordList() const {
    return this->current_wordlist;
}

// Get the size of the available words list
int WordReader::availableWordListSize() const {
    return this->available_word_lists_size;
}

// Get the name of the word lists available
const char ** WordReader::availableWordLists() const {
    return this->available_word_lists;
}

// Fetch a new word
void WordReader::fetchWord() {
    // Remove the last word fetched
    if (this->latest_word != nullptr){
        delete this->latest_word->scrambled_word;
        delete this->latest_word->word;
        delete this->latest_word->correct_letters;
        delete this->latest_word;
    }
    // Resize array if word count exceeds array size
    if (this->read_lines_content_size==this->read_lines_size){
        // copy contents to new array
        int* new_array = new int[2*this->read_lines_size];
        for (int i=0; i<this->read_lines_size; i++){
            new_array[i]=this->read_lines[i];
        }
        delete this->read_lines; // Remove old
        this->read_lines = new_array; // Add ned
    }
    int size = this->file_line_count-this->read_lines_content_size;
    int options[size];
    bool exists;

    for (int i=0; i<size; i++){
        exists=false;
        for (int j=0; j<this->read_lines_content_size; j++) {
            if (i == read_lines[j]) {
                exists = true;
                break;
            }
        }
        if (!exists){
            options[i]=i;
        }
    }
    std::srand(std::time(nullptr)); // use time as random seed
    // get random line number to get word from
    int rand_line = rand() % (this->file_line_count - this->read_lines_content_size);
    int line_size[1]; // Retrieves the size of the line
    char* rand_word = read_line_number_x(this->current_wordlist, rand_line, line_size);

    // Update read lines
    this->read_lines_content_size+=1;
    this->read_lines[this->read_lines_content_size]=rand_line;
    char* scrambled_word = scramble_word(rand_word, line_size[0]);

    int cnt = 0;
    bool* correct_words = new bool[line_size[0]];
    for (int i=0; i<line_size[0]-1; i++){
        if (rand_word[i]==scrambled_word[i]){
            correct_words[i]=true;
            cnt++;
        }
        else{
            correct_words[i]=false;
        }
    }
    // Create GuessWord object
    GuessWord* guess_word = new GuessWord();
    guess_word->scrambled_word = scrambled_word;
    guess_word->word = rand_word;
    guess_word->word_size = line_size[0];
    guess_word->correct_letters = correct_words;
    guess_word->initially_correct_letters = cnt;
    this->latest_word = guess_word;
}

// Reset do initial values
void WordReader::reset() {
    delete this->read_lines;
    delete this->latest_word->scrambled_word;
    delete this->latest_word->word;
    delete this->latest_word->correct_letters;
    delete this->latest_word;
    int* init_read_lines = new int[20];
    this->read_lines = init_read_lines;
}

// Swap a letter into the correct position
void swap_correct_char(GuessWord& guessword, int index){
    char swap_for = guessword.scrambled_word[index];
    std::cout << "Swapping character: " << swap_for << std::endl;
    for (int i=0; i<guessword.word_size; i++){
        if (guessword.word[i]==swap_for && !guessword.correct_letters[i]){
            swap(&guessword.scrambled_word[index], &guessword.scrambled_word[i]);
            break;
        }
    }
}

// Update array that hold what characters are correct
void update_correct_words(GuessWord& gw){
    for (int i=0; i<gw.word_size; i++){
        if (gw.word[i]==gw.scrambled_word[i]){
            gw.correct_letters[i]=true;
            std::cout <<  gw.correct_letters[i] ;
        }else{
            gw.correct_letters[i]=false;
        }
    }
    std::cout << std::endl;
}

// Add another character to the correct position
void WordReader::addHint() {
    if(this->latest_word == nullptr){
        std::cout << "WARNING: Cannot add a hint before fetching a word" << std::endl;
    }
    else {
        bool equal = true;
        for (int i=0; i<this->latest_word->word_size; i++){
            //std::cout << "Word size: " << this->latest_word->word_size << std::endl;
            if (this->latest_word->word[i]!=this->latest_word->scrambled_word[i]){
                equal=false;
                break;
            }
        }
        if (equal){
            std::cout << "WARNING: Strings are already equal!" << std::endl;
            return;
        }
        std::srand(std::time(nullptr)); // use time as random seed
        int rand_left_right = rand() % 2; // 0 or 1
        if (rand_left_right==0){
            for (int i=this->latest_word->word_size-1; i>-1; i--){
                if (!this->latest_word->correct_letters[i]){
                    swap_correct_char(*this->latest_word, i);
                    update_correct_words(*this->latest_word);
                    break;
                }
            }
        }else{
            for (int i=0; i<this->latest_word->word_size; i++){
                if (!this->latest_word->correct_letters[i]){
                    swap_correct_char(*this->latest_word, i);
                    update_correct_words(*this->latest_word);
                    break;
                }
            }
        }
    }
}