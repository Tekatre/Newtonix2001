#include "AnchorForceGenerator.h"

AnchorForceGenerator::AnchorForceGenerator(Vecteur3D anchor, float k, float lzero)
{
	this->anchor = anchor;
	this->k = k;
	this->lzero = lzero;
}


void AnchorForceGenerator::updateForce(RigidBody* rigidBody, int type, Vecteur3D point)
{
	if (type == 0) {
		Vecteur3D d = (rigidBody->getPosition() - anchor);
		if (d.norme() == 0) {
			return;
		}
		Vecteur3D dir = d / d.norme();
		Vecteur3D force = dir.mul((-k / (1 / rigidBody->getInverseMass())) * (d.norme() - lzero));
		rigidBody->addForce(force);
	}
	if (type == 2) {
		//the anchor is link to the point on the rigidbody
		Vecteur3D d = (rigidBody->getPosition() - anchor);
		if (d.norme() == 0) {
			return;
		}
		Vecteur3D dir = d / d.norme();
		Vecteur3D force = dir.mul((-k / (1 / rigidBody->getInverseMass())) * (d.norme() - lzero));
		rigidBody->addForceAtBodyPoint(force, point);
	}
}