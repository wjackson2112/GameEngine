//
// Created by Will on 7/22/2022.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>

#include "Entity.h"
#include "ParticleEmitter.h"

#include "Shader.h"
#include "Texture2D.h"
#include "EntityManager.h"

class Particle : public Entity
{
protected:
    float life = 0.0f;

public:
    Particle(Entity* emitter, glm::vec3 emitPosition) {
        // TODO: Maybe all entities should do this?
        Scene* owningScene = EntityManager::getInstance()->getSceneForEntity(emitter);
        EntityManager::getInstance()->registerEntity(owningScene, this);
    };

    inline const bool isAlive() { return life > 0.0f; }
};

#endif //PARTICLE_H
