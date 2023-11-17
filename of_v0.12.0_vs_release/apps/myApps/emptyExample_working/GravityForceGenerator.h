#pragma once

#include "ForceGenerator.h"	

class GravityGenerator : public ForceGenerator
{
private :
	Vecteur3D gravity;

public :
	void updateForce(RigidBody* rigidBdy) override;
};

