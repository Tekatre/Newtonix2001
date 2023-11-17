#include "ParticleCable.h"


unsigned int ParticleCable::addContact(ParticleContact* contact, unsigned int limit) {
	
	// Find the length of the cable
	float length = currentLength();

	// Check if we're over-extended
	if (length < maxLength) return 0;

	ParticleContact newContact;// = new ParticleContact();

	// Otherwise return the contact
	newContact.particle[0] = particle[0];
	newContact.particle[1] = particle[1];

	// Calculate the normal
	Vecteur3D normal = (particle[1]->getPosition() - particle[0]->getPosition()).normalize();

	newContact.contactNormal = normal;

	newContact.penetration = length - maxLength;
	newContact.restitution = restitution;

	contact[limit] = newContact;

	return 1;
   

}

