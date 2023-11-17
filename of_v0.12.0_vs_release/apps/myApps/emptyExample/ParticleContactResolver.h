#pragma once
#include "ParticleContact.h"
class ParticleContactResolver
{

public:
	unsigned int iteration;
	void resolveContacts(ParticleContact* contactArray, unsigned int numContacts, float duration);
};

