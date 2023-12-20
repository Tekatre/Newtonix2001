#include "Box.h"

Box::Box(Vecteur3D halfsize)
{
	this->halfSize = halfsize;


	for (int i = 0; i < 8; i++)
	{
		vertices[i] = offset*vertices[i];
	}

}

Box::Box(RigidBody* body) : Primitive(body)
{
	this->body=body;
	if (body->getShapeID() == 2) {
		this->halfSize = Vecteur3D(((CylinderRigidBody*)body)->getRadius(), ((CylinderRigidBody*)body)->getHeight(), ((CylinderRigidBody*)body)->getRadius());
	}
	else {
		this->halfSize = Vecteur3D(((BoxRigidBody*)body)->getWidth() / 2, ((BoxRigidBody*)body)->getHeight() / 2, ((BoxRigidBody*)body)->getDepth() / 2);
	}
	

}

