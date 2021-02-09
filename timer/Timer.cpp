//
// Created by agirm on 06/02/2021.
//

#include "Timer.h"
#include <ctime>
#include <iostream>

Timer::Timer() {
    this->timestamp = 0;
    this->pause_timestamp = 0;
    this->elapsed_time_sec = 0;
    this->is_paused = false;
}

void Timer::start_time(){
    if (this->timestamp!=0){
        std::cout << "Timer has already been started!" << std::endl;
        return;
    }
    // Create a new timestamp for when the timer was started
    time_t time_now = time(0);
    this -> timestamp = (unsigned int) time_now;
}

void Timer::pause_time() {
    if (this->timestamp==0){
        std::cout << "Timer has not yet been started!" << std::endl;
        return;
    }
    // Update elapsed time since start at the time of the pause
    time_t time_now = time(0);
    this -> pause_timestamp = (unsigned int) time_now;
    this -> elapsed_time_sec += this->pause_timestamp - this->timestamp;
    this -> is_paused = true;
}

void Timer::restart_time() {
    if (!this->is_paused){
        std::cout << "Time is not paused!" << std::endl;
        return;
    }
    // Update the timestamp to be the time of the restart
    time_t time_now = time(0);
    this -> timestamp = (unsigned int) time_now;
    this -> is_paused = false;
}

void Timer::reset_time() {
    this->timestamp = 0;
    this->pause_timestamp = 0;
    this->elapsed_time_sec = 0;
    this->is_paused = false;
}

unsigned int Timer::elapsed_time() {
    if (this->timestamp==0){
        std::cout << "Time has not been started yet!" << std::endl;
        return 0;
    }
    time_t time_now = time(0);
    unsigned int rest_time = (unsigned int) time_now - this->timestamp;
    return rest_time + this->elapsed_time_sec;
}