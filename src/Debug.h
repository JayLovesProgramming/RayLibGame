#pragma once

#include <iostream>

template<typename T>

#define DEBUG true
#define debug DEBUG
#define DEBUG_ACTIVE DEBUG
#define DEBUG_ENABLED DEBUG_ACTIVE
#define MUSIC_ENABLED true

void JPrint(T message)
{   
    if (DEBUG)
    {
        std::cout << message << std::endl;
    }
    return;
}
