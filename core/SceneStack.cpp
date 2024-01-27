//
// Created by Will on 12/1/2022.
//

#include "SceneStack.h"

void SceneStack::pushScene(Scene* scene)
{
    sceneEntries.emplace_back(scene);
}

void SceneStack::pushScene(SceneSettings settings, Scene* scene)
{
    sceneEntries.emplace_back(settings, scene);
}

Scene* SceneStack::peekScene()
{
    return sceneEntries.back().scene.get();
}

std::unique_ptr<Scene> SceneStack::popScene()
{
    std::unique_ptr<Scene> scene = std::move(sceneEntries.back().scene);
    sceneEntries.pop_back();
    return scene;
}

void SceneStack::clearScenes()
{
    sceneEntries.clear();
}

void SceneStack::draw()
{
    for(uint8_t i = sceneEntries.size()-1; i >= 0; i--)
    {
        sceneEntries[i].scene->draw();
        if(!sceneEntries[i].settings.hasTransparency)
            break;
    }
}

void SceneStack::update()
{
    for(auto it = sceneEntries.begin(); it != sceneEntries.end(); ++it)
    {
        if(std::next(it) == sceneEntries.end() || it->settings.updatesFromBackground)
            it->scene->update();
    }
}

void SceneStack::resolveCollisions()
{
    for(auto it = sceneEntries.begin(); it != sceneEntries.end(); ++it)
    {
        if(std::next(it) == sceneEntries.end() || it->settings.updatesFromBackground)
            it->scene->resolveCollisions();
    }
}