#pragma once
#include <iostream>
#include <math.h>
class Vecteur3D
{
	// Attributs
private:
	double x;
	double y;
	double z;
	// Méthodes
public:
	// Constructeurs
	Vecteur3D();
	Vecteur3D(double x, double y, double z);
	// Destructeur
	~Vecteur3D();
	// Accesseurs
	double getX();
	const double Vecteur3D::getX() const;
	double getY();
	const double Vecteur3D::getY() const;
	double getZ();
	const double Vecteur3D::getZ() const;
	// Mutateurs
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	// Autres méthodes
	Vecteur3D add(Vecteur3D q);
	Vecteur3D mul(double k);
	Vecteur3D sub(Vecteur3D q);
	Vecteur3D operator+(Vecteur3D q);
	Vecteur3D operator-(Vecteur3D q);
	Vecteur3D operator*(float k);
	Vecteur3D operator/(float k);
	Vecteur3D operator^(Vecteur3D q);
	double norme();
	float length();
	Vecteur3D normalize();
	float ProduitScalaire(Vecteur3D q);
	bool operator==(const Vecteur3D& v) const;
};
