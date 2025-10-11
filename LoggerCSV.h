#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <format>

class CsvLogger {
private:
    std::string filename_;
    bool is_first_write_ = true;

public:
    CsvLogger(const std::string& filename);

    void log(const std::string& algorithm, 
             const std::string& optimization, 
             long volume, 
             int threads, 
             long long time_us, 
             int result);
};