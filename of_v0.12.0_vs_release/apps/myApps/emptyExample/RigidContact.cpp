#include "RigidContact.h"

RigidContact::RigidContact()
{
}

RigidContact::~RigidContact()
{
}	

void RigidContact::resolve(float duration) {


}

void RigidContact::resolveInterpenetration(float duration) {
	//étapes : poids de l'inertie linéaire pour les objets : deltap'd = ma^-1 + mb^-1
	//         poids de l'inertie angulaire pour les objets : 
	//             u = qrel + d
	//             deltatheta' = I^-1 * u
	//             q' = theta' * qrel
	//Calcul du déplacement angulaire linéaire pondéré :
	//			real inverseInertia = 1 / totalInertia;
	//			linearMove[0] = penetration * linearInertia[0] * inverseInertia;
	//			linearMove[1] = penetration * linearInertia[1] * inverseInertia;
	//			angularMove[0] = penetration * angularInertia[0] * inverseInertia;
	//			angularMove[1] = penetration * angularInertia[1] * inverseInertia;
	// Mouvement Linéaire : 
	//			body[0]->setPosition(body[0]->getPosition() + contactNormal*linearMove[0]);
	//			body[1]->setPosition(body[1]->getPosition() - contactNormal*linearMove[1]);

	//code :
	//calcul de la masse totale
	float totalMass = body[0]->getInverseMass() + body[1]->getInverseMass();
	//calcul du déplacement linéaire pondéré
	Vecteur3D linearMove[2];
	linearMove[0] = contactNormal * (penetration * body[0]->getInverseMass() / totalMass);
	linearMove[1] = contactNormal * (penetration * body[1]->getInverseMass() / totalMass);
	//mise à jour de la position
	/*body[0]->setPosition(body[0]->getPosition() + linearMove[0]);
	body[1]->setPosition(body[1]->getPosition() - linearMove[1]);*/


}

