#include "ParticleDrag.h"

void ParticleDrag::updateForce(Particule* p, float dt)
{
	float vnorm = p->getVelocite().norme();
	float val = ((k1 * vnorm) + (k2 * pow(vnorm, 2)));
	p->addAcceleration(p->getVelocite() * (-1) * val / (p->getMasse() * vnorm));
}
