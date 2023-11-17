#pragma once

#include "Vecteur3D.h"
#include "Particule.h"
#include "ParticleForceRegistry.h"
#include "RigidBody.h"

class Integrateur
{
public:
	Integrateur();
	~Integrateur();
	void integrer(Particule* p, double time);
	void integrer(RigidBody* r, double time);
	double t;
};

