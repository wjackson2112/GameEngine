//
// Created by Will on 12/8/2022.
//

#include "MenuButton.h"

#include <iostream>

#include "AssetManager.h"
#include "SpriteComponent2D.h"
#include "TextComponent.h"

#include "InputManager.h"
#include "EventManager.h"

MenuButton::MenuButton(glm::vec2 origin, glm::vec2 size, std::string background, std::string text, Event event)
: size(size)
, event(event)
{
    transform.translate(origin);

    Shader spriteShader = AssetManager::getInstance()->loadShader("shaders/sprite.vert",
                                                                  "shaders/sprite.frag",
                                                                  nullptr,
                                                                  "block");
    Texture2D texture = AssetManager::getInstance()->loadTexture(background.c_str(), false, background);
    addComponent<SpriteComponent2D>(new SpriteComponent2D(spriteShader, texture, size));

    Shader textShader = AssetManager::getInstance()->loadShader("shaders/text.vert",
                                                                "shaders/text.frag",
                                                                nullptr,
                                                                text);
    TextFont textFont = AssetManager::getInstance()->loadTextFont("assets/arial.ttf",
                                                                  "arial48", 48);
    auto textComponent = new TextComponent(textShader, textFont, text);
    addComponent<TextComponent>(textComponent);

    float offsetPad = (size.y - textComponent->getMaxBearingY()) / 2;
    textComponent->setColor(glm::vec3(.5f, .75f, .5f));
    textComponent->setTransform(glm::vec3(offsetPad, offsetPad, 0.1f));

    InputConfig config = InputConfig();
    config.mouseButtons.push_back(MOUSE_BUTTON_1);
    InputManager::getInstance()->registerReceiver(this, config);
}

MenuButton::~MenuButton()
{
    InputManager::getInstance()->deregisterReceiver(this);
}

void MenuButton::mouseInputCallback(double xpos, double ypos, MouseButton button, Action action, Modifier mods)
{
    glm::vec2 origin = getWorldTransform().getPosition2();
    if(button == MOUSE_BUTTON_LEFT && action == ACTION_RELEASE &&
       xpos >= origin.x && xpos <= origin.x + size.x &&
       ypos >= origin.y && ypos <= origin.y + size.y)
    {
        EventManager::getInstance()->broadcastEvent(event);
    }
}
