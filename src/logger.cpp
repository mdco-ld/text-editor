#include <logger.hpp>

#include <filesystem>
#include <iostream>

std::string_view getLogFile() {
    // TODO: Make this find a proper log file
    if (!std::filesystem::exists("debug")) {
        std::filesystem::create_directory("debug");
    }
    return "debug/logs.txt";
}

Logger::Logger() : logFile_(getLogFile().data(), std::ios::app) {}

Logger::~Logger() { std::cerr << deferred_.str(); }

Logger &Logger::get() {
    static Logger instance;
    return instance;
}

// TODO: Make this thread-safe
void Logger::_println(std::string_view message) {
    logFile_ << message << std::endl;
}

void Logger::printlnAtExit(std::string_view message) {
    deferred_ << message << std::endl;
}
