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
	//le cylindre est traite comme une boite (r, h/2, r) pour les collisions :
	//on renvoie le rayon de la sphere englobant cette boite, pour que le BSP soit coherent
	Vecteur3D rad = Vecteur3D(this->radius, this->height / 2, this->radius);
	return rad.norme();
}

void CylinderRigidBody::calculateDerivedData()
{
	//tenseur d'inertie inverse local d'un cylindre plein d'axe Y (comme ofCylinderPrimitive) :
	//Ixx = Izz = m/12 * (3r² + h²), Iyy = m/2 * r²
	float inverseMass = this->getInverseMass();
	float height = this->getHeight();
	float radius = this->getRadius();
	Matrix33 CylinderInverseInertiaTensor;
	CylinderInverseInertiaTensor.setValues(12.0f * inverseMass / (3 * radius * radius + height * height), 0, 0,
				0, 2.0f * inverseMass / (radius * radius), 0,
				0, 0, 12.0f * inverseMass / (3 * radius * radius + height * height));
	this->setInverseInertiaTensor(CylinderInverseInertiaTensor);

	//matrice de transformation et tenseur en coordonnées monde
	RigidBody::calculateDerivedData();
}

int CylinderRigidBody::getShapeID()
{
	return shapeID;
}



