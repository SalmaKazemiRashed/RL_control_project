/*
#pragma once
#include <fstream>
#include <iostream>

class Logger {
public:
    Logger(const std::string& path) {
        file.open(path);
        if (!file.is_open()) {
            std::cerr << "ERROR: Failed to open log file: " << path << std::endl;
        } else {
            file << "step,error,energy,q0,q1,q2,q3,q4,q5\n";
            file.flush();
        }
    }

    void log(int step, double error, double energy, const std::vector<double>& positions) {
    file << step << "," << error << "," << energy;
    for (auto p : positions) file << "," << p;
    file << "\n";
}

    ~Logger() {
        if (file.is_open()) {
            file.flush();
            file.close();
        }
    }

private:
    std::ofstream file;
};
*/
#pragma once
#include <iostream>

inline void log(const char* msg) {
    std::cout << msg << std::endl;
}