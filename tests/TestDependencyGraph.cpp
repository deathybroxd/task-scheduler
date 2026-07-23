/* TestDependencyGraph.cpp */

#include <gtest/gtest.h>
#include <vector>
#include <unordered_set>
#include "DependencyGraph.hpp"

TEST(DependencyGraphTest, AddGetTaskTest) {
    DependencyGraph graph;

    // graph should be empty
    EXPECT_TRUE(graph.IsEmpty());
    EXPECT_EQ(graph.GetSize(), 0);
    graph.AddTask(Task(0, 0, 0, 0, 0, 0, Task::TaskState::PENDING));
    graph.AddTask(Task(1, 1, 1, 1, 1, 1, Task::TaskState::PENDING));
    graph.AddTask(Task(2, 2, 2, 2, 2, 2, Task::TaskState::PENDING));
    
    EXPECT_FALSE(graph.IsEmpty());
    EXPECT_EQ(graph.GetSize(), 3);

    EXPECT_EQ(graph.GetTask(0).value().GetId(), 0);
    EXPECT_EQ(graph.GetTask(1).value().GetId(), 1);
    EXPECT_EQ(graph.GetTask(2).value().GetId(), 2);
}

TEST(DependencyGraphTest, AddDependencyTest) {
    DependencyGraph graph;

    graph.AddTask(Task(0, 0, 0, 0, 0, 0, Task::TaskState::PENDING));
    graph.AddTask(Task(1, 1, 1, 1, 1, 1, Task::TaskState::PENDING));
    graph.AddTask(Task(2, 2, 2, 2, 2, 2, Task::TaskState::PENDING));
    graph.AddDependency(0, 1);
    graph.AddDependency(0, 2);

    EXPECT_EQ(graph.GetTask(0).value().GetDependencies().size(), 2);
}

TEST(DependencyGraphTest, HasCycleTest) {
    DependencyGraph graph;

    graph.AddTask(Task(0, 0, 0, 0, 0, 0, Task::TaskState::PENDING));
    graph.AddTask(Task(1, 1, 1, 1, 1, 1, Task::TaskState::PENDING));
    graph.AddTask(Task(2, 2, 2, 2, 2, 2, Task::TaskState::PENDING));

    EXPECT_FALSE(graph.HasCycle());

    // dependencies but no cycle yet
    graph.AddDependency(0, 1);
    graph.AddDependency(0, 2);

    EXPECT_FALSE(graph.HasCycle());

    // should be a cycle now
    graph.AddDependency(1, 2);
    graph.AddDependency(2, 0);

    EXPECT_TRUE(graph.HasCycle());

}

TEST(DependencyGraphTest, GetReadyTasksTest) {
    DependencyGraph graph;

    // getreadytasks accepts ready and pending tasks
    constexpr int ARRIVED_ON_TIME = 0;
    graph.AddTask(Task(0, 0, ARRIVED_ON_TIME, 0, 0, 0, Task::TaskState::READY));
    graph.AddTask(Task(1, 0, ARRIVED_ON_TIME, 0, 0, 0, Task::TaskState::PENDING));
    graph.AddTask(Task(2, 0, ARRIVED_ON_TIME, 0, 0, 0, Task::TaskState::READY));

    // also add some tests that dont pass
    constexpr int LATE_TIME = 1000;
    graph.AddTask(Task(3, 0, LATE_TIME, 0, 0, 0, Task::TaskState::READY));
    graph.AddTask(Task(4, 0, LATE_TIME, 0, 0, 0, Task::TaskState::PENDING));
    graph.AddTask(Task(5, 0, ARRIVED_ON_TIME, 0, 0, 0, Task::TaskState::MISSED_DEADLINE));
    graph.AddTask(Task(6, 0, ARRIVED_ON_TIME, 0, 0, 0, Task::TaskState::COMPLETED));
    graph.AddTask(Task(7, 0, ARRIVED_ON_TIME, 0, 0, 0, Task::TaskState::COMPLETED));
    graph.AddTask(Task(8, 0, ARRIVED_ON_TIME, 0, 0, 0, Task::TaskState::COMPLETED));
    graph.AddTask(Task(9, 0, ARRIVED_ON_TIME, 0, 0, 0, Task::TaskState::RUNNING));
    
    const std::unordered_set<int> completedIds = {6, 7, 8};

    constexpr int PRESENT_TIME = 10;
    EXPECT_EQ(graph.GetReadyTasks(PRESENT_TIME, completedIds).size(), 3);
}