#include "SphereRigidBody.h"

SphereRigidBody::~SphereRigidBody()
{
}

float SphereRigidBody::getRadius()
{
	return radius;
}

void SphereRigidBody::setRadius(float Radius)
{
	radius = Radius;
}

float SphereRigidBody::getOuterRadius()
{
	return radius;
}

void SphereRigidBody::calculateDerivedData()
{
	float mass = 1 / this->getInverseMass();
	Matrix33 SphereInertiaTensor;
	SphereInertiaTensor.setValues(2.0f / 5.0f * mass * radius * radius, 0, 0,
				0, 2.0f / 5.0f * mass * radius * radius, 0,
				0, 0, 2.0f / 5.0f * mass * radius * radius);

	this->setInverseInertiaTensor(SphereInertiaTensor.Inverse());

	this->getOrientation().Normalized();
	Matrix34 transformMatrix = this->getTransformMatrix();
	transformMatrix.setOrientationAndPosition(this->getOrientation(), this->getPosition());
	this->setTransformMatrix(transformMatrix);
	//get the 3x3 of transform matrix
	Matrix33 orientationMatrix = this->getTransformMatrix().getOrientation();

	this->setInverseInertiaTensor(getInverseInertiaTensor() * orientationMatrix);
}