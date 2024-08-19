#include "Logger.h"
#include <iostream>

namespace Hydro::log
{
    Logger::Logger() 
    {
        //TODO: Initlize files and other outputs
    }

    Logger::~Logger()
    {
        //TODO: Close files and other outputs
    }

    void Logger::log_message(Level level, const std::string& message)
    {
        //HACK: This is a hack to get colored output in the console and will not work on all systems
        std::string level_str[6] = {
            "\033[31m [FATAL]: \033[0m",
            "\033[1;31m [ERROR]: \033[0m",
            "\033[33m [WARN]: \033[0m", 
            "\033[1;32m [INFO]: \033[0m",
            "\033[1;36m [DEBUG]: \033[0m",
            "\033[1;34m [TRACE]: \033[0m" 
        };

        std::cout << level_str[level] << message << std::endl;
    }

    Logger& GetLogger()
    {
        static Logger logger;
        return logger;
    }
}