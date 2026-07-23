/* TestEDFScheduler.cpp */
#include <gtest/gtest.h>
#include <vector>
#include <unordered_set>
#include "DependencyGraph.hpp"
#include "EDFScheduler.hpp"

TEST(EDFSchedulerTest, SelectNextTaskTest) {
    DependencyGraph graph;
    EDFScheduler scheduler;
    
    constexpr int ARRIVED_ON_TIME = 0;
    constexpr int TASK0_DEADLINE = 1;
    constexpr int TASK1_DEADLINE = 5;
    constexpr int TASK2_DEADLINE = 10;

    Task task0(0, 0, ARRIVED_ON_TIME, TASK0_DEADLINE, 0, 0, Task::TaskState::READY);
    Task task1(1, 0, ARRIVED_ON_TIME, TASK1_DEADLINE, 0, 0, Task::TaskState::PENDING);
    Task task2(2, 0, ARRIVED_ON_TIME, TASK2_DEADLINE, 0, 0, Task::TaskState::READY);
    graph.AddTask(task0);
    graph.AddTask(task1);
    graph.AddTask(task2);

    constexpr int PRESENT_TIME = 10;
    const std::unordered_set<int> completedIds; // intentionally empty
    std::vector<Task> readyTasks;

    EXPECT_EQ(scheduler.SelectNextTask(readyTasks), nullptr);

    readyTasks = graph.GetReadyTasks(PRESENT_TIME, completedIds);
    EXPECT_EQ(readyTasks.size(), 3);
    
    // selectnexttask returns a task* to a task:
    const Task* ptr0 = scheduler.SelectNextTask(readyTasks);
    EXPECT_EQ(ptr0->GetId(), 0);
    for(std::size_t i = 0; i < readyTasks.size(); ++i) {
        if(readyTasks.at(i).GetId() == 0) {
            readyTasks.erase(readyTasks.begin() + i);
            --i;
            break;
        }
    }

    const Task* ptr1 = scheduler.SelectNextTask(readyTasks);
    EXPECT_EQ(ptr1->GetId(), 1);
    for(std::size_t i = 0; i < readyTasks.size(); ++i) {
        if(readyTasks.at(i).GetId() == 1) {
            readyTasks.erase(readyTasks.begin() + i);
            --i;
            break;
        }
    }

    const Task* ptr2 = scheduler.SelectNextTask(readyTasks);
    EXPECT_EQ(ptr2->GetId(), 2);
}
