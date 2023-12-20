#include "Quaternion.h"


Quaternion::Quaternion()
{
	// Constructeur par défaut
	values[0] = 0;
	values[1] = 0;
	values[2] = 0;
	values[3] = 1;
}

Quaternion::Quaternion(double x, double y, double z, double w)
{
	// Constructeur avec paramètres
	values[0] = x;
	values[1] = y;
	values[2] = z;
	values[3] = w;
}

void Quaternion::Normalized()
{
	double norm = sqrt(values[0] * values[0] + values[1] * values[1] + values[2] * values[2] + values[3] * values[3]);

	values[0] /= norm;
	values[1] /= norm;
	values[2] /= norm;
	values[3] /= norm;
}	

Quaternion Quaternion::operator*(const Quaternion& other) const
{
	Quaternion result;
	result.values[0] = values[0]*other.values[0] - values[1]*other.values[1] - values[2]*other.values[2] - values[3]*other.values[3];
	result.values[1] = values[0]*other.values[1] + values[1]*other.values[0] + values[2]*other.values[3] - values[3]*other.values[2];
	result.values[2] = values[0]*other.values[2] - values[1]*other.values[3] + values[2]*other.values[0] + values[3]*other.values[1];
	result.values[3] = values[0]*other.values[3] + values[1]*other.values[2] - values[2]*other.values[1] + values[3]*other.values[0];
	return result;
}	

Quaternion Quaternion::operator*(double other)
{
	Quaternion result;
	result.values[0] = values[0]*other;
	result.values[1] = values[1]*other;
	result.values[2] = values[2]*other;
	result.values[3] = values[3]*other;
	return result;
}

Quaternion Quaternion::operator+(const Quaternion& other) const
{
	Quaternion result;
	result.values[0] = values[0] + other.values[0];
	result.values[1] = values[1] + other.values[1];
	result.values[2] = values[2] + other.values[2];
	result.values[3] = values[3] + other.values[3];
	return result;
}
//
//void Quaternion::RotateByVector(const Vecteur3D& vector)
//{
//	Quaternion q(0, vector.getX(), vector.getY(), vector.getZ());
//	(*this) = (*this) + (q * (*this));
//}

void Quaternion::UpdateByAngularVelocity(const Vecteur3D& angularVelocity, double duration)
{
	Quaternion result;
	result = (*this) + (Quaternion(0, angularVelocity.getX(), angularVelocity.getY(), angularVelocity.getZ()) * (*this) * (duration/2));
	result.Normalized();
	(*this) = result;
}

const double Quaternion::getW() const
{
	// Accesseur
	return values[0];
}

const double Quaternion::getX() const
{
	// Accesseur
	return values[1];
}

const double Quaternion::getY() const
{
	// Accesseur
	return values[2];
}

const double Quaternion::getZ() const
{
	// Accesseur
	return values[3];
}

Quaternion Quaternion::getConjugate()
{
	Quaternion result;
	result.values[0] = values[0];
	result.values[1] = -values[1];
	result.values[2] = -values[2];
	result.values[3] = -values[3];
	return result;
}

void Quaternion::RotateByVector(const Vecteur3D& vector)
{
	Quaternion q(0, vector.getX(), vector.getY(), vector.getZ());
	(*this) = (*this) + (q * (*this));
}


