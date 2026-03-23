//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 7/5/2023.
//

#include <algorithm>
#include "UIGrid.h"

#include "OptionsManager.h"

void UIGrid::registerElement(Entity* element)
{
    if (std::find(elements.begin(), elements.end(), element) != elements.end())
        return;

    elements.push_back(element);
}

void UIGrid::deregisterElement(Entity* element)
{
    remove(elements.begin(), elements.end(), element);
}

void UIGrid::deregisterAllElements()
{
    elements.clear();
}

Entity *UIGrid::getElementAbove(Entity* element)
{
    if(!element)
        return nullptr;

    return getElementAbove(element->getWorldTransform().getPosition2());
}

Entity *UIGrid::getElementAbove(glm::vec2 position)
{
    updateBearing(UIGD_UP, position);
    position.x = bearing;

    glm::vec2 upVector = glm::vec2(0.0f, -1.0f);

    float bestDistance = INT_MAX;
    float bestAngle = 0;
    Entity* bestEntity = nullptr;

    for(Entity* other : elements)
    {
        // If the element is below or equal, continue
        glm::vec2 otherPosition = other->getWorldTransform().getPosition2();
        if(otherPosition.y >= position.y)
            continue;

        // If the element is farther away, continue
        glm::vec2 otherDirection = otherPosition - position;
        float otherDistance = glm::length(otherDirection);
        float otherAngle = glm::dot(glm::normalize(otherDirection), upVector);

        if(priorityY == UIGD_PRIORITIZE_ALIGNMENT)
        {
            if(otherPosition.x != position.x)
                continue;

            if(otherDistance > bestDistance)
                continue;
        }
        else if(bestEntity && priorityY == UIGD_PRIORITIZE_AXIS)
        {
            glm::vec2 bestPosition = bestEntity->getWorldTransform().getPosition2();
            if (otherPosition.y < bestPosition.y)
                continue;

            if(otherPosition.y == bestPosition.y && otherDistance > bestDistance)
                continue;
        }
        else
        {
            if(otherDistance > bestDistance)
                continue;
        }

        if(otherDistance == bestDistance && otherAngle < bestAngle)
            continue;

        // Update new current best
        bestDistance = otherDistance;
        bestAngle = otherAngle;
        bestEntity = other;
    }

    if(position.y != OptionsManager::getInstance()->getViewportResolution().y && !bestEntity && wrapY)
        return getElementAbove(glm::vec2(position.x, OptionsManager::getInstance()->getViewportResolution().y));

    // Return best
    return bestEntity;
}

Entity *UIGrid::getElementBelow(Entity* element)
{
    if(!element)
        return nullptr;

    return getElementBelow(element->getWorldTransform().getPosition2());
}

Entity *UIGrid::getElementBelow(glm::vec2 position)
{
    updateBearing(UIGD_DOWN, position);
    position.x = bearing;

    glm::vec2 downVector = glm::vec2(0.0f, 1.0f);

    float bestDistance = INT_MAX;
    float bestAngle = 0;
    Entity* bestEntity = nullptr;

    for(Entity* other : elements)
    {
        // If the element is above or equal, continue
        glm::vec2 otherPosition = other->getWorldTransform().getPosition2();
        if(otherPosition.y <= position.y)
            continue;

        // If the element is farther away, continue
        glm::vec2 otherDirection = otherPosition - position;
        float otherDistance = glm::length(otherDirection);
        float otherAngle = glm::dot(glm::normalize(otherDirection), downVector);

        if(priorityY == UIGD_PRIORITIZE_ALIGNMENT)
        {
            if(otherPosition.x != position.x)
                continue;

            if(otherDistance > bestDistance)
                continue;
        }
        else if(bestEntity && priorityY == UIGD_PRIORITIZE_AXIS)
        {
            glm::vec2 bestPosition = bestEntity->getWorldTransform().getPosition2();
            if (otherPosition.y > bestPosition.y)
                continue;

            if(otherPosition.y > bestPosition.y == otherDistance > bestDistance)
                continue;
        }
        else
        {
            if(otherDistance > bestDistance)
                continue;
        }


        if(otherDistance == bestDistance && otherAngle < bestAngle)
            continue;

        // Update new current best
        bestDistance = otherDistance;
        bestAngle = otherAngle;
        bestEntity = other;
    }

    if(position.y != 0 && !bestEntity && wrapY)
        return getElementBelow(glm::vec2(position.x, 0));

    // Return best
    return bestEntity;
}

Entity *UIGrid::getElementToLeft(Entity* element)
{
    if(!element)
        return nullptr;

    return getElementToLeft(element->getWorldTransform().getPosition2());
}

Entity *UIGrid::getElementToLeft(glm::vec2 position)
{
    updateBearing(UIGD_LEFT, position);
    position.y = bearing;

    glm::vec2 leftVector = glm::vec2(-1.0f, 0.0f);

    float bestDistance = INT_MAX;
    float bestAngle = 0;
    Entity* bestEntity = nullptr;

    for(Entity* other : elements)
    {
        // If the element is to right or equal, continue
        glm::vec2 otherPosition = other->getWorldTransform().getPosition2();
        if(otherPosition.x >= position.x)
            continue;

        glm::vec2 otherDirection = otherPosition - position;
        float otherDistance = glm::length(otherDirection);
        float otherAngle = glm::dot(glm::normalize(otherDirection), leftVector);

        if(priorityX == UIGD_PRIORITIZE_ALIGNMENT)
        {
            if(otherPosition.y != position.y)
                continue;

            if(otherDistance > bestDistance)
                continue;
        }
        else if(bestEntity && priorityX == UIGD_PRIORITIZE_AXIS)
        {
            glm::vec2 bestPosition = bestEntity->getWorldTransform().getPosition2();
            if (otherPosition.x < bestPosition.x)
                continue;

            if(otherPosition.x == bestPosition.x && otherDistance > bestDistance)
                continue;
        }
        else
        {
            if(otherDistance > bestDistance)
                continue;
        }

        if(otherDistance == bestDistance && otherAngle < bestAngle)
            continue;

        // Update new current best
        bestDistance = otherDistance;
        bestAngle = otherAngle;
        bestEntity = other;
    }

//    if(priorityX == UIGD_PRIORITIZE_AXIS)
//    {
//        UIGridPriority origPriority = priorityX;
//        priorityX = UIGD_PRIORITIZE_BEARING;
//        if(bestEntity != getElementToLeft(position))
//            clearBearing();
//        priorityX = origPriority;
//    }

    if(position.x != OptionsManager::getInstance()->getViewportResolution().x && !bestEntity && wrapX)
        return getElementToLeft(glm::vec2(OptionsManager::getInstance()->getViewportResolution().x, position.y));

    // Return best
    return bestEntity;
}

Entity* UIGrid::getElementToRight(Entity* element)
{
    if(!element)
        return nullptr;

    return getElementToRight(element->getWorldTransform().getPosition2());
}

Entity *UIGrid::getElementToRight(glm::vec2 position)
{
    updateBearing(UIGD_RIGHT, position);
    position.y = bearing;

    glm::vec2 rightVector = glm::vec2(1.0f, 0.0f);

    float bestDistance = INT_MAX;
    float bestAngle = 0;
    Entity* bestEntity = nullptr;

    for(Entity* other : elements)
    {
        // If the element is to left or equal, continue
        glm::vec2 otherPosition = other->getWorldTransform().getPosition2();
        if(otherPosition.x <= position.x)
            continue;

        glm::vec2 otherDirection = otherPosition - position;
        float otherDistance = glm::length(otherDirection);
        float otherAngle = glm::dot(glm::normalize(otherDirection), rightVector);

        if(priorityX == UIGD_PRIORITIZE_ALIGNMENT)
        {
            if(otherPosition.y != position.y)
                continue;

            if(otherDistance > bestDistance)
                continue;
        }
        else if(bestEntity && priorityX == UIGD_PRIORITIZE_AXIS)
        {
            glm::vec2 bestPosition = bestEntity->getWorldTransform().getPosition2();
            if (otherPosition.x > bestPosition.x)
                continue;

            if(otherPosition.x == bestPosition.x && otherDistance > bestDistance)
                continue;
        }
        else
        {
            if(otherDistance > bestDistance)
                continue;
        }

        if(otherDistance == bestDistance && otherAngle < bestAngle)
            continue;

        // Update new current best
        bestDistance = otherDistance;
        bestAngle = otherAngle;
        bestEntity = other;
    }

    if(position.x != 0 && !bestEntity && wrapX)
        return getElementToRight(glm::vec2(0, position.y));

    // Return best
    return bestEntity;
}

void UIGrid::clearBearing()
{
    prevDirection = UIGD_NONE;
}

void UIGrid::updateBearing(UIGridDirection newDirection, glm::vec2 position)
{
    // If the directions are not on the same axis
    if(prevDirection == UIGD_NONE || prevDirection % 2 != newDirection % 2)
    {
        if(newDirection == UIGD_LEFT || newDirection == UIGD_RIGHT)
            bearing = position.y;
        else if(newDirection == UIGD_UP || newDirection == UIGD_DOWN)
            bearing = position.x;
    }

    prevDirection = newDirection;
}