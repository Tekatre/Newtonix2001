
#pragma once
#include "RigidBody.h"
#include "Matrix34.h"
class Primitive
{
public :
	RigidBody *body;
	Matrix34 offset;
	Matrix34 transform;

	Primitive();
	Primitive(RigidBody *body);
	~Primitive();

	Vecteur3D getAxis(int index);
	
};

