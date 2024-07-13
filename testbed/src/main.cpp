#include <core/log/logger.h>

int main()
{
    using namespace Hydro;

    LOG_FATAL("Test: 1");
    LOG_ERROR("Test: 2");
    LOG_WARN("Test: 3");
    LOG_INFO("Test: 4");
    LOG_DEBUG("Test: 5");
    LOG_TRACE("Test: 6");

    return 0;
}