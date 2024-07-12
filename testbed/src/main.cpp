#include <core/logger.h>

int main()
{
    HFATAL("Test: %d", 1);
    HERROR("Test: %d", 2);
    HWARN("Test: %d", 3);
    HINFO("Test: %d", 4);
    HDEBUG("Test: %d", 5);
    HTRACE("Test: %d", 6);

    return 0;
}