#pragma once
#include "Vecteur3D.h"

class Quaternion
{
private:
		double values[4];
	public:
		Quaternion();
		Quaternion(double w, double x, double y, double z);	
		void Normalized();
		Quaternion operator*(const Quaternion& other) const;
		Quaternion operator+(const Quaternion& other) const;
		Vecteur3D operator*(const Vecteur3D& other) const;
		void RotateByVector(const Vecteur3D& vector);
		void UpdateByAngularVelocity(const Vecteur3D& angularVelocity, double duration);
		const double getW() const;
		const double getX() const;
		const double getY() const;
		const double getZ() const;
		Quaternion operator*(double other);

		Quaternion getConjugate();
};

