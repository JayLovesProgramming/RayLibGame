#pragma once

#define DEBUG true
#define debug DEBUG
#define DEBUG_ACTIVE DEBUG
#define DEBUG_ENABLED DEBUG_ACTIVE
#include <iostream>

template<typename T>

void JPrint(T message)
{   
    if (DEBUG)
    {
        std::cout << message << std::endl;
    }
    return;
}
