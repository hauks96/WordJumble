#ifndef HW2_GAMESETTINGS_H
#define HW2_GAMESETTINGS_H

class GameSettings {
public:
    GameSettings();
    int starting_points;
    int score_per_correct_char;
    int word_base_score;
    double score_per_time_mp;
    int score_mp_time_limit;
    char* default_wordlist;
    char* highscore_file;
private:
    struct Loader;
};

#endif //HW2_GAMESETTINGS_H


