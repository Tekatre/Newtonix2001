#include "DragForceGenerator.h"

void DragForceGenerator::updateForce(RigidBody* rigidBody)
{
	float vnorm = rigidBody->getVelocity().norme();
	float val = ((k1 * vnorm) + (k2 * pow(vnorm, 2)));
	rigidBody->addForce(rigidBody->getVelocity() * (-1) * val * rigidBody->getInverseMass()/vnorm) ;
}

Vecteur3D DragForceGenerator::getBodyAnchor()
{
	return Vecteur3D();
}