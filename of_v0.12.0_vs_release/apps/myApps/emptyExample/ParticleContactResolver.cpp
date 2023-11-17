#include "ParticleContactResolver.h"


void ParticleContactResolver::resolveContacts(ParticleContact* contactArray, unsigned int numContacts, float duration) {
	//resolve les contacts de la vitesse de séparation la plus élevée à la plus faible

	/*for (unsigned int i = 0; i < numContacts; i++) {
		float max = 0;
		unsigned int maxIndex = i;
		for (unsigned int j = i; j < numContacts; j++) {
			float sepVel = contactArray[j].calculateSeparatingVelocity();
			if (sepVel < max) {
				max = sepVel;
				maxIndex = j;
			}
		}
		ParticleContact temp = contactArray[i];
		contactArray[i] = contactArray[maxIndex];
		contactArray[maxIndex] = temp;
	}*/

	//résoudre les contacts
	for (unsigned int i = 0; i < numContacts; i++) {
		contactArray[i].resolve(duration);
	}


}
