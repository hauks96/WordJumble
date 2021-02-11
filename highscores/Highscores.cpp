//
// Created by agirm on 11/02/2021.
//

#include "Highscores.h"
#define SCORE_DELIMITER_NR 0
#define WORDLIST_DELIMITER_NR 1
#define CORR_WORDS_DELIMITER_NR 2
#define CORR_CHARS_DELIMITER_NR 3
#define DELIMITER_CHAR ','
#define MAX_COL_SIZE 64

// Get the desired column (col idx is delimiter)
friend char* getLineBufferDelimited(char* line, int delimiter){
    int line_idx = 0;
    int buffer_idx = 0;
    int delimiter_nr = 0;
    char line_char = line[line_idx];
    char tmp_buffer[MAX_COL_SIZE];
    while(true){
        if (line_char=='\n' || line_char==DELIMITER_CHAR || line_char=='\0'){
            if (delimiter==delimiter_nr){
                tmp_buffer[buffer_idx]='\0';
                char* ret_buffer = new char[buffer_idx+1];
                for (int i=0; i<buffer_idx+1){
                    ret_buffer[i]=tmp_buffer[i];
                }
                return ret_buffer; // remember to delete after usage
            }
            else if (line_char=='\0'){
                std::cout << "WARNING: Reached end of line while trying to fetch on delimiter " << delimiter << std::endl;
                std::runtime_error("End of line reached without return.");
            }
            else {
                delimiter_nr++;
            }
        }
        tmp_buffer[buffer_idx]=line_char;
        line_idx++;
        buffer_idx++;
        line_char=line[line_idx];
    }
}

int getScore(char* line){
    // Get all numbers within score delimiter
    char* score_as_char = getLineBufferDelimited(line, SCORE_DELIMITER_NR);
    return score_as_char;
}
int getCorrectWords(char* line){
    // Get all numbers within corr words delimiter
    char* corr_words_as_char = getLineBufferDelimited(line, CORR_WORDS_DELIMITER_NR);
    return corr_words_as_char;
}
int getCharsCorrected(char* line){
    // Get all numbers within corr char delimiter
    char* corr_char_as_char = getLineBufferDelimited(line, CORR_CHARS_DELIMITER_NR);
    return corr_words_as_char;
}
char* getWordlist(char* line){
    // Get all chars within wordlist delimiter
    char* wordlist = getLineBufferDelimited(line, WORDLIST_DELIMITER_NR);
    return wordlist;
}
