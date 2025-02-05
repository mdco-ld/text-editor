#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <format>
#include <fstream>
#include <sstream>
#include <string_view>

#if defined(DEVELOPMENT)

#define _LOG_DEBUG0(fmt)                                                       \
    do {                                                                       \
        Logger::get().println("[DEBUG] @ ({}:<{}.{}>): " fmt, __FILE__,        \
                              __func__, __LINE__);                             \
    } while (false);

#define _LOG_DEBUG1(fmt, ...)                                                  \
    do {                                                                       \
        Logger::get().println("[DEBUG] @ ({}:<{}.{}>): " fmt, __FILE__,        \
                              __func__, __LINE__, __VA_ARGS__);                \
    } while (false);

#define _GET_LOG_DEBUG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME

#define LOG_DEBUG(...)                                                         \
    _GET_LOG_DEBUG(__VA_ARGS__, _LOG_DEBUG1, _LOG_DEBUG1, _LOG_DEBUG1,         \
                   _LOG_DEBUG1, _LOG_DEBUG1, _LOG_DEBUG1, _LOG_DEBUG1,         \
                   _LOG_DEBUG1, _LOG_DEBUG1, _LOG_DEBUG0)                      \
    (__VA_ARGS__)

#else

#define LOG_DEBUG(...)

#endif

#define _LOG_INFO0(fmt)                                                        \
    do {                                                                       \
        Logger::get().println("[INFO] @ ({}:<{}.{}>): " fmt, __FILE__,         \
                              __func__, __LINE__);                             \
    } while (false);

#define _LOG_INFO1(fmt, ...)                                                   \
    do {                                                                       \
        Logger::get().println("[INFO] @ ({}:<{}.{}>): " fmt, __FILE__,         \
                              __func__, __LINE__, __VA_ARGS__);                \
    } while (false);

#define _GET_LOG_INFO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME

#define LOG_INFO(...)                                                          \
    _GET_LOG_INFO(__VA_ARGS__, _LOG_INFO1, _LOG_INFO1, _LOG_INFO1, _LOG_INFO1, \
                  _LOG_INFO1, _LOG_INFO1, _LOG_INFO1, _LOG_INFO1, _LOG_INFO1,  \
                  _LOG_INFO0)                                                  \
    (__VA_ARGS__)

#define _LOG_WARN0(fmt)                                                        \
    do {                                                                       \
        Logger::get().println("[WARN] @ ({}:<{}.{}>): " fmt, __FILE__,         \
                              __func__, __LINE__);                             \
    } while (false);

#define _LOG_WARN1(fmt, ...)                                                   \
    do {                                                                       \
        Logger::get().println("[WARN] @ ({}:<{}.{}>): " fmt, __FILE__,         \
                              __func__, __LINE__, __VA_ARGS__);                \
    } while (false);

#define _GET_LOG_WARN(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME

#define LOG_WARN(...)                                                          \
    _GET_LOG_WARN(__VA_ARGS__, _LOG_WARN1, _LOG_WARN1, _LOG_WARN1, _LOG_WARN1, \
                  _LOG_WARN1, _LOG_WARN1, _LOG_WARN1, _LOG_WARN1, _LOG_WARN1,  \
                  _LOG_WARN0)                                                  \
    (__VA_ARGS__)

#define _LOG_ERROR0(fmt)                                                       \
    do {                                                                       \
        Logger::get().println("[ERROR] @ ({}:<{}.{}>): " fmt, __FILE__,        \
                              __func__, __LINE__);                             \
    } while (false);

#define _LOG_ERROR1(fmt, ...)                                                  \
    do {                                                                       \
        Logger::get().println("[ERROR] @ ({}:<{}.{}>): " fmt, __FILE__,        \
                              __func__, __LINE__, __VA_ARGS__);                \
    } while (false);

#define _GET_LOG_ERROR(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME

#define LOG_ERROR(...)                                                         \
    _GET_LOG_ERROR(__VA_ARGS__, _LOG_ERROR1, _LOG_ERROR1, _LOG_ERROR1,         \
                   _LOG_ERROR1, _LOG_ERROR1, _LOG_ERROR1, _LOG_ERROR1,         \
                   _LOG_ERROR1, _LOG_ERROR1, _LOG_ERROR0)                      \
    (__VA_ARGS__)

class Logger {
  public:
    static Logger &get();

    template <typename... T>
    void println(std::format_string<T...> fmt, T &&...args) {
        _println(std::format(fmt, std::forward<T>(args)...));
    }

    void printlnAtExit(std::string_view message);

  private:
    void _println(std::string_view message);

    Logger();
    ~Logger();

    std::ofstream logFile_;
    std::stringstream deferred_;
};

#endif
