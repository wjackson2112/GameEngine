//
// Created by Will on 12/1/2022.
//

#include "SceneStack.h"

void SceneStack::pushScene(Scene* scene, bool updatesFromBackground /*= false*/, bool hasTransparency /*= false*/)
{
     sceneEntries.emplace_back(SceneStack::SceneStackEntry(scene, updatesFromBackground, hasTransparency));
}

Scene* SceneStack::peekScene()
{
    return sceneEntries.back().scene;
}

Scene* SceneStack::popScene()
{
    Scene* scene = sceneEntries.back().scene;
    sceneEntries.pop_back();
    return scene;
}

void SceneStack::clearScenes()
{
    for(auto it = sceneEntries.begin(); it != sceneEntries.end(); ++it)
    {
        delete it->scene;
    }

    sceneEntries.clear();
}

void SceneStack::draw()
{
    for(uint8_t i = sceneEntries.size()-1; i >= 0; i--)
    {
        sceneEntries[i].scene->draw();
        if(!sceneEntries[i].hasTransparency)
            break;
    }
}

void SceneStack::update()
{
    for(auto it = sceneEntries.begin(); it != sceneEntries.end(); ++it)
    {
        if(std::next(it) == sceneEntries.end() || it->updatesFromBackground)
            it->scene->update();
    }
}

void SceneStack::resolveCollisions()
{
    for(auto it = sceneEntries.begin(); it != sceneEntries.end(); ++it)
    {
        if(std::next(it) == sceneEntries.end() || it->updatesFromBackground)
            it->scene->resolveCollisions();
    }
}