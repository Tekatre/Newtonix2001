#include "RigidBody.h"


RigidBody::RigidBody()
{
}

RigidBody::~RigidBody()
{
}

double RigidBody::getInverseMass()
{
	return this->inverseMass;
}

void RigidBody::setInverseMass(double mass)
{
	this->inverseMass = mass;
}

double RigidBody::getLinearDamping()
{
	return this->linearDamping;
}

void RigidBody::setLinearDamping(double damping)
{
	this->linearDamping = damping;
}

double RigidBody::getAngularDamping()
{
	return this->angularDamping;
}

void RigidBody::setAngularDamping(double damping)
{
	this->angularDamping = damping;
}

Vecteur3D RigidBody::getPosition()
{
	return this->position;
}

void RigidBody::setPosition(Vecteur3D pos)
{
	this->position = pos;
}

Vecteur3D RigidBody::getVelocity()
{
	return this->velocity;
}

void RigidBody::setVelocity(Vecteur3D vel)
{
	this->velocity = vel;
}

Vecteur3D RigidBody::getForceAccum()
{
	return this->forceAccum;
}

void RigidBody::setForceAccum(Vecteur3D force)
{
	this->forceAccum = force;
}

Vecteur3D RigidBody::getTorqueAccum()
{
	return this->torqueAccum;
}

void RigidBody::setTorqueAccum(Vecteur3D torque)
{
	this->torqueAccum = torque;
}	

Quaternion RigidBody::getOrientation()
{
	return this->orientation;
}

void RigidBody::setOrientation(Quaternion q)
{
	this->orientation = q;
}

Vecteur3D RigidBody::getRotation()
{
	return this->rotation;
}

void RigidBody::setRotation(Vecteur3D rot)
{
	this->rotation = rot;
}

Matrix34 RigidBody::getTransformMatrix()
{
	return this->transformMatrix;
}

void RigidBody::setTransformMatrix(Matrix34 matrix)
{
	this->transformMatrix = matrix;
}

void RigidBody::integrate(double duration)
{

	//mise à jour de la position
	this->position = this->position + this->velocity * duration;
	//mise à jour de l'orientation
	this->orientation.UpdateByAngularVelocity(this->rotation, duration);
	//Calculer les valeurs dérivées (matrice de transformation et I^-1')
	this->calculateDerivedData();
	//Calculer l'accélération linéaire p.. = F/m
	Vecteur3D acceleration = this->forceAccum * this->inverseMass;
	//Calculer l'accélération angulaire a.. = I^-1' * T
	Vecteur3D angularAcceleration = InverseInertiaTensor * torqueAccum;
	//Mettre à jour la vélocité linéaire
	this->velocity = this->velocity + acceleration * duration;
	//Mettre à jour la vélocité angulaire
	this->rotation = this->rotation + angularAcceleration * duration;

	//Réinitialiser les forces et les torques
	this->clearAccumulator();


}

void RigidBody::addForce(const Vecteur3D& force)
{
	this->setForceAccum(this->getForceAccum() + force);
}

void RigidBody::calculateDerivedData()
{
	//call each frame to calculate the transform matrix and normalize the orientation
	this->orientation.Normalized();
	//this->transformMatrix.setOrientationAndPosition(this->orientation, this->position);

	//calculate the intertia matrix for a cylinder
	double mass = 1.0f / this->inverseMass;
	double radius = 1.0f;
	double height = 1.0f;
	//create a matrix with the inertia tensor values

InverseInertiaTensor.setValues(0.083f * mass * (3.0f * radius * radius + height * height), 0.0f, 0.0f,
0.0f, 0.083f * mass * (3.0f * radius * radius + height * height), 0.0f,
0.0f, 0.0f, 0.5f * mass * radius * radius);




	this->transformMatrix.Inverse();




}


void RigidBody::clearAccumulator()
{
	this->setForceAccum(Vecteur3D(0, 0, 0));
	this->setTorqueAccum(Vecteur3D(0, 0, 0));

}



