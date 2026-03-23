//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 7/21/2022.
//

#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <vector>
#include <glm/glm.hpp>
#include <algorithm>

#include "Particle.h"
#include "Component.h"

class Particle; // Forward declare for static assert

template <class P>
class ParticleEmitter : public Component
{
    std::vector<P*> particles;
    int numParticles;
    Transform centerTransform;

public:
    ParticleEmitter(Entity* parent, int numParticles, Transform centerTransform)
    : numParticles(numParticles)
    , centerTransform(centerTransform)
    {
        this->parent = parent;
        this->receivesUpdates = true;
    }

    void update(float deltaTime) override
    {
        Transform worldCenterTransform = getWorldTransform().compose(centerTransform);

        if(particles.size() < numParticles) {
            int numNewParticles = 2; // TODO: Make this configurable
            for (int i = 0; i < numNewParticles; i++) {
                static_assert(std::is_base_of<Particle, P>::value, "P not derived from Particle");
                particles.emplace_back(new P(parent, worldCenterTransform.getPosition()));
            }
        }

        auto it = particles.begin();
        while(it != particles.end())
        {
            P* particle = *(it++);
            if(!particle->isAlive())
            {
                particle->shouldBeDestroyed = true;
                particles.erase(std::remove(particles.begin(), particles.end(), particle), particles.end());
                particles.emplace_back(new P(parent, worldCenterTransform.getPosition()));
            }
        }
    }
};

#endif //PARTICLE_EMITTER_H
