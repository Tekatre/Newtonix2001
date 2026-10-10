#include "DragForceGenerator.h"

void DragForceGenerator::updateForce(RigidBody* rigidBody)
{
	float vnorm = rigidBody->getVelocity().norme();
	if (vnorm == 0) {
		//objet immobile : pas de frottement (et pas de division par 0)
		return;
	}
	float val = ((k1 * vnorm) + (k2 * pow(vnorm, 2)));
	//F = -(k1*|v| + k2*|v|²) * v/|v| : la masse est prise en compte dans RigidBody::integrate
	rigidBody->addForce(rigidBody->getVelocity() * (-1) * val / vnorm) ;
}

Vecteur3D DragForceGenerator::getBodyAnchor()
{
	return Vecteur3D();
}