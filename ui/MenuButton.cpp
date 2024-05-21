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
, boundEvent(event)
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
}

void MenuButton::eventCallback(Event event) {
    if(event != Event::EVT_RELEASE)
        return;

    glm::vec2 cursorPos = InputManager::getCursorPosition();

    glm::vec2 origin = getWorldTransform().getPosition2();
    if(cursorPos.x >= origin.x && cursorPos.x <= origin.x + size.x &&
       cursorPos.y >= origin.y && cursorPos.y <= origin.y + size.y)
    {
        EventManager::getInstance()->broadcastEvent(boundEvent);
    }
}
