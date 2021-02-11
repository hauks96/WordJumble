#include <iostream>
#include "gamemanager/GameManager.h"
#include "gamemanager/GameManager.cpp"
#include <windows.h>
#include <future>
#include <thread>

int main(){
    GameManager game_manager;
    game_manager.start();
    return 0;
}
