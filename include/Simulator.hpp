/* Simulator.hpp */ 

#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include "DependencyGraph.hpp"
#include "EDFScheduler.hpp"
#include "Report.hpp"
#include "SimClock.hpp"
#include <unordered_set>
#include <optional>



class Simulator {
public:
    // constructor
    Simulator(int startTime = 0);

    // destructor 
    ~Simulator() = default;

    // add task
    void AddTask(const Task& task);

    // add dependency
    void AddDependency(int id, int dependsOnId);

    // has cycle
    bool HasCycle();

    // run the program
    void Run();  
    
private:

    // simulation checker
    bool IsSimulationComplete() const;

    // missing deadline check
    void CheckMissedDeadlines();
    
    // attempt a new task
    void TryStartNextTask();

    void CheckTaskCompletion();

    struct RunningTask {
        std::optional<int> id;
        int finishTime;
    };
    
    SimClock m_clock;
    RunningTask m_runningTask;
    DependencyGraph m_graph;
    EDFScheduler m_scheduler;
    Report m_reporter;
    std::unordered_set<int> m_completedIds;

};
#endif