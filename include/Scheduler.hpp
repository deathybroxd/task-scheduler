/* Scheduler.hpp */
#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "Task.hpp"
#include <vector>

// abstract base class for EDFScheduler
class Scheduler {
public:
    virtual ~Scheduler() = default;

    // pure virtual - selects the next taask from readytasks
    virtual const Task* SelectNextTask(const std::vector<Task>& readyTasks, int currentTime) = 0;
};

#endif