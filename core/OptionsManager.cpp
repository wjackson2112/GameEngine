//
// Created by Will on 12/12/2022.
//

#include "OptionsManager.h"

#include "Globals.h"
#ifdef __EMSCRIPTEN__
#include "emscripten/html5.h"
#endif
#include "glfw-3.3.2/include/GLFW/glfw3.h"

OptionsManager *OptionsManager::instance = nullptr;

OptionsManager::OptionsManager()
{
#ifdef __EMSCRIPTEN__
    int width = EM_ASM_INT({
        return window.innerWidth;
    });
    int height = EM_ASM_INT({
        return window.innerHeight;
    });

    emscripten_set_canvas_element_size("#canvas", width, height);

    windowSize = { width, height };
    viewportResolution = { width, height };
#else
    windowSize = { 1600.f, 1200.f };
    viewportResolution = { 1600.f, 1200.f };
#endif
}

OptionsManager *OptionsManager::getInstance()
{
    if(!instance)
        instance = new OptionsManager();
    return instance;
}

void OptionsManager::deregisterReceiver(IOptionsReceiver *receiver)
{
    for(auto it = receivers.begin(); it != receivers.end(); it++)
    {
        if (*it == receiver) {
            receivers.erase(it);
            break;
        }
    }
}