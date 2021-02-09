//
// Created by agirm on 09/02/2021.
//

#include "../WordReader.h"
#include "../WordReader.cpp"
#include <iostream>
int main(){
    WordReader word_reader;
    char default_word_list[] = "../../programming";
    word_reader.init_word_reader(default_word_list);
    word_reader.fetchWord();
    std::cout << "made it though" << std::endl;
    return 0;
}