#pragma once
#include "RigidBody.h"
using namespace std;
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
	bool VelocityResolved = false;


	RigidContact();
	~RigidContact();

	void resolveInterpenetration(float duration);
	void resolveVelocity(float duration);
	float calculateSeparatingVelocity();

};

