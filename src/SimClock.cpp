/* SimClock.cpp 
simulated clock
*/
#include "SimClock.hpp"
#include <iostream>

SimClock::SimClock(int startTime) {
    if(startTime < 0) {
        std::cerr << "ERROR: Time cannot be started at a negative number, setting to a default of 0" << std::endl;
        m_currentTime = 0;
    } else {
        m_currentTime = startTime;
    }
}

int SimClock::Now() const {
    return m_currentTime;
}

void SimClock::Advance(int delta) {
    if(delta < 0) {
        std::cerr << "ERROR: Time cannot be advanced to a negative number" << std::endl;
        return;
    }
    m_currentTime += delta;
}

void SimClock::SetTime(int time) {
    if(time < 0) {
        std::cerr << "ERROR: Time cannot be set to a negative number" << std::endl;
        return;
    }
    m_currentTime = time;
}
