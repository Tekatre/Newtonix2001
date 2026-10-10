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
	//tenseur d'inertie inverse local d'une sphère pleine : I = 2/5 * m * r²
	float inverseMass = this->getInverseMass();
	Matrix33 SphereInverseInertiaTensor;
	SphereInverseInertiaTensor.setValues(5.0f * inverseMass / (2.0f * radius * radius), 0, 0,
				0, 5.0f * inverseMass / (2.0f * radius * radius), 0,
				0, 0, 5.0f * inverseMass / (2.0f * radius * radius));
	this->setInverseInertiaTensor(SphereInverseInertiaTensor);

	//matrice de transformation et tenseur en coordonnées monde
	RigidBody::calculateDerivedData();
}

int SphereRigidBody::getShapeID()
{
	return shapeID;
}