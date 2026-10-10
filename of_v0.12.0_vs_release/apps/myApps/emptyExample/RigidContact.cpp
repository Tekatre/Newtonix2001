#include "RigidContact.h"

RigidContact::RigidContact()
{
}

RigidContact::~RigidContact()
{
}	


void RigidContact::resolveInterpenetration(float duration) {

	//Convention : la normale de contact pointe vers body[0]
	//On ne fait que du déplacement linéaire (pas de correction angulaire), donc la pénétration
	//est répartie uniquement selon les inverses des masses pour être entièrement résolue
	float totalInverseMass = body[0]->getInverseMass() + body[1]->getInverseMass();
	if (totalInverseMass <= 0) {
		//deux objets de masse infinie : rien à déplacer
		return;
	}

	float linearMove[2];
	linearMove[0] = penetration * (body[0]->getInverseMass() / totalInverseMass);
	linearMove[1] = -penetration * (body[1]->getInverseMass() / totalInverseMass);

	body[0]->setPosition(body[0]->getPosition() + contactNormal * linearMove[0]);
	body[1]->setPosition(body[1]->getPosition() + contactNormal * linearMove[1]);

	//TODO ANGULAIRE
}


float RigidContact::calculateSeparatingVelocity() {
	//vitesse de séparation = (v1-v2) * n, avec la vitesse des corps AU POINT de contact (v + w x r)
	//verify the existence of the particles
	if (body[0] == NULL) {
		return 0;
	}
	if (body[1] == NULL) {
		return 0;
	}
	Vecteur3D r1 = worldContactPoint - body[0]->getPosition();
	Vecteur3D r2 = worldContactPoint - body[1]->getPosition();
	Vecteur3D v1 = body[0]->getVelocity() + (body[0]->getRotation() ^ r1);
	Vecteur3D v2 = body[1]->getVelocity() + (body[1]->getRotation() ^ r2);
	return (v1 - v2).ProduitScalaire(contactNormal);
}


void RigidContact::resolveVelocity(float duration) {
	float separatingVelocity = calculateSeparatingVelocity();
	if (separatingVelocity >= 0) {
		//les objets s'éloignent déjà
		return;
	}

 	Vecteur3D r1 = worldContactPoint - body[0]->getPosition();
	Vecteur3D r2 = worldContactPoint - body[1]->getPosition();

	//masse effective au point de contact :
	//1/m1 + 1/m2 + ((I1^-1 (r1 x n)) x r1).n + ((I2^-1 (r2 x n)) x r2).n
	Vecteur3D angularPart1 = (body[0]->getInverseInertiaTensorWorld() * (r1 ^ contactNormal)) ^ r1;
	Vecteur3D angularPart2 = (body[1]->getInverseInertiaTensorWorld() * (r2 ^ contactNormal)) ^ r2;
	float denominator = body[0]->getInverseMass() + body[1]->getInverseMass()
		+ angularPart1.ProduitScalaire(contactNormal) + angularPart2.ProduitScalaire(contactNormal);
	if (denominator <= 0) {
		return;
	}

	//une seule impulsion k, appliquée à la fois sur la vitesse linéaire et angulaire
	float k = -(1 + restitution) * separatingVelocity / denominator;
	applyImpulse(contactNormal * k, r1, r2);

	//Frottement de Coulomb : impulsion tangentielle qui s'oppose au glissement,
	//limitée à friction * k (cône de frottement)
	if (friction <= 0) {
		return;
	}
	Vecteur3D v1 = body[0]->getVelocity() + (body[0]->getRotation() ^ r1);
	Vecteur3D v2 = body[1]->getVelocity() + (body[1]->getRotation() ^ r2);
	Vecteur3D relativeVelocity = v1 - v2;
	Vecteur3D tangentVelocity = relativeVelocity - contactNormal * relativeVelocity.ProduitScalaire(contactNormal);
	float slidingSpeed = tangentVelocity.norme();
	if (slidingSpeed < 0.0001) {
		return;
	}
	Vecteur3D tangent = tangentVelocity / slidingSpeed;

	//masse effective dans la direction tangentielle
	Vecteur3D tangentAngularPart1 = (body[0]->getInverseInertiaTensorWorld() * (r1 ^ tangent)) ^ r1;
	Vecteur3D tangentAngularPart2 = (body[1]->getInverseInertiaTensorWorld() * (r2 ^ tangent)) ^ r2;
	float tangentDenominator = body[0]->getInverseMass() + body[1]->getInverseMass()
		+ tangentAngularPart1.ProduitScalaire(tangent) + tangentAngularPart2.ProduitScalaire(tangent);
	if (tangentDenominator <= 0) {
		return;
	}

	//impulsion qui annulerait le glissement, bornée par le frottement maximal
	float frictionImpulse = slidingSpeed / tangentDenominator;
	if (frictionImpulse > friction * k) {
		frictionImpulse = friction * k;
	}
	applyImpulse(tangent * (-frictionImpulse), r1, r2);
}

void RigidContact::applyImpulse(Vecteur3D impulse, Vecteur3D r1, Vecteur3D r2) {
	//impulsion appliquée au point de contact : +impulse sur body[0], -impulse sur body[1]
	body[0]->setVelocity(body[0]->getVelocity() + impulse * body[0]->getInverseMass());
	body[1]->setVelocity(body[1]->getVelocity() - impulse * body[1]->getInverseMass());

	body[0]->setRotation(body[0]->getRotation() + body[0]->getInverseInertiaTensorWorld() * (r1 ^ impulse));
	body[1]->setRotation(body[1]->getRotation() - body[1]->getInverseInertiaTensorWorld() * (r2 ^ impulse));
}

void RigidContact::setBodyData(RigidBody* one, RigidBody* two, float friction, float restitution) {
	RigidContact::body[0] = one;
	RigidContact::body[1] = two;
	RigidContact::friction = friction;
	RigidContact::restitution = restitution;
}
