#include "ParticleSpring.h"

ParticleSpring::ParticleSpring(Particule* p, float k, float lzero) {
	this->other = p;
	this->k = k;
	this->lzero = lzero;
}

void ParticleSpring::updateForce(Particule* p, float dt)
{
	Vecteur3D d = (p->getPosition() - other->getPosition());
	Vecteur3D dir = d / d.norme();
	p->addAcceleration(dir.mul((-k / p->getMasse()) * (d.norme() - lzero)));
}

//Particule ParticleSpring::getOther()
//{
//	return *other;
//}
//
//void ParticleSpring::setOther(Particule* p)
//{
//	other = p;
//}