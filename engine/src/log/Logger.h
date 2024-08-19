#pragma once
#include "Defines.h"
#include <string>


namespace Hydro::log
{

    enum Level
    {
        FATAL = 0,
        ERROR = 1,
        WARN = 2,
        INFO = 3,
        DEBUG = 4,
        TRACE = 5
    };

    class Logger
    {
    public:
        Logger();
        ~Logger();
        //TODO: Add ability to log to diffrent outputs file console etc.
        HAPI void log_message(Level level, const std::string& message);
    };

    HAPI Logger& GetLogger();

    #define LOG_LEVEL INFO

    #if LOG_LEVEL >= FATAL
    #define LOG_FATAL(message) Hydro::log::GetLogger().log_message(Hydro::log::FATAL, message);
    #else
    #define LOG_FATAL(message)
    #endif

    #if LOG_LEVEL >= ERROR
    #define LOG_ERROR(message) Hydro::log::GetLogger().log_message(Hydro::log::ERROR, message);
    #else
    #define LOG_ERROR(message)
    #endif

    #if LOG_LEVEL >= WARN
    #define LOG_WARN(message) Hydro::log::GetLogger().log_message(Hydro::log::WARN, message);
    #else
    #define LOG_WARN(message)
    #endif

    #if LOG_LEVEL >= INFO
    #define LOG_INFO(message) Hydro::log::GetLogger().log_message(Hydro::log::INFO, message);
    #else
    #define LOG_INFO(message)
    #endif

    #if LOG_LEVEL >= DEBUG
    #define LOG_DEBUG(message) Hydro::log::GetLogger().log_message(Hydro::log::DEBUG, message);
    #else
    #define LOG_DEBUG(message)
    #endif

    #if LOG_LEVEL >= TRACE
    #define LOG_TRACE(message) Hydro::log::GetLogger().log_message(Hydro::log::TRACE, message);
    #else
    #define LOG_TRACE(message)
    #endif
}