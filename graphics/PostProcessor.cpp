//
// Created by Will on 8/6/2022.
//

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <iostream>

#include "PostProcessor.h"
#include "EventManager.h"
#include "OptionsManager.h"



PostProcessor::PostProcessor(Shader screenShader)
: screenShader(screenShader)
, msaaBuffer(Texture2DMS(4))
{
    // Hook up shader
    screenShader.use();
    screenShader.setInt("screenTexture", 0);

    // Create VAO for screen quad
    unsigned int quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glm::vec2 viewportRes = OptionsManager::getInstance()->getViewportResolution();
    generateBuffers(viewportRes.x, viewportRes.y);

    OptionsManager::getInstance()->registerReceiver(this);
}

void PostProcessor::generateBuffers(int width, int height)
{
    // Configure MSAA Framebuffer
    glGenFramebuffers(1, &msaaFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, msaaFBO);

    // Create MSAA Color Attachment
    msaaBuffer.generate(width, height, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, msaaBuffer.id, 0);

    // Create MSAA Renderbuffer
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    // Check for completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Configure Intermediate Framebuffer
    glGenFramebuffers(1, &interFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, interFBO);

    // Create Intermediate Color Attachment
    interBuffer.generate(width, height, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, interBuffer.id, 0);

    // Check for completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Intermediate framebuffer is not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::begin()
{
    // Bind to MSAA Framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, msaaFBO);
    glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

    // Clear the buffer
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcessor::end()
{
    glm::vec2 viewportRes = OptionsManager::getInstance()->getViewportResolution();

    static float deltaTime = 0.0f;
    static float lastFrame = 0.0f;

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Blit the MSAA Framebuffer to the Intermediate and down sample
    glBindFramebuffer(GL_READ_FRAMEBUFFER, msaaFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, interFBO);
    glBlitFramebuffer(0, 0, viewportRes.x, viewportRes.y, 0, 0, viewportRes.x, viewportRes.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // Bind to the default Framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);

    // Clear the buffer
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float offset = 1.0f / 300.0f;
    float offsets[9][2] = {
        { -offset,  offset  },  // top-left
        {  0.0f,    offset  },  // top-center
        {  offset,  offset  },  // top-right
        { -offset,  0.0f    },  // center-left
        {  0.0f,    0.0f    },  // center-center
        {  offset,  0.0f    },  // center - right
        { -offset, -offset  },  // bottom-left
        {  0.0f,   -offset  },  // bottom-center
        {  offset, -offset  }   // bottom-right
    };

    int edgeKernel[9] = {
            -1, -1, -1,
            -1,  8, -1,
            -1, -1, -1
    };

    float blurKernel[9] = {
            1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
            2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
            1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
    };

    // Draw the quad for the scene
    screenShader.use();

    screenShader.setFloat("time", (float) currentFrame);
    glUniform2fv(glGetUniformLocation(screenShader.id, "offsets"), 9, (float*) offsets);
    glUniform1iv(glGetUniformLocation(screenShader.id, "edge_kernel"), 9, edgeKernel);
    glUniform1fv(glGetUniformLocation(screenShader.id, "blur_kernel"), 9, blurKernel);

    if(shakeTime > 0.0f)
    {
        shakeTime -= deltaTime;
        screenShader.setBool("shake", true);
    }
    else
    {
        screenShader.setBool("shake", false);
    }

    screenShader.setBool("confuse", confuseOn);
    screenShader.setBool("chaos", chaosOn);

    glBindVertexArray(quadVAO);
    glActiveTexture(GL_TEXTURE0);
    interBuffer.bind();

    if(chaosOn) // Use GL_REPEAT during chaos so the play can still see the whole play field
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else // GL_MIRRORED_REPEAT looks nicest when shake is used
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    }

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void PostProcessor::eventCallback(Event event)
{
//    switch(event)
//    {
//        case SOLID_HIT:
//            shakeTime = 0.05f;
//            break;
//        case POWER_CONFUSE_START:
//            confuseOn = true;
//            break;
//        case POWER_CONFUSE_END:
//            confuseOn = false;
//            break;
//        case POWER_CHAOS_START:
//            chaosOn = true;
//            break;
//        case POWER_CHAOS_END:
//            chaosOn = false;
//            break;
//        default:
//            break;
//    }
}

void PostProcessor::resolutionUpdated(glm::vec2 oldRes, glm::vec2 newRes)
{
    generateBuffers(newRes.x, newRes.y);
}
