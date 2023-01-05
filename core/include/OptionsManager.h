//
// Created by Will on 12/12/2022.
//

#ifndef OPTIONS_MANAGER_H
#define OPTIONS_MANAGER_H

#include <glm/glm.hpp>

class OptionsManager
{
    static OptionsManager* instance;

    glm::vec2 screenResolution;
    glm::vec2 viewportResolution;

    // This is a singleton so the constructor is private
    OptionsManager();

public:
    static OptionsManager *getInstance();

    inline glm::vec2 getScreenResolution() { return screenResolution; };
    inline glm::vec2 getViewportResolution() { return viewportResolution; }; // TODO: This should live in the game, not the engine
};

#endif //OPTIONS_MANAGER_H
