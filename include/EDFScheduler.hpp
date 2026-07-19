/* EDFScheduler.hpp */
#ifndef EDFSCHEDULER_HPP
#define EDFSCHEDULER_HPP

#include "Scheduler.hpp"

class EDFScheduler : public Scheduler {
public:
    // no destructor needed

    // selects the next task from readytasks
    const Task* SelectNextTask(const std::vector<Task>& readyTasks, int currentTime) override;
};

#endif