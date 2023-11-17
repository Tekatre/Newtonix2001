#include "ParticleAnchorSpring.h"

ParticleAnchorSpring::ParticleAnchorSpring(Vecteur3D anchor, float k, float lzero) {
	this->anchor = anchor;
	this->k = k;
	this->lzero = lzero;
}

void ParticleAnchorSpring::updateForce(Particule* p, float dt)
{
	Vecteur3D d = (p->getPosition() - anchor);
	Vecteur3D dir = d / d.norme();
	p->addAcceleration(dir.mul((-k / p->getMasse()) * (d.norme() - lzero)));
}