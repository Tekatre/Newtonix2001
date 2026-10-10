
#pragma once
#include "RigidBody.h"
#include "Matrix34.h"
class Primitive
{
public :
	RigidBody *body;
	Matrix34 offset;
	Matrix34 transform;
	// axes du repere local en coordonnees monde, calcules une seule fois a la construction
	// (getAxis est appele des dizaines de fois par test boite/boite)
	Vecteur3D axes[3];

	Primitive();
	Primitive(RigidBody *body);
	~Primitive();

	Vecteur3D getAxis(int index);
	
};

