#include "RigidContact.h"

RigidContact::RigidContact()
{
}

RigidContact::~RigidContact()
{
}	


void RigidContact::resolveInterpenetration(float duration) {


	float totalInertia = 0;
	float linearInertia[2];
	float angularInertia[2];
	//calcul de l'inertie lin�aire et angulaire
	linearInertia[0] = body[0]->getInverseMass();
	linearInertia[1] = body[1]->getInverseMass();

	Vecteur3D u = (worldContactPoint - body[0]->getPosition())^contactNormal;
	Vecteur3D accelangu1 = body[0]->getInverseInertiaTensorWorld() * u;
	angularInertia[0] = (accelangu1 ^ u).ProduitScalaire(contactNormal);

	u = (worldContactPoint - body[1]->getPosition())^contactNormal;
	Vecteur3D accelangu2 = body[1]->getInverseInertiaTensorWorld() * u;
	angularInertia[1] = (accelangu2 ^ u).ProduitScalaire(contactNormal);

	totalInertia = linearInertia[0] + linearInertia[1] + angularInertia[0] + angularInertia[1];

	float inverseInertia = 1 / totalInertia;
	float linearMove[2];
	float angularMove[2];
	linearMove[0] = penetration * (linearInertia[0] * inverseInertia);
	linearMove[1] = -penetration * (linearInertia[1] * inverseInertia);
	angularMove[0] = penetration * (angularInertia[0] * inverseInertia);
	angularMove[1] = -penetration * (angularInertia[1] * inverseInertia);

	body[0]->setPosition(body[0]->getPosition() + contactNormal * linearMove[0]);
	body[1]->setPosition(body[1]->getPosition() + contactNormal * linearMove[1]);

	//TODO ANGULAIRE





}


float RigidContact::calculateSeparatingVelocity() {
	//vitesse de s�paration = (v1-v2) * n
	//verify the existence of the particles
	if (body[0] == NULL) {
		return 0;
	}
	if (body[1] == NULL) {
		return 0;
	}
	return (body[0]->getVelocity() - body[1]->getVelocity()).ProduitScalaire(contactNormal);
}


void RigidContact::resolveVelocity(float duration) {
	float k = -(1 + restitution) * (body[0]->getVelocity() - body[1]->getVelocity()).ProduitScalaire(contactNormal) / (body[0]->getInverseMass() + body[1]->getInverseMass());
	body[0]->setVelocity(body[0]->getVelocity() + contactNormal.mul(k * body[0]->getInverseMass()));
	body[1]->setVelocity(body[1]->getVelocity() - contactNormal.mul(k * body[1]->getInverseMass()));
}