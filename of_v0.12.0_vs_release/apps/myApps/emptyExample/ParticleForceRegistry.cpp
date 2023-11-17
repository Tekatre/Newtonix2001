#include "ParticleForceRegistry.h"


ParticleForceRegistry::ParticleForceRegistry()
{
}

void ParticleForceRegistry::updateForces(float duration)
{
    for (size_t i = 0; i < my_registry.size(); i++) {
        my_registry[i].particule->setAcceleration(Vecteur3D(0, 0, 0));
    }
    for (size_t i = 0; i < my_registry.size(); i++) {
        my_registry[i].fg->updateForce(my_registry[i].particule, duration);
    }
}


