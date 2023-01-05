//
// Created by Will on 8/6/2022.
//

#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include "Shader.h"
#include "Texture2D.h"
#include "Texture2DMS.h"
#include "IEventReceiver.h"

class PostProcessor : public IEventReceiver
{
    Shader screenShader;

    unsigned int msaaFBO = 0;
    Texture2DMS msaaBuffer;

    unsigned int interFBO = 0;
    Texture2D interBuffer;

    unsigned int quadVAO = 0;

    float shakeTime = 0.0f;

    bool confuseOn = false;
    bool chaosOn = false;

    float quadVertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
            1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
            1.0f, -1.0f,  1.0f, 0.0f,
            1.0f,  1.0f,  1.0f, 1.0f
    };

public:
    explicit PostProcessor(Shader screenShader);

    void begin();
    void end();

    void eventCallback(Event event) override;
};

#endif //POSTPROCESSOR_H
