#include "AnchorForceGenerator.h"

AnchorForceGenerator::AnchorForceGenerator(Vecteur3D anchor, float k, float lzero)
{
	this->anchor = anchor;
	this->k = k;
	this->lzero = lzero;
}


void AnchorForceGenerator::updateForce(RigidBody* rigidBody, int type, Vecteur3D point)
{
	
		Vecteur3D d = (rigidBody->getTransformMatrix() * point - anchor);
		if (d.norme() == 0) {
			return;
		}
		Vecteur3D dir = d / d.norme();
		Vecteur3D force = dir.mul((-k * rigidBody->getInverseMass()) * (d.norme() - lzero));
		
	
		
		
		if (type == 0) {
			rigidBody->addForce(force);
		}
		if (type == 2) {
			rigidBody->addForceAtBodyPoint(force, point);
		}
}