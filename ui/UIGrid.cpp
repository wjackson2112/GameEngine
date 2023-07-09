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
    glm::vec2 elementLocation = element->getWorldTransform().getPosition2();
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
    glm::vec2 elementLocation = element->getWorldTransform().getPosition2();
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
    glm::vec2 elementLocation = element->getWorldTransform().getPosition2();
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
    glm::vec2 elementLocation = element->getWorldTransform().getPosition2();
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