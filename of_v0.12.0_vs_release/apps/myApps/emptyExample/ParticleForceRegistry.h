#pragma once
#include "Particule.h"
#include "ParticleForceGenerator.h"
#include <vector>


class ParticleForceRegistry
{
public:
	struct ParticleForceRegistration
	{
		Particule* particule;
		ParticleForceGenerator* fg;
	};

	using Registry = std::vector<ParticleForceRegistration>;
	Registry my_registry;

public:
	ParticleForceRegistry();
	void updateForces(float duration);
};



