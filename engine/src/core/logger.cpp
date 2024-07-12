#include "logger.h"


//TODO: TEMP
#include <iostream>
#include <sstream>
#include <stdarg.h>

bool initilize_logging()
{
    //TODO: CRAETE LOG FILE
    return true;
}

void shutdown_logging()
{
    //TODO: CELANUP
}

void log_output(log_level level, std::string message, ...)
{
    const std::string level_strings[6] = {
        "\033[0;31m[FATAL]: \033[0m",
        "\033[1;31m[ERROR]: \033[0m",
        "\033[1;33m[WARN]:  \033[0m",
        "\033[1;36m[INFO]:  \033[0m",
        "[DEBUG]: ",
        "[TRACE]: "};

    // Build the formatted message
    std::ostringstream formatted_message;
    formatted_message << level_strings[level];

    // Handling variable arguments
    va_list args;
    va_start(args, message);

    // Use vsnprintf to handle the variable arguments
    char buffer[32000]; // Adjust size as necessary
    vsnprintf(buffer, sizeof(buffer), message.c_str(), args);

    // Append the formatted message to the output
    formatted_message << buffer;

    va_end(args);

    // Output to console
    std::cout << formatted_message.str() << std::endl;
}