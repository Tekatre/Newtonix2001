#pragma once
#include "RigidBody.h"
#include "ForceGenerator.h"
#include <vector>
class RigidForceRegistry
{
public :
	struct RigidForceRegistration
	{
		RigidBody* rigidBody;
		ForceGenerator* fg;
	};

	using Registry = std::vector<RigidForceRegistration>;
	Registry my_RigidRegistry;

	RigidForceRegistry();
	void updateForces(float duration);
};

