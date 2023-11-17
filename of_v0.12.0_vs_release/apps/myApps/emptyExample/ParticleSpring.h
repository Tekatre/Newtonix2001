#pragma once
#include "ParticleForceGenerator.h"

class ParticleSpring : public ParticleForceGenerator
{
private:
	Particule* other;
	float k;
	float lzero;
public:
	ParticleSpring(Particule* p, float k, float lzero);
	void updateForce(Particule* p, float dt);
	//Particule getOther();
	//void setOther(Particule* p);
};

