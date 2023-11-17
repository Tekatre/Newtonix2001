#pragma once
#include "RigidBody.h"
#include "ForceGenerator.h"
#include <vector>
class RigidForceRegistry
{
public:
	struct RigidForceRegistration
	{
		RigidBody* rigidBody;
		ForceGenerator* fg;
		int type;
		Vecteur3D applicationPoint;
		
	};

	using Registry = std::vector<RigidForceRegistration>;
	Registry my_RigidRegistry;

	RigidForceRegistry();
	void updateForces(float duration);
};


