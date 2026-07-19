/* TaskSchedulerTests.cpp */
#include "Task.hpp"
#include "DependencyGraph.hpp"
#include "EDFScheduler.hpp"
#include "Report.hpp"
#include "SimClock.hpp"
#include <iostream>
#include <string>
#include <array>

int main() {
    DependencyGraph graph;
    Task task1(1, 0, 0, 0, 0, 0, Task::TaskState::PENDING);
    Task task2(2, 0, 0, 0, 0, 0, Task::TaskState::PENDING);
    Task task3(3, 0, 0, 0, 0, 0, Task::TaskState::PENDING);
    Task task4(4, 0, 0, 0, 0, 0, Task::TaskState::PENDING);
    Task task5(5, 0, 0, 0, 0, 0, Task::TaskState::PENDING);
    Task task6(6, 0, 0, 0, 0, 0, Task::TaskState::PENDING);
    std::array<Task, 6> taskList = {task1, task2, task3, task4, task5, task6};

    for(const auto& task : taskList) { 
        graph.AddTask(task);
    }

    graph.AddDependency(1, 2);
    graph.AddDependency(2, 3);
    graph.AddDependency(3, 1);
    std::cout << graph.HasCycle() << std::endl;
}