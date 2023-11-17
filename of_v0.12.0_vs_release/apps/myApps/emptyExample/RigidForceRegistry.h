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
		int type = 0; // 0 center, 1 world, 2 local
		Vecteur3D applicationPoint = Vecteur3D(0,0,0);
	};

	using Registry = std::vector<RigidForceRegistration>;
	Registry my_RigidRegistry;

	RigidForceRegistry();
	void updateForces(float duration);
};

