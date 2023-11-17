#pragma once
#include "ForceGenerator.h"

class AnchorForceGenerator : public ForceGenerator
{
private:
	Vecteur3D anchor;
	float k;
	float lzero;
public:
	AnchorForceGenerator(Vecteur3D anchor, float k, float lzero);
	void updateForce(RigidBody* rigidBody, Vecteur3D applicationPoint, int type);
};

