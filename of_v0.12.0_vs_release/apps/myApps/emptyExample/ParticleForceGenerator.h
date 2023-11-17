#pragma once
#include "Particule.h"



class ParticleForceGenerator
{
public:
	ParticleForceGenerator();
	~ParticleForceGenerator();
	virtual void updateForce(Particule* p, float dt) = 0;
};
