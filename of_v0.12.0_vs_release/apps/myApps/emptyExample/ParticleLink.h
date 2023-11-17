#pragma once
#include "ParticleContactGenerator.h"
#include "Particule.h"
class ParticleLink : public ParticleContactGenerator
{
public:
	Particule* particle[2];
	float currentLength() const;
	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;

};


