/* DependencyGraph.hpp */

#ifndef DEPENDENCYGRAPH_HPP
#define DEPENDENCYGRAPH_HPP

#include "Task.hpp"
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <optional>

class DependencyGraph {
public:

    // constructor / destructor
    DependencyGraph() = default;
    ~DependencyGraph() = default;

    // add task
    void AddTask(const Task& task);

    // add dependency (adds to m_adjacency)
    void AddDependency(int id, int dependsOnId);

    // has cycle - does a DFS to find 
    bool HasCycle();

    // get tasks that are ready
    std::vector<Task> GetReadyTasks(int currentTime, const std::unordered_set<int>& completedIds) const;

    // task getterr
    const std::optional<Task> GetTask(int id) const;

private:
    std::unordered_map<int, Task> m_tasks;
};
#endif