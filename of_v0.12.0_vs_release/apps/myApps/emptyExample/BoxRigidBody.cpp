#include "BoxRigidBody.h"




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
	//tenseur d'inertie inverse local d'un pavé : I = m/12 * (h²+d², w²+d², w²+h²)
	//calculé directement avec l'inverse de la masse (évite 1/0 pour une masse infinie)
	float inverseMass = this->getInverseMass();
	float height = this->getHeight();
	float width = this->getWidth();
	float depth = this->getDepth();
	Matrix33 CubeInverseInertiaTensor;
	CubeInverseInertiaTensor.setValues(12.0f * inverseMass / (height * height + depth * depth), 0, 0,
		0, 12.0f * inverseMass / (width * width + depth * depth), 0,
		0, 0, 12.0f * inverseMass / (width * width + height * height));
	this->setInverseInertiaTensor(CubeInverseInertiaTensor);

	//matrice de transformation et tenseur en coordonnées monde
	RigidBody::calculateDerivedData();
}


int BoxRigidBody::getShapeID()
{
	return this->shapeID;
}