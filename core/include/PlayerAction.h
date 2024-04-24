//
// Created by Will on 4/7/2024.
//

#ifndef PLAYER_ACTION_H
#define PLAYER_ACTION_H

#include "InputComponent.h"

class PlayerAction
{
    virtual void execute(InputEvent event) = 0;
};

#endif //ACTION_H
