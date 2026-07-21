/* Task.hpp 
Task container class
*/
#ifndef TASK_HPP
#define TASK_HPP

#include <vector>

class Task {
public:
    enum class TaskState { PENDING, READY, RUNNING, COMPLETED, MISSED_DEADLINE };
    
    // constructor
    explicit Task(int id, int priority, int arrivalTime, int deadline, int duration, int remainingTime, TaskState state);

    // destructor
    ~Task() = default;

    // id gettere
    int GetId() const;

    // priority getter
    int GetPriority() const;

    // arrival time getter
    int GetArrivalTime() const;

    // deadline getter
    int GetDeadline() const;

    // duration getter
    int GetDuration() const;

    // remaining time getter
    int GetRemainingTime() const;

    // dependencies getter
    const std::vector<int>& GetDependencies() const;

    // add a dependency
    void AddDependency(int dependsOnId);

    // State getter
    TaskState GetState() const;

    // state setter
    void SetState(TaskState state);
    
    
private:
    int m_id, m_priority, m_arrivalTime, m_deadline, m_duration, m_remainingTime;
    std::vector<int> m_dependencies;
    TaskState m_state;
};




#endif