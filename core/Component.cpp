//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 12/14/2022.
//
#include "Component.h"
#include "Entity.h"

void Component::setParent(Entity *in_parent)
{
    this->parent = in_parent;
}

void Component::setTransform(Transform transform)
{
    this->transform = transform;
}

Transform Component::getWorldTransform()
{
    if(parent)
        return parent->getWorldTransform().compose(transform);
    else
        return transform;
}