#include "GravityForceGenerator.h"

void GravityGenerator::updateForce(RigidBody* rigidBody)
{
	rigidBody->addForce( gravity/ rigidBody->getInverseMass());
}

Vecteur3D GravityGenerator::getBodyAnchor()
{
	return Vecteur3D();
} 