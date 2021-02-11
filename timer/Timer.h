#ifndef HW2_TIMER_H
#define HW2_TIMER_H

class Timer {
public:
    Timer();
    void start_time();   // start the timer
    void pause_time();   // pause the timer
    void restart_time(); // Start a paused timer
    void reset_time();   // Reset the timer to default
    unsigned int elapsed_time(); // Get the currently elapsed time

private:
    bool is_paused;
    unsigned int timestamp;        // timestamp of start in seconds
    unsigned int pause_timestamp;  // timestamp of pause in seconds
    unsigned int elapsed_time_sec; // If time is paused, this variable stores the total elapsed time so far
};


#endif //HW2_TIMER_H
