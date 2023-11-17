#include "ParticleRod.h"
#include <vector>

unsigned int ParticleRod::addContact(ParticleContact* contact, unsigned int limit) {
	
	// Find the length of the cable
	float currentLen = currentLength();

	// Check if we're over-extended
	if (currentLen == length) return 0;


	ParticleContact newContact;// = new ParticleContact();

	// Otherwise return the contact
	newContact.particle[0] = particle[0];
	newContact.particle[1] = particle[1];

	// Calculate the normal
	Vecteur3D normal = (particle[1]->getPosition() - particle[0]->getPosition()).normalize();

	// The contact normal depends on whether we're extending or compressing
	if (currentLen > length) {
		newContact.contactNormal = normal;
		newContact.penetration = currentLen - length;
	}
	else {
		newContact.contactNormal = normal * -1;
		newContact.penetration = length - currentLen;
	}

	// Always use zero restitution (no bounciness)
	newContact.restitution = 0;

	contact[limit] = newContact;

	return 1;
   
}