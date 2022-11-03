//
// Created by Will on 6/9/2022.
//
#include "CameraComponentBase.h"

Transform CameraComponentBase::getWorldTransform()
{
    return parent->getWorldTransform().compose(transform);
}