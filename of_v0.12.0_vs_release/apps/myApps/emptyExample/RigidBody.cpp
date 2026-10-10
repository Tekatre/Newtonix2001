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

	//Calculer les valeurs dérivées (la position a pu être modifiée par la résolution des contacts)
	this->calculateDerivedData();
	//Calculer l'accélération linéaire p.. = F/m
	Vecteur3D acceleration = this->forceAccum * this->inverseMass;
	//Calculer l'accélération angulaire a.. = I^-1' * T (tenseur en coordonnées monde)
	Vecteur3D angularAcceleration = InverseInertiaTensorWorld * torqueAccum;
	//Mettre à jour la vélocité linéaire
	this->velocity = this->velocity*(pow(linearDamping,duration)) + acceleration * duration;
	//Mettre à jour la vélocité angulaire
	this->rotation = this->rotation * (pow(angularDamping, duration)) + angularAcceleration * duration;
	//mise à jour de la position (Euler semi-implicite : avec la nouvelle vélocité)
	this->position = this->position + this->velocity * duration;
	//mise à jour de l'orientation
	this->orientation.UpdateByAngularVelocity(this->rotation, duration);
	//Calculer les valeurs dérivées (matrice de transformation et I^-1')
	this->calculateDerivedData();
	//Réinitialiser les forces et les torques
	this->clearAccumulator();


}

void RigidBody::addForce(const Vecteur3D& force)
{
	this->setForceAccum(this->getForceAccum() + force);
}

void RigidBody::addForceAtPoint(const Vecteur3D& force, const Vecteur3D& point)
{
	//point en coordonnées monde : le moment de force est calculé par rapport au centre de masse
	Vecteur3D relativePoint = (Vecteur3D)point - this->position;
	//ajouter la force
	this->addForce(force);
	//ajouter le moment de force
	this->setTorqueAccum(this->getTorqueAccum() + (relativePoint ^ force));
}

void RigidBody::addForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& point)
{
	//convertir le point local en coordonnées globales
	Vecteur3D globalPoint = this->transformMatrix * point;
	this->addForceAtPoint(force, globalPoint);
}
void RigidBody::calculateDerivedData()
{
	//call each frame to calculate the transform matrix and normalize the orientation
	this->orientation.Normalized();

	//calculate the transform matrix
	this->transformMatrix.setOrientationAndPosition(this->orientation, this->position);

	//I^-1 monde = R * I^-1 local * R^T (InverseInertiaTensor reste en coordonnées locales)
	Matrix33 orientationMatrix = this->transformMatrix.getOrientation();
	this->InverseInertiaTensorWorld = orientationMatrix * this->InverseInertiaTensor * orientationMatrix.Transpose();
}

Matrix33 RigidBody::getInverseInertiaTensor()
{
	return this->InverseInertiaTensor;
}

void RigidBody::setInverseInertiaTensor(Matrix33 matrix)
{
	this->InverseInertiaTensor = matrix;
}


void RigidBody::clearAccumulator()
{
	this->setForceAccum(Vecteur3D(0, 0, 0));
	this->setTorqueAccum(Vecteur3D(0, 0, 0));
	

}

float RigidBody::getOuterRadius()
{
	return 0;
}

Matrix33 RigidBody::getInverseInertiaTensorWorld()
{
	return this->InverseInertiaTensorWorld;
}

void RigidBody::setInverseInertiaTensorWorld(Matrix33 matrix)
{
	this->InverseInertiaTensorWorld = matrix;
}

int RigidBody::getShapeID()
{
	return this->shapeID;
}

