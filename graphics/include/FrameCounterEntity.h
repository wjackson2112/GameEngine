//
// Created by Will on 6/2/2024.
//

#ifndef FRAME_COUNTER_ENTITY_H
#define FRAME_COUNTER_ENTITY_H

#include "Entity.h"

class FrameCounterEntity : public Entity
{
public:
    FrameCounterEntity();
    void update(float deltaTime);
};

#endif //FRAME_COUNTER_ENTITY_H
