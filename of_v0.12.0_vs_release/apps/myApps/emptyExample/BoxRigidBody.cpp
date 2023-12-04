#include "BoxRigidBody.h"


BoxRigidBody::BoxRigidBody()
{
}


BoxRigidBody::~BoxRigidBody()
{
}

float BoxRigidBody::getWidth()
{
	return this->width;
}

void BoxRigidBody::setWidth(float width)
{
	this->width = width;
}

float BoxRigidBody::getHeight()
{
	return this->height;
}

void BoxRigidBody::setHeight(float height)
{
	this->height = height;
}

float BoxRigidBody::getDepth()
{
	return this->depth;
}

void BoxRigidBody::setDepth(float depth)
{
	this->depth = depth;
}

float BoxRigidBody::getOuterRadius()
{
	float diag = sqrt(pow(this->width/2, 2) + pow(this->height/2, 2));
    return sqrt(pow(diag, 2) + pow(this->depth/2, 2));
}