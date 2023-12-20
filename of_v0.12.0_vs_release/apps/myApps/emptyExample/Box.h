#pragma once
#include "Primitive.h"
#include "BoxRigidBody.h"
class Box : public Primitive
{
public:
	Vecteur3D halfSize;
	Vecteur3D vertices[8] = 	{ Vecteur3D(-halfSize.getX(), -halfSize.getY(), -halfSize.getZ()),
			Vecteur3D(-halfSize.getX(), -halfSize.getY(), halfSize.getZ()),
			Vecteur3D(-halfSize.getX(), halfSize.getY(), -halfSize.getZ()),
			Vecteur3D(-halfSize.getX(), halfSize.getY(), halfSize.getZ()),
			Vecteur3D(halfSize.getX(), -halfSize.getY(), -halfSize.getZ()),
			Vecteur3D(halfSize.getX(), -halfSize.getY(), halfSize.getZ()),
			Vecteur3D(halfSize.getX(), halfSize.getY(), -halfSize.getZ()),
			Vecteur3D(halfSize.getX(), halfSize.getY(), halfSize.getZ())
		};
	Box(Vecteur3D halfsize);
	Box(RigidBody *body);
	Vecteur3D getAxis(int index) override;
	


};

