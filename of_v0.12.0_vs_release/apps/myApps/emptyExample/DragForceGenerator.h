#pragma once
#include "ForceGenerator.h"
class DragForceGenerator : public ForceGenerator
{
private:
	float k1 = 0.05;
	float k2 = 0.001;
public:
	void updateForce(RigidBody* rigidBody, int type, Vecteur3D point);
};

