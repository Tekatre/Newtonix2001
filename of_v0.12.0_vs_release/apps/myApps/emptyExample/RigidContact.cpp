#include "RigidContact.h"

RigidContact::RigidContact()
{
}

RigidContact::~RigidContact()
{
}	

void RigidContact::resolve(float duration) {


}

void RigidContact::resolveInterpenetration(float duration) {
	//calculer l'inertie totale
	Matrix33 totalInertia = body[0]->getInverseInertiaTensor().Inverse() + body[1]->getInverseInertiaTensor().Inverse();
	Matrix33 totalInertiaInverse = totalInertia.Inverse();
	//calculer l'inertie linéaire pour chaque body

	Vecteur3D linearInertia[2];
	linearInertia[0] = body[0]->getInverseInertiaTensor().Inverse() * this->contactNormal;
	linearInertia[1] = body[1]->getInverseInertiaTensor().Inverse() * this->contactNormal;

	//calculer l'inertie angulaire pour chaque body
	Vecteur3D angularInertia[2];
	//angularInertia[0] = body[0]->getInverseInertiaTensor().Inverse() * (this->worldContactPoint - body[0]->getPosition()).cross(this->contactNormal);
}

