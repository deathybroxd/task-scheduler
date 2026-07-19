/* SimClock.hpp 
simulated clock
*/

#ifndef SIMCLOCK_HPP
#define SIMCLOCK_HPP

class SimClock {
public:
    // constructor - takes in only positive ints
    SimClock(int startTime = 0);

    // destructor
    ~SimClock() = default;

    // now - gives current time
    int Now() const;

    // advance - advances the time by a delta - takes in only positive ints
    void Advance(int delta);

    // settime - changes m_currentTime - takes in only positive ints
    void SetTime(int time);

private:
    int m_currentTime;

};
#endif