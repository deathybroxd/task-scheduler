/* DependencyGraph.hpp */

#ifndef DEPENDENCYGRAPH_HPP
#define DEPENDENCYGRAPH_HPP

#include "Task.hpp"
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <optional>
#include <cstddef>

class DependencyGraph {
public:

    // constructor / destructor
    DependencyGraph() = default;
    ~DependencyGraph() = default;

    // add task
    void AddTask(const Task& task);

    // add dependency (adds to m_adjacency)
    void AddDependency(int id, int dependsOnId);

    // has cycle - does a black/gray/white DFS to find cycles
    bool HasCycle();

    // get tasks that are ready - this is returned by value because it creates a new vector every time - not a real getter
    std::vector<Task> GetReadyTasks(int currentTime, const std::unordered_set<int>& completedIds) const;

    // getter for all tasks
    const std::unordered_map<int, Task>& GetAllTasks() const;

    // task getterr 
    std::optional<Task> GetTask(int id) const;

    // set task state
    void SetTaskState(int id, Task::TaskState state);

    // isempty
    bool IsEmpty();

    // getsize
    std::size_t GetSize();

private:
    // recursive helper for hascycle
    bool HasCycleHelper(int id, std::unordered_set<int>& visiting, std::unordered_set<int>& visited);

    std::unordered_map<int, Task> m_tasks;
};
#endif