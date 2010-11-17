#include "xEngine.h"

#include <unistd.h>

void xSleep(xUInt32 milliseconds)
{
    usleep(milliseconds * 1000);
}
