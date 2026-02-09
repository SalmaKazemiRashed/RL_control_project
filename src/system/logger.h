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
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

class Logger {
public:
    Logger(const std::string& filename) : file(filename, std::ios::out) {
        if(!file.is_open()){
            std::cerr << "Failed to open log file: " << filename << std::endl;
        }
    }

    ~Logger(){
        if(file.is_open()) file.close();
    }

    // Write CSV header
    void write_header(const std::vector<std::string>& header){
        for(size_t i=0;i<header.size();i++){
            file << header[i];
            if(i < header.size()-1) file << ",";
        }
        file << "\n";
    }

    // Log a vector of doubles as a CSV row
    void log_vector(const std::vector<double>& data){
        for(size_t i=0;i<data.size();i++){
            file << data[i];
            if(i < data.size()-1) file << ",";
        }
        file << "\n";
    }

private:
    std::ofstream file;
};