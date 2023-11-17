#pragma once
#include "ParticleContact.h"
#include "ParticleLink.h"
#include <vector>
class ParticleRod : public ParticleLink
{
public:
	float length;
	unsigned int addContact(ParticleContact* contact, unsigned int limit);


};