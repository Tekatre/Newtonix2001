#pragma once

#include "RigidBody.h"

class ForceGenerator
{
public :
	virtual void updateForce(RigidBody* rigidBody, int type, Vecteur3D point) = 0 ;
};

