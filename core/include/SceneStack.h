//
// Created by Will on 12/1/2022.
//

#ifndef SCENE_STACK_H
#define SCENE_STACK_H

#include <vector>
#include <memory>

#include "Scene.h"

struct SceneSettings
{
    bool updatesFromBackground = false;
    bool hasTransparency = false;

    SceneSettings()
    : updatesFromBackground(false)
    , hasTransparency(false)
    {};

    SceneSettings(bool updatesFromBackground, bool hasTransparency)
    : updatesFromBackground(updatesFromBackground)
    , hasTransparency(hasTransparency)
    {};
};

class SceneStack
{
    struct SceneStackEntry
    {
        std::unique_ptr<Scene> scene;
        SceneSettings settings;

        explicit SceneStackEntry(Scene* scene)
        : settings(SceneSettings())
        {
            this->scene = std::unique_ptr<Scene>(scene);
        }

        explicit SceneStackEntry(SceneSettings settings, Scene* scene)
        : settings(settings)
        {
            this->scene = std::unique_ptr<Scene>(scene);
        }
    };

    std::vector<SceneStackEntry> sceneEntries;

public:
    void pushScene(Scene* scene);
    void pushScene(SceneSettings settings, Scene* scene);

    template<class T, typename... Args>
    T* pushScene(SceneSettings settings, Args... args)
    {
        T* scene = new T(args...);
        sceneEntries.emplace_back(SceneStackEntry(settings, scene));
        return scene;
    }

    Scene* peekScene();
    std::unique_ptr<Scene> popScene();
    void clearScenes();

    void draw();
    void update();
    void resolveCollisions();
};

#endif //SCENE_STACK_H
