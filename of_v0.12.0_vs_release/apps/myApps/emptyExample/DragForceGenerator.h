#pragma once
#include "ForceGenerator.h"
class DragForceGenerator : public ForceGenerator
{
private:
	float k1 = 0.01;
	float k2 = 0.0005;
public:
	void updateForce(RigidBody* rigidBody);
	Vecteur3D getBodyAnchor();
};

