//
// Created by Will on 6/2/2024.
//

#include "FrameCounterEntity.h"
#include "AssetManager.h"
#include "TextComponent.h"

FrameCounterEntity::FrameCounterEntity()
{
    std::string text = "0.0";
    Shader textShader = AssetManager::getInstance()->loadShader("shaders/text.vert",
                                                                "shaders/text.frag",
                                                                nullptr,
                                                                text);
    TextFont textFont = AssetManager::getInstance()->loadTextFont("assets/arial.ttf",
                                                                  "arial48", 48);
    auto* textComponent = new TextComponent(textShader, textFont, text);

    textComponent->setColor(glm::vec3(1.0f, .0f, .0f));
    textComponent->setTransform(glm::vec3(0.f, 0.f, 0.2f));
    addComponent(textComponent);

    receivesUpdates = true;
}

void FrameCounterEntity::update(float deltaTime)
{
    std::string numFrames = std::to_string((int) (1/deltaTime));
    getComponent<TextComponent>()->setText(numFrames);
}