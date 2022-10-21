#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iomanip>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <vector>

enum LogLevel {ERROR, WARN, INFO, ALERT};

class Logger {
private:
    static std::vector<std::string> buffer;
public:
    static std::string ansiColor;
    static void save(std::string path);
    static void log(LogLevel level, std::string message);
    static void log(std::string message);
    static void title(std::string message);
    inline static std::string datetime();
    inline static std::string time();
    inline static std::string reset();
    inline static std::string color(int n);
    inline static std::string color(int n, int m);
};

#endif