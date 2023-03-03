//
// Created by Will on 3/3/2023.
//

#ifndef STEAMWORKS_H
#define STEAMWORKS_H

#include "steam_api.h"

#define MAX_CONTROLLERS 1

class Steamworks
{
    InputHandle_t controllerHandles[MAX_CONTROLLERS];

public:
    int init();
    void update();
};

#endif //STEAMWORKS_H
