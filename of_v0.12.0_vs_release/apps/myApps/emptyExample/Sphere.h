#pragma once
#include "Primitive.h"
#include "SphereRigidBody.h"
class Sphere : public Primitive
{
public :
	float radius;

	Vecteur3D getAxis(int index) override;
	Sphere(RigidBody *body);

};

