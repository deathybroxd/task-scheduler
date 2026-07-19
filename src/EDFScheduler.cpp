/* EDFScheduler.cpp */

#include "EDFScheduler.hpp"

const Task* EDFScheduler::SelectNextTask(const std::vector<Task>& readyTasks, int currentTime) {
    if(readyTasks.empty()) {
        return nullptr;
    }

    const Task* best = nullptr;
    for(const auto& task : readyTasks) {
        if(task.GetDeadline() ) {
            if(best == nullptr || task.GetDeadline() < best->GetDeadline()) {
                best = &task;
            }
        }
    }
    return best;
}