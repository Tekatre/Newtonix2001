#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(Vecteur3D bodyAnchor, RigidBody* otherRigidBody, Vecteur3D otherRigidBodyAnchor, float k, float restLength)
{
	this->m_bodyAnchor = bodyAnchor;
	this->m_otherRigidBody = otherRigidBody;
	this->m_otherRigidBodyAnchor = otherRigidBodyAnchor;
	this->m_k = k;
	this->m_restLength = restLength;

}

SpringForceGenerator::~SpringForceGenerator()
{
}

void SpringForceGenerator::updateForce(RigidBody* rigidBody)
{
	Vecteur3D d = rigidBody->getTransformMatrix()* m_bodyAnchor - m_otherRigidBody->getTransformMatrix() * m_otherRigidBodyAnchor;
	Vecteur3D dir = d / d.norme();
	Vecteur3D force = dir.mul((-m_k * rigidBody->getInverseMass()) * (d.norme() - m_restLength));
	rigidBody->addForceAtBodyPoint(force, m_bodyAnchor);
	//rigidBody->addForce(force);
}

Vecteur3D SpringForceGenerator::getBodyAnchor()
{
	return m_bodyAnchor;
}