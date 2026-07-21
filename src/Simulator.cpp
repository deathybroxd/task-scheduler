/* Simulator.cpp */

#include "Simulator.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>

Simulator::Simulator(int startTime) : 
m_clock(startTime) {}

void Simulator::AddTask(const Task& task) {
    m_graph.AddTask(task);
}

void Simulator::AddDependency(int id, int dependsOnId) {
    m_graph.AddDependency(id, dependsOnId);
}

bool Simulator::HasCycle() {
    return m_graph.HasCycle();
}

void Simulator::Run() {
    if(m_graph.HasCycle()) {
        std::cerr << "ERROR: Dependency graph contains a cycle " << std::endl;
        return;
    }

    while(!IsSimulationComplete()) {
        CheckMissedDeadlines();
        TryStartNextTask();
        m_clock.Advance(1);
        CheckTaskCompletion();
    }
    m_reporter.ExportCSV();
}

// PRIVATE METHODS //

bool Simulator::IsSimulationComplete() const {
    const std::unordered_map<int, Task>& tasks = m_graph.GetAllTasks();
    for(const auto& pair : tasks) {
        Task::TaskState taskState = pair.second.GetState();
        if(taskState != Task::TaskState::COMPLETED && taskState != Task::TaskState::MISSED_DEADLINE) {
            return false; // there is at least one task that is not completed or has missed their deadline
        }
    }
    return true; 
}

void Simulator::CheckMissedDeadlines() {
    const std::unordered_map<int, Task>& tasks = m_graph.GetAllTasks();
    for(const auto& pair : tasks) {
        if(pair.second.GetState() == Task::TaskState::COMPLETED || pair.second.GetState() == Task::TaskState::MISSED_DEADLINE) {
            continue;
        }

        if(m_clock.Now() > pair.second.GetDeadline()) {
            m_graph.SetTaskState(pair.second.GetId(), Task::TaskState::MISSED_DEADLINE);
            m_reporter.RecordResult(pair.second, m_clock.Now());
        }
    }
}

void Simulator::TryStartNextTask() {
    if(m_runningTask.id.has_value()) {
        return;
    }

    std::vector<Task> readyTasks = m_graph.GetReadyTasks(m_clock.Now(), m_completedIds);
    if(!readyTasks.empty()) {
        const Task* runningTask = m_scheduler.SelectNextTask(readyTasks);
        m_runningTask.id = runningTask->GetId();
        m_runningTask.finishTime = m_clock.Now() + runningTask->GetDuration();
        m_graph.SetTaskState(runningTask->GetId(), Task::TaskState::RUNNING);
    }
}

void Simulator::CheckTaskCompletion() {
    if(m_runningTask.id.has_value() && m_clock.Now() >= m_runningTask.finishTime) {
        m_graph.SetTaskState(m_runningTask.id.value(), Task::TaskState::COMPLETED);
        m_completedIds.emplace(m_runningTask.id.value());
        m_reporter.RecordResult(m_graph.GetTask(m_runningTask.id.value()).value(), m_clock.Now());
        
        // reset running task
        m_runningTask.id = std::nullopt;
        m_runningTask.finishTime = 0;
    }
}