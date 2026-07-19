/* Report.hpp */
#ifndef REPORT_HPP
#define REPORT_HPP

#include "Task.hpp"
#include <iostream>
#include <vector>
#include <string>

struct CompletionRecord {
    int taskId, arrivalTime, deadline, completionTime;
    bool deadlineMet;

    explicit CompletionRecord(int id, int arrival, int whenDue, int whenCompleted, bool finishedOnTime) :
    taskId(id), arrivalTime(arrival), deadline(whenDue), completionTime(whenCompleted), deadlineMet(finishedOnTime) {}

    friend std::ostream& operator<<(std::ostream& out, const CompletionRecord& record);
};

class Report {
public:

    Report() = default;
    ~Report() = default;

    // recordresult
    // determines if a task has been completed on time or not and records it
    void RecordResult(const Task& task, int completionTime);
    
    // prints summary
    void PrintSummary() const;

    // exports summary into a csv
    void ExportCSV(const std::string& filename) const;

private:
    std::vector<CompletionRecord> m_records;

};
#endif