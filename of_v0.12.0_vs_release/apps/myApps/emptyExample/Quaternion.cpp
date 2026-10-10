#include "Quaternion.h"


Quaternion::Quaternion()
{
	// Constructeur par défaut : quaternion identité
	// Le stockage est (w, x, y, z) : values[0] est la partie réelle
	values[0] = 1;
	values[1] = 0;
	values[2] = 0;
	values[3] = 0;
}

Quaternion::Quaternion(double w, double x, double y, double z)
{
	// Constructeur avec paramètres
	values[0] = w;
	values[1] = x;
	values[2] = y;
	values[3] = z;
}

void Quaternion::Normalized()
{
	double norm = sqrt(values[0] * values[0] + values[1] * values[1] + values[2] * values[2] + values[3] * values[3]);
	if (norm == 0) {
		// quaternion nul : on revient à l'identité plutôt que de diviser par 0
		values[0] = 1;
		return;
	}

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


