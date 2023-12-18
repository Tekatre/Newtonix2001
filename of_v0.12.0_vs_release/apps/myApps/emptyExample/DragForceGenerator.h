#pragma once
#include "ForceGenerator.h"
class DragForceGenerator : public ForceGenerator
{
private:
	float k1 = 0.1;
	float k2 = 0.5;
public:
	void updateForce(RigidBody* rigidBody);
	Vecteur3D getBodyAnchor();
};

