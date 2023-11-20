#pragma once

#include "RigidBody.h"

class ForceGenerator
{
public :
	virtual void updateForce(RigidBody* rigidBody) = 0 ;
	virtual Vecteur3D getBodyAnchor() = 0;
};

