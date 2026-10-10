#pragma once

#include "ForceGenerator.h"	

class GravityGenerator : public ForceGenerator
{
private :
	Vecteur3D gravity = Vecteur3D(0,-9.81,0);

public :
	GravityGenerator() {}
	GravityGenerator(Vecteur3D gravity) : gravity(gravity) {}
	void updateForce(RigidBody* rigidBody) override;
	Vecteur3D getBodyAnchor();
};

