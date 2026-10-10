#include "GravityForceGenerator.h"

void GravityGenerator::updateForce(RigidBody* rigidBody)
{
	if (rigidBody->getInverseMass() == 0) {
		//masse infinie (objet statique, ex : le sol) : pas soumis a la gravite
		return;
	}
	rigidBody->addForce( gravity/ rigidBody->getInverseMass());
}

Vecteur3D GravityGenerator::getBodyAnchor()
{
	return Vecteur3D();
} 