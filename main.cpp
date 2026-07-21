/* main.cpp */
#include "Simulator.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

static constexpr int NUM_TASKS = 100;

int main() {
    std::srand(std::time(nullptr));
    std::vector<Task> testTasks;
    testTasks.reserve(NUM_TASKS);
    Simulator sim(0);

    for(int i = 0; i < NUM_TASKS; ++i) {
        testTasks.emplace_back(i, std::rand() % 100, std::rand() % 100, std::rand() % 100, std::rand() % 100, std::rand() % 100, Task::TaskState::PENDING);
        sim.AddTask(testTasks.at(i));
    }

    for(int i = 0; i < NUM_TASKS/2; ++i) {
        int id = std::rand() % 99;
        int dependsOnId = std::rand() % 99;
        if(id != dependsOnId) {
            sim.AddDependency(id, dependsOnId);
        }
    }

    sim.Run();
    return 0;   
}