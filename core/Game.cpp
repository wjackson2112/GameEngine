//
// Created by Will on 6/7/2022.
//
#include "Game.h"

#include <GLFW/glfw3.h>

Game::Game(Scene* scene)
{
    sceneStack = SceneStack();
    this->sceneStack.pushScene(scene);
}

Game::~Game()
{
    glfwTerminate();
}

void Game::draw()
{
    sceneStack.draw();
}

void Game::update()
{
    sceneStack.update();
}

void Game::resolveCollisions()
{
    sceneStack.resolveCollisions();
}