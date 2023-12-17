#include "BoxRigidBody.h"


//BoxRigidBody::BoxRigidBody()
//{
//	
//}
//
//
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
	Vecteur3D rad = Vecteur3D(this->width / 2, this->height / 2, this->depth / 2);
	return rad.norme();
	/*float diag = sqrt(pow(this->width/2, 2) + pow(this->height/2, 2));
    return sqrt(pow(diag, 2) + pow(this->depth/2, 2));*/
}

void BoxRigidBody::calculateDerivedData()
{
	float mass = 1 / this -> getInverseMass();
	float height = this->getHeight();
	float width = this->getWidth();
	float depth = this->getDepth();
	Matrix33 CubeInertiaTensor;
	CubeInertiaTensor.setValues(1.0f / 12.0f * mass * (height * height + depth * depth), 0, 0,
		0, 1.0f / 12.0f * mass * (width * width + depth * depth), 0,
		0, 0, 1.0f / 12.0f * mass * (width * width + height * height));
	this->setInverseInertiaTensor(CubeInertiaTensor.Inverse());

	this->getOrientation().Normalized();

	//calculate the transform matrix
	Matrix34 transformMatrix = this->getTransformMatrix();


	transformMatrix.setOrientationAndPosition(this->getOrientation(), this->getPosition());
	this->setTransformMatrix(transformMatrix);
	

	//get the 3x3 of transform matrix
	Matrix33 orientationMatrix = this->getTransformMatrix().getOrientation();

	this->setInverseInertiaTensor(getInverseInertiaTensor()* orientationMatrix);
	this->setInverseInertiaTensorWorld(this->getTransformMatrix().getOrientation() * this->getInverseInertiaTensor() * this->getTransformMatrix().getOrientation().Inverse());
}


