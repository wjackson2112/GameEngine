//
// Created by Will on 7/5/2023.
//

#ifndef UI_GRID_H
#define UI_GRID_H

#include "Entity.h"

enum UIGridDirection
{
    UIGD_NONE,
    UIGD_UP,
    UIGD_DOWN,
    UIGD_LEFT,
    UIGD_RIGHT
};

class UIGrid
{
    UIGridDirection prevDirection = UIGD_NONE;
    std::vector<Entity*> elements;
public:

    void registerElement(Entity* element);
    void deregisterElement(Entity* element);

    Entity* getElementAbove(Entity* element);
    Entity* getElementBelow(Entity* element);
    Entity* getElementToLeft(Entity* element);
    Entity* getElementToRight(Entity* element);
};

#endif //UI_GRID_H
