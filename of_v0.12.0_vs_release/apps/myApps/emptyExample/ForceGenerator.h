#pragma once

#include "RigidBody.h"
#include "../RigidForceRegistry.h"

class ForceGenerator
{
public :
	virtual void updateForce(RigidBody* rigidBody, Vecteur3D applicationPoint, int type) = 0 ;
	//virtual void updateForce(RigidBody* rigidBody) = 0;
};

