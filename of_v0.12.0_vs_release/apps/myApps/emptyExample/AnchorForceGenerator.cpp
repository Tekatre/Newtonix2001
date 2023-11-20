#include "AnchorForceGenerator.h"

AnchorForceGenerator::AnchorForceGenerator(Vecteur3D anchor, Vecteur3D bodyAnchor, float k, float lzero)
{
	this->anchor = anchor;
	this->bodyAnchor = bodyAnchor;
	this->k = k;
	this->lzero = lzero;
}


void AnchorForceGenerator::updateForce(RigidBody* rigidBody)
{
	
		Vecteur3D d = (rigidBody->getTransformMatrix() * bodyAnchor - anchor);
		if (d.norme() == 0) {
			return;
		}
		Vecteur3D dir = d / d.norme();
		Vecteur3D force = dir.mul((-k * rigidBody->getInverseMass()) * (d.norme() - lzero));
		
	
	
		rigidBody->addForceAtBodyPoint(force, bodyAnchor);
		
}

Vecteur3D AnchorForceGenerator::getBodyAnchor()
{
	return bodyAnchor;
}