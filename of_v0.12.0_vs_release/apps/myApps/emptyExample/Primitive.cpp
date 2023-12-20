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