#include <logger.hpp>

#include <iostream>

std::string_view getLogFile() {
    // TODO: Make this find a proper log file
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
