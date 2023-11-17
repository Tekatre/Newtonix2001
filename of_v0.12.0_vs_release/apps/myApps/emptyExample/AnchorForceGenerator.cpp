#include "AnchorForceGenerator.h"

AnchorForceGenerator::AnchorForceGenerator(Vecteur3D anchor, float k, float lzero)
{
	this->anchor = anchor;
	this->k = k;
	this->lzero = lzero;
}

void AnchorForceGenerator::updateForce(RigidBody* p, Vecteur3D applicationPoint, int type)
{
	

	
		Vecteur3D d = (p->getPosition() - anchor);
		Vecteur3D dir = d / d.norme();
		Vecteur3D forcetoAdd = dir.mul((-k / (1 / p->getInverseMass())) * (d.norme() - lzero));
		if (type == 0) {
			p->addForce(forcetoAdd);
		}
	
		if (type == 1) {
			p->addForceAtPoint(forcetoAdd, applicationPoint);
		}

		if (type == 2) {
			p->addForceAtBodyPoint(forcetoAdd, applicationPoint);
		}

}