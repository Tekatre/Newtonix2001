#pragma once
#include "Vecteur3D.h"

class Quaternion
{
private:
		double values[4];
	public:
		Quaternion();
		Quaternion(double x, double y, double z, double w);	
		void Normalized();
		Quaternion operator*(const Quaternion& other) const;
		Quaternion operator+(const Quaternion& other) const;
		void RotateByVector(const Vecteur3D& vector);
		void UpdateByAngularVelocity(const Vecteur3D& angularVelocity, double duration);
		const double Quaternion::getW() const;
		const double Quaternion::getX() const;
		const double Quaternion::getY() const;
		const double Quaternion::getZ() const;
		Quaternion operator*(double other);
};

