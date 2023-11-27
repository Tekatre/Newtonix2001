#pragma once
#include "Vecteur3D.h"
#include "Quaternion.h"
#include "Matrix33.h"

class Matrix34
{
	private:
	double values[12];
public:
	Matrix34 operator*(const Matrix34& other) const;
	Vecteur3D operator*(const Vecteur3D& vector) const;
	Matrix34 Inverse();
	void setOrientationAndPosition(const Quaternion& q, const Vecteur3D& pos);
	Vecteur3D TransformPosition(const Vecteur3D& vector);
	Vecteur3D TransformDirection(const Vecteur3D& vector);
	Matrix33 getOrientation();
};

