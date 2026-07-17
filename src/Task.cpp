/* Task.cpp */
#include "Task.hpp"

Task::Task(int id, int priority, int arrivalTime, int deadline, int duration, int remainingTime, TaskState state) :
m_id(id), m_priority(priority), m_arrivalTime(arrivalTime), m_deadline(deadline), m_duration(duration), m_remainingTime(remainingTime), m_state(state) {}

int Task::GetId() const {
    return m_id;
}

int Task::GetPriority() const {
    return m_priority;
}

int Task::GetArrivalTime() const {
    return m_arrivalTime;
}

int Task::GetDeadline() const {
    return m_deadline;
}

int Task::GetDuration() const {
    return m_duration;
}

int Task::GetRemainingTime() const {
    return m_remainingTime;
}

const std::vector<int>& Task::GetDependencies() const {
    return m_dependencies;
}

void Task::AddDependency(int dependsOnId) {
    m_dependencies.emplace_back(dependsOnId);
}

Task::TaskState Task::GetState() const {
    return m_state;
}

void Task::SetState(Task::TaskState state) {
    m_state = state;
}

