#include "RigidForceRegistry.h"

RigidForceRegistry::RigidForceRegistry()
{
}


void RigidForceRegistry::updateForces(float duration)
{
	for (auto& it : my_RigidRegistry)
	{
		it.fg->updateForce(it.rigidBody, it.applicationPoint, it.type);
		//it.fg->updateForce(it.rigidBody, Vecteur3D(0,0,0), 0);
	}
}