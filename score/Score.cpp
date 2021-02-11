#include "Score.h"
#include "../settings/GameSettings.h"
// Calculate score according to correct letters guessed by user in a word
Score::Score() {
    return;
}

void Score::init_score(GameSettings& settings) {
    this -> points = settings.starting_points;
    this -> starting_points = settings.starting_points;
    this -> score_mp_time_limit = settings.score_mp_time_limit;
    this -> score_per_correct_char = settings.score_per_correct_char;
    this -> score_per_time_mp = settings.score_per_time_mp;
    this -> base_score = settings.word_base_score;
    this -> guessed_words = 0;
    this -> current_score=0;
    this -> multiplier = 1;
    this -> characters_corrected = 0;
}

void Score::decreasePoints(int points) {
    this -> points -=points;
    this -> multiplier = 1;
}

void Score::increasePoints(int points) {
    this -> points -=points;
}

int Score::getCurrentScore() {
    return this->current_score;
}

void Score::updateScore(GuessWord &gw, Timer &timer) {
    // If time was within time limit increase multiplier and set score
    if (timer.elapsed_time()<this->score_mp_time_limit){
        this->multiplier = this->multiplier + (double) this->score_per_time_mp;
        this->current_score += this->multiplier * (this->base_score+((gw.word_size-gw.initially_correct_letters)*this->score_per_correct_char));
    }
    // Otherwise reset multiplier and set score
    else{
        this->multiplier=1;
        this->current_score += this->base_score+((gw.word_size-gw.initially_correct_letters)*this->score_per_correct_char);
    }
    this->guessed_words++;
    this->characters_corrected+=(gw.word_size-gw.initially_correct_letters);
}

void Score::reset(){
    this->points = this->starting_points;
    this->multiplier = 1;
    this->characters_corrected = 0;
    this->guessed_words = 0;
    this->current_score=0;
}

int Score::getCurrentPoints() {
    return this->points;
}

double Score::getCurrentMultiplier() {
    return this->multiplier;
}