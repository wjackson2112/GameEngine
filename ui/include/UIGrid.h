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
    UIGD_RIGHT,
    UIGD_DOWN,
    UIGD_LEFT
};

class UIGrid
{
    std::vector<Entity*> elements;

    UIGridDirection prevDirection = UIGD_NONE;
    float bearing = 0.0f;

public:
    void registerElement(Entity* element);
    void deregisterElement(Entity* element);

    Entity* getElementAbove(Entity* element);
    Entity* getElementBelow(Entity* element);
    Entity* getElementToLeft(Entity* element);
    Entity* getElementToRight(Entity* element);

private:
    void updateBearing(UIGridDirection newDirection, Entity* element);
};

#endif //UI_GRID_H
