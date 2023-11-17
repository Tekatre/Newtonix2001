#pragma once
#include "ParticleForceGenerator.h"

class ParticleAnchorSpring : public ParticleForceGenerator
{
private:
	Vecteur3D anchor;
	float k;
	float lzero;
public:
	ParticleAnchorSpring(Vecteur3D anchor, float k, float lzero);
	void updateForce(Particule* p, float dt);
};

