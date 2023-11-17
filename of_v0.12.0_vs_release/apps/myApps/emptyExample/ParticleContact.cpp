#include "ParticleContact.h"




void ParticleContact::resolve(float duration) {
	resolveVelocity();
	resolveInterpenetration();
}

float ParticleContact::calculateSeparatingVelocity() {
	//vitesse de séparation = (v1-v2) * n
	//verify the existence of the particles
	if (particle[0] == NULL) {
		return 0;
	}
	if (particle[1] == NULL) {
		return 0;
	}
	return (particle[0]->getVelocite() - particle[1]->getVelocite()).ProduitScalaire(contactNormal);
}

void ParticleContact::resolveVelocity() {

	//post collision velocity = velocity + k*vector normal /mass (=1)
	//k = -(1+e) * (v1-v2) * n / (1/m1 + 1/m2)
//e = restitution	

	float k = -(1 + restitution) * (particle[0]->getVelocite() - particle[1]->getVelocite()).ProduitScalaire(contactNormal) / (1 / particle[0]->getMasse() + 1 / particle[1]->getMasse());
	particle[0]->setVelocite(particle[0]->getVelocite() + contactNormal.mul(k / particle[0]->getMasse()));
	particle[1]->setVelocite(particle[1]->getVelocite() - contactNormal.mul(k / particle[1]->getMasse()));

}

void ParticleContact::resolveInterpenetration() {

	//somme total de l'interpénétration =  deltaP1 + deltaP2 = d
	//ratio pondéré par la masse des objets = m1deltaP1 = m2deltaP2
	//en combinant les deux équations et en appliquant le déplacement dans la direction normale au contact
	// deltaP1 = d normalvector * m2 / (m1+m2)
	// deltaP2 = d normalvector * m1 / (m1+m2)

	float m1 = particle[0]->getMasse();
	float m2 = particle[1]->getMasse();
	float totalMass = m1 + m2;
	float deltaP1 = penetration * m2 / totalMass;
	float deltaP2 = penetration * m1 / totalMass;
	particle[0]->setPosition(particle[0]->getPosition() + contactNormal.mul(deltaP1));
	particle[1]->setPosition(particle[1]->getPosition() - contactNormal.mul(deltaP2));

}





