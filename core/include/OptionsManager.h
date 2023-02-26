//
// Created by Will on 12/12/2022.
//

#ifndef OPTIONS_MANAGER_H
#define OPTIONS_MANAGER_H

#include <glm/glm.hpp>
#include <vector>

#include "IOptionsReceiver.h"

class OptionsManager
{
    static OptionsManager* instance;
    std::vector<IOptionsReceiver*> receivers;

    glm::vec2 windowSize;
    glm::vec2 viewportResolution;

    // This is a singleton so the constructor is private
    OptionsManager();

public:
    static OptionsManager *getInstance();

    inline glm::vec2 getWindowSize() { return windowSize; };

    inline glm::vec2 getViewportResolution() { return viewportResolution; }; // TODO: This should live in the game, not the engine

    inline void updateResolution(glm::vec2 resolution) {
        glm::vec2 oldResolution = windowSize;

        this->viewportResolution = resolution;
        this->windowSize = resolution;

        for(auto* receiver : receivers)
            receiver->resolutionUpdated(oldResolution, resolution);
    }

    void registerReceiver(IOptionsReceiver* receiver) { receivers.push_back(receiver); };
    void deregisterReceiver(IOptionsReceiver* receiver);

};

#endif //OPTIONS_MANAGER_H
