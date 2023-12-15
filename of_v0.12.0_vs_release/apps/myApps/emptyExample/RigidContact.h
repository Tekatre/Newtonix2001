#pragma once
#include "RigidBody.h"
class RigidContact
{
	public:
	RigidBody* body[2];
	Vecteur3D worldContactPoint;
	Vecteur3D contactNormal;
	float penetration;
	float restitution;
	float friction;

	bool InterpenetrationResolved = false;


	RigidContact();
	~RigidContact();

	void resolve(float duration);
	void resolveInterpenetration(float duration);

};

