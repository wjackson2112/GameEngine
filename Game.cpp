//
// Created by Will on 6/7/2022.
//
#include "Game.h"

#include <GLFW/glfw3.h>

Game::Game(Scene* scene)
{
    this->scene = scene;
}

Game::~Game()
{
    glfwTerminate();
}

void Game::draw()
{
    scene->draw();
}

void Game::update()
{
    scene->update();
}

void Game::resolveCollisions()
{
    scene->resolveCollisions();
}