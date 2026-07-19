/* DependencyGraph.hpp */

#include "DependencyGraph.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <stack>

void DependencyGraph::AddTask(const Task& task) {
    auto it = m_tasks.find(task.GetId());
    if(it != m_tasks.end()) {
        std::cerr << "ERROR: Task id " << std::to_string(task.GetId()) << " already exists" << std::endl;
        return;
    }
    m_tasks.emplace(task.GetId(), task);
}

void DependencyGraph::AddDependency(int id, int dependsOnId) {
    auto it1 = m_tasks.find(id);
    auto it2 = m_tasks.find(dependsOnId);
    if(it1 == m_tasks.end() || it2 == m_tasks.end()) {
        std::cerr << "ERROR: One or more task ids don't exist" << std::endl;
        return;
    }
    it1->second.AddDependency(dependsOnId);
}

bool DependencyGraph::HasCycle() {
    // white nodes are unexplored
    std::unordered_set<int> visiting; // gray
    std::unordered_set<int> visited; // black

    for(const auto& pair : m_tasks) {
        auto it = visited.find(pair.first);
        if(it == visited.end()) {
            if(HasCycleHelper(pair.first, visiting, visited)) {
                return true;
            }
        }
    }
    return false;
}

std::vector<Task> DependencyGraph::GetReadyTasks(int currentTime, const std::unordered_set<int>& completedIds) const {
    std::vector<Task> readyTasks;

    // tasks that are ready are pending, ready, have a valid arrival time, or doesn't have any dependencies that are completed.
    for(const auto& pair : m_tasks) {
        if(pair.second.GetState() != Task::TaskState::PENDING && pair.second.GetState() != Task::TaskState::READY) {
            continue;
        } 
        
        if(pair.second.GetArrivalTime() > currentTime) {
            continue;
        }

        bool dependenciesSatisfied = true;
        for(const auto& id : pair.second.GetDependencies()) {
            if(completedIds.find(id) == completedIds.end()) {
                dependenciesSatisfied = false;
                break;
            }
        }

        if(!dependenciesSatisfied) {
            continue;
        }

        readyTasks.emplace_back(pair.second);
    }
    return readyTasks;
}

const std::optional<Task> DependencyGraph::GetTask(int id) const {
    auto it = m_tasks.find(id);
    if(it == m_tasks.end()) {
        return std::nullopt;
    }
    return it->second;
}

// PRIVATE HELPERS
bool DependencyGraph::HasCycleHelper(int id, std::unordered_set<int>& visiting, std::unordered_set<int>& visited) {
    visiting.emplace(id); // make current node gray
    auto it = m_tasks.find(id);
    for(const auto& dependencyId : it->second.GetDependencies()) {
        if(visiting.find(dependencyId) != visiting.end()) {
            return true; // dependency is already gray, cycle found
        }

        if(visited.find(dependencyId) == visited.end()) { 
            if(HasCycleHelper(dependencyId, visiting, visited)) {
                return true; // if we have ended up back at a id that is black, we must be in a cycle
            }
        }
    }
    visiting.erase(id);
    visited.emplace(id);
    return false;
}