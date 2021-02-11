#ifndef HW2_SCORE_H
#define HW2_SCORE_H
#include "../settings/GameSettings.h"
#include "../timer/Timer.h"
#include "../words/GuessWord.h"

class Score {

public:
    Score();
    void init_score(GameSettings& settings);
    void reset();
    void decreasePoints(int points);
    void increasePoints(int points);
    // Update the score after a word is guessed correctly
    void updateScore(GuessWord& gw, Timer& timer);
    int getCurrentScore();
    int getCurrentPoints();
    double getCurrentMultiplier();
    int points;
    int guessed_words;
    int characters_corrected;
private:
    double multiplier;
    int starting_points;
    int current_score;
    int base_score;
    int score_per_correct_char;
    double score_per_time_mp;
    int score_mp_time_limit;
};


#endif //HW2_SCORE_H
