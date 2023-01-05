//
// Created by Will on 12/1/2022.
//

#ifndef SCENE_STACK_H
#define SCENE_STACK_H

#include <vector>
#include <memory>

#include "Scene.h"

class SceneStack
{
    struct SceneStackEntry
    {
        Scene* scene;
        bool updatesFromBackground;
        bool hasTransparency;

        explicit SceneStackEntry(Scene* scene)
        : scene(scene)
        , updatesFromBackground(false)
        , hasTransparency(false)
        {};

        SceneStackEntry(Scene* scene, bool updatesFromBackground, bool hasTransparency)
        : scene(scene)
        , updatesFromBackground(updatesFromBackground)
        , hasTransparency(hasTransparency)
        {};
    };

    std::vector<SceneStackEntry> sceneEntries;

public:
    void pushScene(Scene* scene, bool updatesFromBackground = false, bool hasTransparency = false);
    Scene* peekScene();
    Scene* popScene();
    void clearScenes();

    void draw();
    void update();
    void resolveCollisions();
};

#endif //SCENE_STACK_H
