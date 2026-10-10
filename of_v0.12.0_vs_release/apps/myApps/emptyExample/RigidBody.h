#pragma once

#include "Vecteur3D.h"
#include "Quaternion.h"
#include "Matrix34.h"
#include "Matrix33.h"
#include <glm/fwd.hpp>


class RigidBody 
{
private:


	int shapeID = 0;

	double inverseMass = 1;
	double linearDamping = 1;
	double angularDamping = 1;
	Vecteur3D position;
	Vecteur3D velocity;

	Vecteur3D forceAccum;
	Vecteur3D torqueAccum;




	Quaternion orientation;
	Vecteur3D rotation;
	Matrix34 transformMatrix;
	Matrix33 InverseInertiaTensor;
	Matrix33 InverseInertiaTensorWorld;

public :

	RigidBody();
	virtual ~RigidBody();
	void integrate(double duration);
	double getInverseMass();
	void setInverseMass(double mass);
	double getLinearDamping();
	void setLinearDamping(double damping);
	double getAngularDamping();
	void setAngularDamping(double damping);
	Vecteur3D getPosition();
	void setPosition(Vecteur3D pos);
	Vecteur3D getVelocity();
	void setVelocity(Vecteur3D vel);
	Vecteur3D getForceAccum();
	void setForceAccum(Vecteur3D force);
	Vecteur3D getTorqueAccum();	
	void setTorqueAccum(Vecteur3D torque);
	Quaternion getOrientation();
	void setOrientation(Quaternion q);
	Vecteur3D getRotation();
	void setRotation(Vecteur3D rot);
	Matrix34 getTransformMatrix();
	void setTransformMatrix(Matrix34 matrix);
	Matrix33 getInverseInertiaTensor();
	void setInverseInertiaTensor(Matrix33 matrix);

	virtual float getOuterRadius();

	Matrix33 getInverseInertiaTensorWorld();
	void setInverseInertiaTensorWorld(Matrix33 matrix);

	virtual int getShapeID();

	void addForce(const Vecteur3D& force);
	void addForceAtPoint(const Vecteur3D& force, const Vecteur3D& point);
	void addForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& point);
	void clearAccumulator();

protected:
	// Met a jour la matrice de transformation et le tenseur d'inertie inverse en coordonnees monde
	// a partir du tenseur local. Les classes filles definissent le tenseur local puis appellent cette methode.
	virtual void calculateDerivedData();
};

