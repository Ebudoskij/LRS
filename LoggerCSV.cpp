#include "LoggerCSV.h"

CsvLogger::CsvLogger(const std::string& filename) : filename_(filename) {
    std::ifstream check_file(filename_);

    is_first_write_ = !check_file.is_open() || (check_file.peek() == std::ifstream::traits_type::eof());
}

void CsvLogger::log(const std::string& algorithm, 
                    const std::string& optimization, 
                    long volume, 
                    int threads, 
                    long long time_us, 
                    int result) 
{
    std::ofstream file(filename_, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename_ << " for logging." << std::endl;
        return;
    }

    if (is_first_write_) {
        file << "Algorithm,Optimization,Volume,Threads,Time_us,Result\n";
        is_first_write_ = false;
    }

    file << std::format("{},{},{},{},{},{}\n", 
                        algorithm, 
                        optimization, 
                        volume, 
                        threads, 
                        time_us, 
                        result);
    
    file.close();
}