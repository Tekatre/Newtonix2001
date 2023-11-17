#pragma once
#include "ParticleForceGenerator.h"

class ParticleDrag : public ParticleForceGenerator
{
private:
	float k1 = 0.05;
	float k2 = 0.001;
public:
	void updateForce(Particule* p, float dt);
};

