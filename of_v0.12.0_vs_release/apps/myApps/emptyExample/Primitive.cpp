#include "Primitive.h"

Primitive::Primitive()
{
}

Primitive::Primitive(RigidBody* body)
{
	this->body = body;
	this->offset = body->getTransformMatrix();
	this->transform = body->getTransformMatrix();

}

Primitive::~Primitive()
{
}

Vecteur3D Primitive::getAxis(int index)
{
	if (index == 0) {
		//use the quaternion of the body to get the axis
		return body->getTransformMatrix().getOrientation() * Vecteur3D(1, 0, 0);
	}
	else if (index == 1) {
		return body->getTransformMatrix().getOrientation() * Vecteur3D(0, 1, 0);
	}
	else if (index == 2) {
		return body->getTransformMatrix().getOrientation() * Vecteur3D(0, 0, 1);
	}
	else {
		return body->getPosition();
	}
}