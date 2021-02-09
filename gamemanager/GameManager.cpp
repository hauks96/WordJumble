//
// Created by agirm on 06/02/2021.
//

#include "GameManager.h"
#include "../score/Score.h"
#include "../score/Score.cpp"
#include "../timer/Timer.h"
#include "../timer/Timer.cpp"
#include "../settings/GameSettings.h"
#include "../settings/GameSettings.cpp"
#include "../gametype/GuessToSeven.h"
#include "../gametype/GuessUntilZero.h"
#include "../gametype/GameType.h"
#include "../words/WordReader.h"
#include "../words/WordReader.cpp"
#include "../words/GuessWord.h"

GameManager::GameManager() {
    this->score.init_score(this->settings);
    this->words.init_word_reader(this->settings.default_wordlist);
    GameType* init_type = new GuessUntilZero();
    this->type = init_type;
    this->user._init_output_manager(*init_type);
}