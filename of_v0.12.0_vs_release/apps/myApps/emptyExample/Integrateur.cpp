#include "Integrateur.h"
#include <ofAppRunner.h>


Integrateur::Integrateur()
{
	// Constructeur par défaut

}

Integrateur::~Integrateur()
{
	// Destructeur
}

void Integrateur::integrer(Particule* p, double time)
{
	Vecteur3D position = p->getPosition();
	Vecteur3D velocite = p->getVelocite();
	Vecteur3D acceleration = p->getAcceleration();
	p->setPosition(position.add(velocite.mul(time)));
	p->setVelocite(velocite.add(acceleration.mul(time)));
}

void Integrateur::integrer(RigidBody* r, double time) {
	r->integrate(time);
}