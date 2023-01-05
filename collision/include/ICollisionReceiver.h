//
// Created by Will on 7/12/2022.
//

#ifndef ICOLLISION_RECEIVER_H
#define ICOLLISION_RECEIVER_H

class ICollisionReceiver
{
public:
    std::string collisionTag;

    virtual void collisionCallback(ICollisionReceiver* collisionReceiver, glm::vec3 overlap) {};
};

#endif //ICOLLISION_RECEIVER_H
