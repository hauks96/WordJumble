#ifndef HW2_GAMETYPE_H
#define HW2_GAMETYPE_H
#include "../score/Score.h"
#include "../timer/Timer.h"

// Abstract class allows defining either game type by using the object of type GameType
class GameType {
public:
    virtual ~GameType()=0; // Pure virtual destructor
    // Check if the game is over for the given game type
    virtual bool checkGameOver(Score& score) = 0;
    // Get the name of the current game
    virtual char* name() const = 0;
};

GameType::~GameType(){};

#endif //HW2_GAMETYPE_H
