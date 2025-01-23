// Copyright 2024 Daniel Dsouza
#include <iostream>
#include <fstream>
#include <regex>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

using std::cout, std::cin, std::endl, std::string, std::getline, std::vector;
using std::ifstream, std::ofstream, std::regex_match, std::regex, std::smatch;
using boost::posix_time::ptime, boost::posix_time::time_duration;
using boost::posix_time::time_from_string;

struct BootupEntry {
    int startLineNumber;
    ptime startTime;
    int endLineNumber;
    ptime endTime;
    bool success;
    time_duration duration;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <log_file>" << endl;
        return 1;
    }

    string logFilePath = argv[1];
    string reportFilePath = logFilePath + ".rpt";

    ifstream logFile(logFilePath);
    ofstream reportFile(reportFilePath);

    if (!logFile.is_open()) {
        cout << "Error opening log file: " << logFilePath << endl;
        return 1;
    }

    if (!reportFile.is_open()) {
        cout << "Error opening report file: " << reportFilePath << endl;
        return 1;
    }

    string line;
    int lineNumber = 0;
    vector<BootupEntry> bootupEntries;
    int successfulBoots = 0;

    regex serverStartedRegex(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}: \(log.c.166\) server started)");
    regex bootCompletedRegex(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}.\d{3}:INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080)");

    while (getline(logFile, line)) {
        lineNumber++;

        smatch serverStartedMatch;
        if (regex_search(line, serverStartedMatch, serverStartedRegex)) {
            BootupEntry entry;
            entry.startLineNumber = lineNumber;
            entry.startTime = time_from_string(line.substr(0, 19));
            entry.success = false;
            bootupEntries.push_back(entry);
        }

        smatch bootCompletedMatch;
        if (regex_search(line, bootCompletedMatch, bootCompletedRegex)) {
            if (!bootupEntries.empty()) {
                BootupEntry& lastEntry = bootupEntries.back();
                if (!lastEntry.success) {
                    lastEntry.endLineNumber = lineNumber;
                    lastEntry.endTime = time_from_string(line.substr(0, 19));
                    lastEntry.success = true;
                    lastEntry.duration = lastEntry.endTime - lastEntry.startTime;
                    successfulBoots++;
                }
            }
        }
    }

    // Output the report
    reportFile.imbue(std::locale(std::locale::classic(),
    new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S")));
    reportFile << "Device Boot Report\n\n";
    reportFile << "InTouch log file: " << logFilePath << endl;
    reportFile << "Lines Scanned: " << lineNumber << "\n\n";
    reportFile << "Device boot count: initiated = " << bootupEntries.size()
               << ", completed: " << successfulBoots << "\n\n\n";

    for (const auto& entry : bootupEntries) {
        reportFile << "=== Device boot ===\n";
        reportFile << entry.startLineNumber << "(" << logFilePath << "): "
                   << entry.startTime << " Boot Start\n";
        if (entry.success) {
            reportFile << entry.endLineNumber << "(" << logFilePath << "): "
                       << entry.endTime << " Boot Completed\n";
            reportFile << "\tBoot Time: " << entry.duration.total_milliseconds() << "ms \n";
        } else {
            reportFile << "**** Incomplete boot ****\n";
        }
        reportFile << endl;
    }

    logFile.close();
    reportFile.close();
    return 0;
}
