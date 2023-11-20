#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{
private:
	Vecteur3D m_bodyAnchor;
	RigidBody* m_otherRigidBody = nullptr;
	Vecteur3D m_otherRigidBodyAnchor;

	float m_k;
	float m_restLength;

public:
	SpringForceGenerator(Vecteur3D bodyAnchor, RigidBody* otherRigidBody, Vecteur3D otherRigidBodyAnchor, float k, float restLength);
	~SpringForceGenerator();

	void updateForce(RigidBody* rigidBody);
	Vecteur3D getBodyAnchor();
};

