#include "CylinderRigidBody.h"


float CylinderRigidBody::getRadius()
{
	return radius;
}

void CylinderRigidBody::setRadius(float Radius)
{
	radius = Radius;
}

float CylinderRigidBody::getHeight()
{
	return height;
}

void CylinderRigidBody::setHeight(float Height)
{
	height = Height;
}

float CylinderRigidBody::getOuterRadius()
{
	Vecteur3D rad = Vecteur3D(this->radius, this->height / 2, 0);
	return rad.norme();
}

void CylinderRigidBody::calculateDerivedData()
{
	float mass = 1 / this->getInverseMass();
	float height = this->getHeight();
	float radius = this->getRadius();
	Matrix33 CylinderInertiaTensor;
	CylinderInertiaTensor.setValues(1.0f / 12.0f * mass * (3 * radius * radius + height * height), 0, 0,
				0, 1.0f / 12.0f * mass * (3 * radius * radius + height * height), 0,
				0, 0, 1.0f / 2.0f * mass * radius * radius);

	this->setInverseInertiaTensor(CylinderInertiaTensor.Inverse());

	this->getOrientation().Normalized();
	Matrix34 transformMatrix = this->getTransformMatrix();
	transformMatrix.setOrientationAndPosition(this->getOrientation(), this->getPosition());
	this->setTransformMatrix(transformMatrix);
	//get the 3x3 of transform matrix
	Matrix33 orientationMatrix = this->getTransformMatrix().getOrientation();

	this->setInverseInertiaTensor(getInverseInertiaTensor() * orientationMatrix);
}



