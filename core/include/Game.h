//
// Created by Will on 6/7/2022.
//

#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "SceneStack.h"

//enum GameState {
//    GAME_ACTIVE,
//    GAME_MENU,
//    GAME_WIN
//};

class Game
{
public:
//    GameState   state;
    SceneStack      sceneStack;

    Game(Scene* scene);
    ~Game();

    void draw();
    virtual void update();
    void resolveCollisions();
};

#endif //GAME_H
