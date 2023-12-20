#pragma once
#include "Primitive.h"
#include "SphereRigidBody.h"
class Sphere : public Primitive
{
public :
	float radius;

	Sphere(RigidBody *body);

};

