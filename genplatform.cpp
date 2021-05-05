#include "genplatform.h"
#include <cstdlib>
#define NORM_PLATFORM 0
#define DISAPPEAR_PLATFORM 1
#define MOVING_PLATFORM 2



platform *genplatform(int result)
{
    int platform_type, num_platform = 1;
    platform* ptr;
    if(result <= 2000)
        num_platform = 1;
    else if(result > 2000 && result <= 4000)
        num_platform = 2;
    else
        num_platform = 3;

    platform_type = random() % num_platform;

    switch (platform_type) {
    case NORM_PLATFORM:
        ptr = new norm_platform;
        break;
    case DISAPPEAR_PLATFORM:
        ptr = new disappear_platform;
        break;
    case MOVING_PLATFORM:
        ptr = new moving_platform;
        break;
    }

    return ptr;
}
