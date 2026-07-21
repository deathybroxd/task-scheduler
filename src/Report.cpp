/* Report.cpp */

#include "Report.hpp"
#include <fstream>
#include <filesystem>

std::ostream& operator<<(std::ostream& out, const CompletionRecord& record) {
    return out << record.taskId << "|" 
        << record.arrivalTime << "|" 
        << record.deadline << "|" 
        << record.completionTime << "|" 
        << (record.deadlineMet ? "Met deadline" : "Late");
}


void Report::RecordResult(const Task& task, int completionTime) {
    m_records.emplace_back(task.GetId(), 
        task.GetArrivalTime(), 
        task.GetDeadline(), 
        completionTime, 
        (task.GetDeadline() < completionTime ? true : false)
    );
}

void Report::PrintSummary() const {
    std::cout << "===== RECORD SUMMARY =====" << std::endl;
    for(const CompletionRecord& record : m_records) {
        std::cout << record << std::endl;
    }
}

void Report::ExportCSV() {
    std::string filename = GetFilename();
    std::ofstream file(filename);
    if(!file.is_open()) {
        std::cerr << "ERROR: file " << filename << " could not be opened" << std::endl;
        return;
    }

    file << "Task Id|Arrival Time|Deadline|Completion Time|Status|Lateness" << std::endl;
    for(const CompletionRecord& record : m_records) {
        file << record << std::endl;
    }

    std::cout << "Data saved successfully as: " << filename << std::endl;
    file.close();
}

// PRIVATE HELPER

std::string Report::GetFilename() {
    int counter = 1;
    std::string filename;

    do {
        filename = BASE_FILENAME + std::to_string(counter) + BASE_FILENAME_EXT;
        counter++;
    } while(std::filesystem::exists(filename));

    return filename;
}   