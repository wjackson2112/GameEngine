//
// Created by Will on 7/5/2023.
//

#include <algorithm>
#include "UIGrid.h"

void UIGrid::registerElement(Entity* element)
{
    Entity *x;
    if (std::find(elements.begin(), elements.end(), x) != elements.end())
        return;

    elements.push_back(element);
}

void UIGrid::deregisterElement(Entity* element)
{
    remove(elements.begin(), elements.end(), element);
}

Entity* UIGrid::getElementAbove(Entity* element)
{
    updateBearing(UIGD_UP, element);

    glm::vec2 elementLocation = element->getWorldTransform().getPosition2();
    elementLocation.x = bearing;

    glm::vec2 upVector = glm::vec2(0.0f, -1.0f);

    float bestDistance = INT_MAX;
    float bestAngle = 0;
    Entity* bestEntity = nullptr;

    for(Entity* other : elements)
    {
        // If same element, continue
        if(element == other)
            continue;

        // If the element is below or equal, continue
        glm::vec2 otherLocation = other->getWorldTransform().getPosition2();
        if(otherLocation.y >= elementLocation.y)
            continue;

        // If the element is farther away, continue
        glm::vec2 otherDirection = otherLocation- elementLocation;
        float otherDistance = glm::length(otherDirection);
        if(otherDistance > bestDistance)
            continue;

        // If the element is at a greater angle off of up vector, continue
        float otherAngle = glm::dot(glm::normalize(otherDirection), upVector);
        if(otherDistance == bestDistance && otherAngle < bestAngle)
            continue;

        // Update new current best
        bestDistance = otherDistance;
        bestAngle = otherAngle;
        bestEntity = other;
    }

    // Return best
    return bestEntity;
}

Entity* UIGrid::getElementBelow(Entity* element)
{
    updateBearing(UIGD_DOWN, element);

    glm::vec2 elementLocation = element->getWorldTransform().getPosition2();
    elementLocation.x = bearing;

    glm::vec2 downVector = glm::vec2(0.0f, 1.0f);

    float bestDistance = INT_MAX;
    float bestAngle = 0;
    Entity* bestEntity = nullptr;

    for(Entity* other : elements)
    {
        // If same element, continue
        if(element == other)
            continue;

        // If the element is above or equal, continue
        glm::vec2 otherLocation = other->getWorldTransform().getPosition2();
        if(otherLocation.y <= elementLocation.y)
            continue;

        // If the element is farther away, continue
        glm::vec2 otherDirection = otherLocation- elementLocation;
        float otherDistance = glm::length(otherDirection);
        if(otherDistance > bestDistance)
            continue;

        // If the element is at a greater angle off of down vector, continue
        float otherAngle = glm::dot(glm::normalize(otherDirection), downVector);
        if(otherDistance == bestDistance && otherAngle < bestAngle)
            continue;

        // Update new current best
        bestDistance = otherDistance;
        bestAngle = otherAngle;
        bestEntity = other;
    }

    // Return best
    return bestEntity;
}

Entity *UIGrid::getElementToLeft(Entity* element)
{
    updateBearing(UIGD_LEFT, element);

    glm::vec2 elementLocation = element->getWorldTransform().getPosition2();
    elementLocation.y = bearing;

    glm::vec2 leftVector = glm::vec2(-1.0f, 0.0f);

    float bestDistance = INT_MAX;
    float bestAngle = 0;
    Entity* bestEntity = nullptr;

    for(Entity* other : elements)
    {
        // If same element, continue
        if(element == other)
            continue;

        // If the element is to right or equal, continue
        glm::vec2 otherLocation = other->getWorldTransform().getPosition2();
        if(otherLocation.x >= elementLocation.x)
            continue;

        // If the element is farther away, continue
        glm::vec2 otherDirection = otherLocation- elementLocation;
        float otherDistance = glm::length(otherDirection);
        if(otherDistance > bestDistance)
            continue;

        // If the element is at a greater angle off of left vector, continue
        float otherAngle = glm::dot(glm::normalize(otherDirection), leftVector);
        if(otherDistance == bestDistance && otherAngle < bestAngle)
            continue;

        // Update new current best
        bestDistance = otherDistance;
        bestAngle = otherAngle;
        bestEntity = other;
    }

    // Return best
    return bestEntity;
}

Entity* UIGrid::getElementToRight(Entity* element)
{
    updateBearing(UIGD_RIGHT, element);

    glm::vec2 elementLocation = element->getWorldTransform().getPosition2();
    elementLocation.y = bearing;

    glm::vec2 rightVector = glm::vec2(1.0f, 0.0f);

    float bestDistance = INT_MAX;
    float bestAngle = 0;
    Entity* bestEntity = nullptr;

    for(Entity* other : elements)
    {
        // If same element, continue
        if(element == other)
            continue;

        // If the element is to left or equal, continue
        glm::vec2 otherLocation = other->getWorldTransform().getPosition2();
        if(otherLocation.x <= elementLocation.x)
            continue;

        // If the element is farther away, continue
        glm::vec2 otherDirection = otherLocation- elementLocation;
        float otherDistance = glm::length(otherDirection);
        if(otherDistance > bestDistance)
            continue;

        // If the element is at a greater angle off of right vector, continue
        float otherAngle = glm::dot(glm::normalize(otherDirection), rightVector);
        if(otherDistance == bestDistance && otherAngle < bestAngle)
            continue;

        // Update new current best
        bestDistance = otherDistance;
        bestAngle = otherAngle;
        bestEntity = other;
    }

    // Return best
    return bestEntity;
}

void UIGrid::updateBearing(UIGridDirection newDirection, Entity* element)
{
    // If the directions are not on the same axis
    if(prevDirection == UIGD_NONE || prevDirection % 2 != newDirection % 2)
    {
        if(newDirection == UIGD_LEFT || newDirection == UIGD_RIGHT)
            bearing = element->getWorldTransform().getPosition2().y;
        else if(newDirection == UIGD_UP || newDirection == UIGD_DOWN)
            bearing = element->getWorldTransform().getPosition2().x;
    }

    prevDirection = newDirection;
}