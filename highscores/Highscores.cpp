//
// Created by agirm on 11/02/2021.
//

#include "Highscores.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstring>
#define SCORE_DELIMITER_NR 0
#define USERNAME_DELIMITER_NR 1
#define WORDLIST_DELIMITER_NR 2
#define CORR_WORDS_DELIMITER_NR 3
#define CORR_CHARS_DELIMITER_NR 4
#define NUMBER_OF_COLUMNS 5
#define DELIMITER_CHAR ','
#define MAX_COL_SIZE 64
#define MAX_LINE_SIZE 256

int getStringSize(char* string){
    char str_char = string[0];
    int size = 0;
    while(str_char!='\n' && str_char!='\0'){
        size++;
        str_char = string[size];
    }
    return size;
}

char* getIntAsString(int number){
    char* buffer = new char[10]; // remember to delete
    sprintf(buffer, "%d", number);
    return buffer;
}

int getStringAsNumber(char* some_string){
    int number = atoi (some_string);
    return number;
}
// Get the desired column (col idx is delimiter)
char* getLineBufferDelimited(char* line, int delimiter){
    int line_idx = 0; // Index of the line received
    int buffer_idx = 0; // Index to write to in the return array
    int delimiter_nr = 0; // Count of delimiters reached
    char line_char = line[line_idx]; // a character in the line
    bool wasDelimiter;
    while(true){
        // reset was delimiter
        wasDelimiter=false;
        // reset temporary buffer (we add the column we want to this array)
        char tmp_buffer[MAX_COL_SIZE];
        // If the character is a comma or we are at the end of the line
        if (line_char=='\n' || line_char==DELIMITER_CHAR || line_char=='\0'){
            wasDelimiter=true;
            // if we got the desired delimiter count copy the contents of the buffer into a new array and return it
            if (delimiter==delimiter_nr){
                tmp_buffer[buffer_idx]='\0';
                char* ret_buffer = new char[buffer_idx+1];
                for (int i=0; i<buffer_idx+1; i++){
                    ret_buffer[i]=tmp_buffer[i];
                }
                return ret_buffer; // remember to delete after usage
            }
            else if (line_char=='\0'){
                std::cout << "WARNING: Reached end of line while trying to fetch on delimiter " << delimiter << std::endl;
                std::runtime_error("End of line reached without return.");
            }
            /* We didn't find find our desired column so we reset the values
             * of the buffer and start writing into it again */
            else {
                buffer_idx=0;
                delimiter_nr++;
            }
        }
        // If the character was a delimiter we don't want to write it into the string
        if (!wasDelimiter){
            tmp_buffer[buffer_idx]=line_char;
            buffer_idx++;
        }
        // Increase the index to read the next character in the line
        line_idx++;
        line_char=line[line_idx];
    }
}

char* getScore(char* line){
    // Get all numbers within score delimiter
    char* score_as_char = getLineBufferDelimited(line, SCORE_DELIMITER_NR);
    return score_as_char;
}

char* getCorrectWords(char* line){
    // Get all numbers within corr words delimiter
    char* corr_words_as_char = getLineBufferDelimited(line, CORR_WORDS_DELIMITER_NR);
    return corr_words_as_char;
}

char* getCharsCorrected(char* line){
    // Get all numbers within corr char delimiter
    char* corr_char_as_char = getLineBufferDelimited(line, CORR_CHARS_DELIMITER_NR);
    return corr_char_as_char;
}

char* getWordlist(char* line){
    // Get all chars within wordlist delimiter
    char* wordlist = getLineBufferDelimited(line, WORDLIST_DELIMITER_NR);
    return wordlist;
}

char* getUsername(char* line){
    // Get all chars within wordlist delimiter
    char* username = getLineBufferDelimited(line, USERNAME_DELIMITER_NR);
    return username;
}

void insert_into_line(char* line, char* insert_string, int* end_index, bool end_of_line){
    int start_index = end_index[0];
    char curr_char = insert_string[0];
    int curr_idx = 0;
    while(true){
        // If we're at the end of the string we want to insert
        if (curr_char=='\0' || curr_char=='\n'){
            // Add the delimiter
            if (!end_of_line){
                line[curr_idx+start_index]=',';
                curr_idx++;
                // Send back the index that we ended on
                end_index[0]=curr_idx+start_index;
                return;
            }
            // Mark end of line
            else {
                line[curr_idx+start_index]='\0';
                return;
            }
        }
        // Insert the character from the insert string into the line
        line[curr_idx+start_index]=insert_string[curr_idx];
        // increase the index for next character
        curr_idx++;
        // get the next character from the string we want to insert into our line
        curr_char=insert_string[curr_idx];
    }
}

char* create_line(int score, char*username, char* wordlist, int correct_words, int correct_chars){
    // Create a line that we can write into the highscores file
    char* line = new char[MAX_LINE_SIZE];
    char* score_str = getIntAsString(score);
    char* correct_words_str = getIntAsString(correct_words);
    char* correct_chars_str = getIntAsString(correct_chars);
    int start_index[1];
    start_index[0]=0;
    insert_into_line(line, score_str, start_index, false);
    insert_into_line(line, username, start_index, false);
    insert_into_line(line, wordlist, start_index, false);
    insert_into_line(line, correct_words_str, start_index,false);
    insert_into_line(line, correct_chars_str, start_index, true);
    return line;
}

char*** Highscores::getHighscores(int howMany, bool all){
    std::ifstream f_in;
    // If want to read all lines
    if (all){
        howMany = this->number_of_highscores;
    }
    // If the number exceeds the available highscores
    if (howMany>this->number_of_highscores){
        std::cout << "TOO MANY NUMBERS REQUESTED!" << std::endl;
        std::runtime_error("Out of bounds highscore request");
    }
    // create a new highscores array that contains all the data from the file
    char*** highscores = new char**[howMany];
    f_in.open(this->filename);
    // if the file is not found stop runtime
    if (!f_in.is_open()){
        std::cout << "File not found." << std::endl;
        std::runtime_error("File was not found");
    }
    // there are no highscores, return a null pointer
    if (f_in.eof()){
        std::cout << "No highscores." << std::endl;
        return nullptr;
    }

    char line_buffer[MAX_LINE_SIZE];
    // read howmany number of lines and convert them into useful data objects
    for (int i=0; i<howMany; i++){
        f_in.getline(line_buffer, MAX_LINE_SIZE);
        if (line_buffer[0]=='\0'){
            return highscores;
        }
        // Each 'columns' array contains all the data for each row
        char** columns = new char*[NUMBER_OF_COLUMNS];
        char* username = getUsername(line_buffer);
        char* wordList = getWordlist(line_buffer);
        char* charsCorrected = getCharsCorrected(line_buffer);
        char* correctWords = getCorrectWords(line_buffer);
        char* score = getScore(line_buffer);
        // Insert data into row column
        columns[USERNAME_DELIMITER_NR]=username;
        columns[SCORE_DELIMITER_NR]=score;
        columns[WORDLIST_DELIMITER_NR]=wordList;
        columns[CORR_CHARS_DELIMITER_NR]=charsCorrected;
        columns[CORR_WORDS_DELIMITER_NR]=correctWords;
        // Add columns to row
        highscores[i]=columns;
    }
    f_in.close();
    return highscores;
}

void Highscores::addHighscore(int score, char* username, char* wordlist, int correct_words, int correct_chars){
    char line_buffer[MAX_LINE_SIZE];
    std::ifstream f_in;
    // try to open file
    f_in.open(this->filename);
    // if the file isnt open stop the runtime of the program
    if (!f_in.is_open()){
        std::cout << "File not found." << std::endl;
        std::runtime_error("File was not found");
    }

    // Reset pointer with seekg
    f_in.seekg(0, std::ios::beg);
    char* lines[this->number_of_highscores];
    // Add all lines of file to the new array
    for (int i=0; i<this->number_of_highscores; i++){
        if (f_in.eof()){
            std::cout << "WARNING: Unexpected end of file." << std::endl;
            std::runtime_error("File end while trying to read line");
        }
        // read a line
        f_in.getline(line_buffer, MAX_LINE_SIZE);
        // copy current line to temporary string
        char* temp_line = new char[MAX_LINE_SIZE];
        strcpy(temp_line, line_buffer);
        // add line to array
        lines[i] = temp_line;
    }

    f_in.close();
    // open filestream again but this time for write
    std::ofstream f_out;
    f_out.open(this->filename);
    bool hasBeenAdded=false; // If the new line has been added or not
    // Find position for new score and insert it
    for (int i=0; i<this->number_of_highscores; i++){
        // get the string that represents the score
        char* score_file_line = getScore(lines[i]);
        // convert the string to int
        int score_this_line = getStringAsNumber(score_file_line);
        // check if the score is lesser than the new score
        if (score>score_this_line && !hasBeenAdded){
            hasBeenAdded = true;
            // write new score to file
            char* new_line = create_line(score, username, wordlist, correct_words, correct_chars);
            f_out << new_line << std::endl;
            delete new_line;
        }
        // write the normal score to file
        f_out << lines[i] << std::endl;
        delete lines[i];
    }
    // If all original highscores have been added but the new one hasn't yet
    if (!hasBeenAdded){
        // add it to highscores at the bottom
        char* new_line = create_line(score, username, wordlist, correct_words, correct_chars);
        f_out << new_line << std::endl;
        delete new_line;
    }
    f_out.close();
    this->number_of_highscores++;
}

int Highscores::numberOfHighscores() {
    return this->number_of_highscores;
}

void Highscores::init_highscores(char *filename) {
    this->filename=filename;
    char line_buffer[MAX_LINE_SIZE];
    std::ifstream f_in;
    f_in.open(filename);
    if (!f_in.is_open()){
        std::cout << "HIGHSCORE FILE NOT FOUND!" << std::endl;
        std::runtime_error("FILE NOT FOUND!");
        return;
    }
    int cnt_lines = 0;
    // Get line count in file
    while(true){
        // Stop if end of file
        if (f_in.eof()){
            break;
        }
        f_in.getline(line_buffer, MAX_LINE_SIZE);
        // Count total number of lines
        if (line_buffer[0]=='\n' ||line_buffer[0]=='\0'){
            break;
        }
        cnt_lines++;
    }
    this->number_of_highscores = cnt_lines;
    std::cout << "NUMBER OF LINES: " << cnt_lines << std::endl;
    f_in.close();
}