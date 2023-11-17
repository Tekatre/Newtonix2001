#include "ParticleGravity.h"

void ParticleGravity::updateForce(Particule* p, float dt)
{
	gravity = Vecteur3D(0, -9.81, 0);
	p->addAcceleration(gravity);
}

void ParticleGravity::setGravity(Vecteur3D g)
{
	gravity = g;
}

