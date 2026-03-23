//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 2/25/2023.
//

#ifndef I_OPTIONS_RECEIVER_H
#define I_OPTIONS_RECEIVER_H

#include <glm/glm.hpp>

class IOptionsReceiver
{
public:
    virtual void resolutionUpdated(glm::vec2 oldRes, glm::vec2 newRes) {};
};

#endif //I_OPTIONS_RECEIVER_H
