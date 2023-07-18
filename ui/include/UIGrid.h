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

enum UIGridPriority
{
    UIGD_PRIORITIZE_AXIS,
    UIGD_PRIORITIZE_BEARING,
    UIGD_PRIORITIZE_ALIGNMENT
};

class UIGrid
{
    std::vector<Entity*> elements;

    UIGridDirection prevDirection = UIGD_NONE;
    UIGridPriority priorityX = UIGD_PRIORITIZE_AXIS;
    UIGridPriority priorityY = UIGD_PRIORITIZE_AXIS;
    float bearing = 0.0f;

public:
    bool wrapX = false;
    bool wrapY = false;

    void registerElement(Entity* element);
    void deregisterElement(Entity* element);
    void deregisterAllElements();

    void setPriorityX(UIGridPriority priority) {this->priorityX = priority;};
    void setPriorityY(UIGridPriority priority) {this->priorityY = priority;};

    Entity* getElementAbove(Entity* element);
    Entity* getElementAbove(glm::vec2 position);

    Entity* getElementBelow(Entity* element);
    Entity* getElementBelow(glm::vec2 position);

    Entity* getElementToLeft(Entity* element);
    Entity* getElementToLeft(glm::vec2 position);

    Entity* getElementToRight(Entity* element);
    Entity* getElementToRight(glm::vec2 position);

    void clearBearing();

private:
    void updateBearing(UIGridDirection newDirection, glm::vec2 position);
};

#endif //UI_GRID_H
