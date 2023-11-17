#include "RigidForceRegistry.h"

RigidForceRegistry::RigidForceRegistry()
{
}


void RigidForceRegistry::updateForces(float duration)
{
	for (auto& it : my_RigidRegistry)
	{
		it.fg->updateForce(it.rigidBody, it.type, it.applicationPoint);
	}
}