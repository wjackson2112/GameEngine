//
// Created by Will on 6/10/2022.
//

#ifndef SPRITE_COMPONENT_2D_H
#define SPRITE_COMPONENT_2D_H

#include "Component.h"
#include "Shader.h"
#include "Texture2D.h"

class SpriteComponent2D : public Component
{
protected:
    Shader shader;
    Texture2D texture;
    unsigned int quadVAO;
    glm::vec2 size;

    int blendFunc;

public:
    glm::vec4 color;

    SpriteComponent2D(Shader shader, Texture2D texture, glm::vec2 size);
    ~SpriteComponent2D();

    void draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightDir, glm::vec3 viewPos) override;

    inline glm::vec3 getColor3() { return glm::vec3(color); };
    void setColor3(glm::vec3 color);

    inline glm::vec4 getColor4() { return color; };
    void setColor4(glm::vec4 color);

    inline glm::vec2 getSize() { return size; };
    void setSize(glm::vec2 size);
    void scaleToWidth(float width);
    void scaleToHeight(float height);

    void setTexture(Texture2D texture);

    inline const void setBlendFunc(int in_blendFunc) { blendFunc = in_blendFunc; };

private:
    void InitRenderData();
};

#endif //SPRITE_COMPONENT_2D_H
