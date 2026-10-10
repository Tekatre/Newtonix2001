#include "Primitive.h"

Primitive::Primitive()
{
	axes[0] = Vecteur3D(1, 0, 0);
	axes[1] = Vecteur3D(0, 1, 0);
	axes[2] = Vecteur3D(0, 0, 1);
}

Primitive::Primitive(RigidBody* body)
{
	this->body = body;
	this->offset = body->getTransformMatrix();
	this->transform = body->getTransformMatrix();

	//use the orientation of the body to get the axis
	Matrix33 orientation = this->transform.getOrientation();
	axes[0] = orientation * Vecteur3D(1, 0, 0);
	axes[1] = orientation * Vecteur3D(0, 1, 0);
	axes[2] = orientation * Vecteur3D(0, 0, 1);
}

Primitive::~Primitive()
{
}

Vecteur3D Primitive::getAxis(int index)
{
	if (index >= 0 && index < 3) {
		return axes[index];
	}
	else {
		return body->getPosition();
	}
}
