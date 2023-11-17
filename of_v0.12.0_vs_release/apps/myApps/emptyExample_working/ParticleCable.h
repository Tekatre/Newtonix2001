#pragma once
#include "ParticleContact.h"
#include "ParticleLink.h"
#include <vector>
class ParticleCable : public ParticleLink
{
public:

	float maxLength;
	float restitution;
	unsigned int addContact(ParticleContact* contact, unsigned int limit);
	

};

