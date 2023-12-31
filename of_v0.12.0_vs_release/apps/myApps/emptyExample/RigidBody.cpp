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

	//mise � jour de la position
	this->position = this->position + this->velocity * duration;
	//mise � jour de l'orientation
	this->orientation.UpdateByAngularVelocity(this->rotation, duration);
	//Calculer les valeurs d�riv�es (matrice de transformation et I^-1')
	this->calculateDerivedData();
	//Calculer l'acc�l�ration lin�aire p.. = F/m
	Vecteur3D acceleration = this->forceAccum * this->inverseMass;
	//Calculer l'acc�l�ration angulaire a.. = I^-1' * T
	Vecteur3D angularAcceleration = InverseInertiaTensor * torqueAccum;
	//Mettre � jour la v�locit� lin�aire
	this->velocity = this->velocity*(pow(linearDamping,duration)) + acceleration * duration;
	//Mettre � jour la v�locit� angulaire
	this->rotation = this->rotation * (pow(angularDamping, duration)) + angularAcceleration * duration;
	//R�initialiser les forces et les torques
	this->clearAccumulator();


}

void RigidBody::addForce(const Vecteur3D& force)
{
	this->setForceAccum(this->getForceAccum() + force);
}

void RigidBody::addForceAtPoint(const Vecteur3D& force, const Vecteur3D& point)
{
	//convertir le point en coordonn�es locales
	Vecteur3D localPoint = this->transformMatrix.Inverse() * point;
	//calculer le moment de force
	Vecteur3D torque = localPoint ^ force;

	//ajouter le moment de force
	this->addForceAtBodyPoint(force, point);
}

void RigidBody::addForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& point)
{
	//convertir le point local en coordonn�es globales
	Matrix34 invTransformMatrix = this->transformMatrix;
	Vecteur3D globalPoint = invTransformMatrix * point;
	//ajouter la force
	this->addForce(force);
	//ajouter le moment de force
	Vecteur3D torque = this->getTorqueAccum();
	Vecteur3D newTorque = (Vecteur3D)point ^ force;
	//si le newTorque n'est pas nul
	if(newTorque != Vecteur3D(0, 0, 0))
	{
		//std::cout << "gbkheugi";
	}
	this->setTorqueAccum(this->getTorqueAccum() + newTorque);
}
void RigidBody::calculateDerivedData()
{
	//call each frame to calculate the transform matrix and normalize the orientation

	//this->transformMatrix.setOrientationAndPosition(this->orientation, this->position);


	/*switch (shape)
	{
		case 0:
		
			Matrix33 SphereInertiaTensor;
			SphereInertiaTensor.setValues(0.4f * mass * radius * radius, 0, 0,
				0, 0.4f * mass * radius * radius, 0,
				0, 0, 0.4f * mass * radius * radius);
			InverseInertiaTensor = SphereInertiaTensor.Inverse();
			break;
		
		case 1:
		
			Matrix33 CubeInertiaTensor;
			CubeInertiaTensor.setValues(1.0f / 12.0f * mass * (height * height + radius * radius), 0, 0,
				0, 1.0f / 12.0f * mass * (height * height + radius * radius), 0,
				0, 0, 1.0f / 12.0f * mass * (height * height + height * height));
			InverseInertiaTensor = CubeInertiaTensor.Inverse();
			break;
		

		case 2:
		
			Matrix33 CylinderInertiaTensor;
			CylinderInertiaTensor.setValues(0.083f * mass * height * height + 0.25f * mass * radius * radius, 0, 0,
				0, 0.5f * mass * radius * radius, 0,
				0, 0, 0.083f * mass * height * height + 0.25f * mass * radius * radius);
			InverseInertiaTensor = CylinderInertiaTensor.Inverse();
			break;
		
		default:
			Matrix33 SphereInertiaTensor2;
			SphereInertiaTensor2.setValues(0.4f * mass * radius * radius, 0, 0,
				0, 0.4f * mass * radius * radius, 0,
				0, 0, 0.4f * mass * radius * radius);
			InverseInertiaTensor = SphereInertiaTensor2.Inverse();
		
	}*/






	this->orientation.Normalized();

	//calculate the transform matrix
	this->transformMatrix.setOrientationAndPosition(this->orientation, this->position);
	//std::cout << "41+1";

	//get the 3x3 of transform matrix
	Matrix33 orientationMatrix = this->transformMatrix.getOrientation();
	InverseInertiaTensor = InverseInertiaTensor * orientationMatrix;
	this->InverseInertiaTensorWorld = this->transformMatrix.getOrientation() * this->InverseInertiaTensor * this->transformMatrix.getOrientation().Inverse();
	


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

