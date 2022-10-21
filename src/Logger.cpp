#include <game/Logger.hpp>

#define LOGGING

std::string Logger::ansiColor = Logger::color(46, 1);
std::vector<std::string> Logger::buffer;

void Logger::log(LogLevel level, std::string message) {
    //#ifdef LOGGING
        int levelColor = 32 + level * 2;
        std::string t = time();
        auto time = t.substr(0, t.size() - 1);
        auto str = color(levelColor) + "[" + time + "] " + message + reset() + "\n";
        std::cout << str;
        Logger::buffer.push_back("[" + time + "] " + message + "\n");
    //#endif
}

void Logger::save(std::string path) {
    std::ofstream file;
    file.open(path);
    for (auto str : Logger::buffer)
        file << str;
    file.close();
}

void Logger::log(std::string message) { log(LogLevel::INFO, message); }

void Logger::title(std::string message) {
    std::cout << Logger::ansiColor << message << reset() << std::endl;
}

std::string Logger::datetime() {
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return std::string(std::ctime(&t));
}

std::string Logger::time()
{
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    auto timer = std::chrono::system_clock::to_time_t(now);
    std::tm bt = *std::localtime(&timer);
    std::ostringstream oss;
    oss << std::put_time(&bt, "%H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

std::string Logger::color(int n) {
    return "\u001b[" + std::to_string(n) + "m";
}

std::string Logger::color(int n, int m) {
    return "\u001b[" + std::to_string(n) + ";" + std::to_string(m) + "m";
}



std::string Logger::reset() { return "\u001b[0m"; }