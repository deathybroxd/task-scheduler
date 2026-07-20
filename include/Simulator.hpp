/* Simulator.hpp */ 

#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include "DependencyGraph.hpp"
#include "EDFScheduler.hpp"
#include "Report.hpp"
#include "SimClock.hpp"
#include <iostream>
#include <string>
#include <unordered_set>



class Simulator {
public:
    // constructor
    Simulator(int startTime = 0);

    // destructor 
    ~Simulator() = default;

    void Run();

private:
    DependencyGraph m_graph;
    EDFScheduler m_scheduler;
    Report m_reporter;
    SimClock m_clock;
    std::unordered_set<int> m_completedIds;

};
#endif