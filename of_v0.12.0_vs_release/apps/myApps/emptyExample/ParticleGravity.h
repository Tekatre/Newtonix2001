#pragma once
#include "ParticleForceGenerator.h"



class ParticleGravity : public ParticleForceGenerator
{
public:
	Vecteur3D gravity = Vecteur3D(0, -9.81, 0);
public:
	void updateForce(Particule* p, float dt);
	void setGravity(Vecteur3D g);
};

