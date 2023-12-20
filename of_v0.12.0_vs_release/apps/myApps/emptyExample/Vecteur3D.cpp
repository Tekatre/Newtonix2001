#include "Vecteur3D.h"

Vecteur3D::Vecteur3D()
{
	// Constructeur par défaut
	x = 0;
	y = 0;
	z = 0;

}

Vecteur3D::Vecteur3D(double x, double y, double z)
{
	// Constructeur avec paramètres
	this->x = x;
	this->y = y;
	this->z = z;
}

Vecteur3D::Vecteur3D(string sexy)
{
	//create random vector
	random_device rd;
	mt19937 gen(rd());
	if (sexy.compare("petit") == 0){
		uniform_real_distribution<> dis(-10, 10);
		this->x = dis(gen);
		this->y = dis(gen);
		this->z = dis(gen);
	}
	else {
		uniform_real_distribution<> dis(-30, 30);
		this->x = dis(gen);
		this->y = dis(gen);
		this->z = dis(gen);
	}
	
	

}

Vecteur3D::~Vecteur3D()
{
	// Destructeur
}

double Vecteur3D::getX()
{
	// Accesseur
	return x;
}

const double Vecteur3D::getX() const
{
	// Accesseur
	return x;
}

double Vecteur3D::getY()
{
	// Accesseur
	return y;
}

const double Vecteur3D::getY() const
{
	// Accesseur
	return y;
}

double Vecteur3D::getZ()
{
	// Accesseur
	return z;
}

const double Vecteur3D::getZ() const
{
	// Accesseur
	return z;
}

void Vecteur3D::setX(double x)
{
	// Mutateur
	this->x = x;
}

void Vecteur3D::setY(double y)
{
	// Mutateur
	this->y = y;
}

void Vecteur3D::setZ(double z)
{
	// Mutateur
	this->z = z;
}

Vecteur3D Vecteur3D::add(Vecteur3D q)
{
	// Addition de deux vecteurs
	Vecteur3D r;
	r.setX(x + q.getX());
	r.setY(y + q.getY());
	r.setZ(z + q.getZ());
	return r;
}

Vecteur3D Vecteur3D::mul(double k)
{
	// Multiplication d'un vecteur par un scalaire
	Vecteur3D r;
	r.setX(k * x);
	r.setY(k * y);
	r.setZ(k * z);
	return r;
}

//define operator - for vector substraction

Vecteur3D Vecteur3D::operator-(Vecteur3D q)
{
	// Substraction de deux vecteurs
	Vecteur3D r;
	r.setX(x - q.getX());
	r.setY(y - q.getY());
	r.setZ(z - q.getZ());
	return r;
}

double Vecteur3D::norme()
{
	// Norme d'un vecteur
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float Vecteur3D::length()
{
	// Norme d'un vecteur
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vecteur3D Vecteur3D::normalize()
{
	// Normalisation d'un vecteur
	Vecteur3D r;
	r.setX(x / norme());
	r.setY(y / norme());
	r.setZ(z / norme());
	return r;
}

Vecteur3D Vecteur3D::operator+(Vecteur3D q)
{
	// Addition de deux vecteurs
	Vecteur3D r;
	r.setX(x + q.getX());
	r.setY(y + q.getY());
	r.setZ(z + q.getZ());
	return r;
}

Vecteur3D Vecteur3D::operator*(float k)
{
	// Multiplication d'un vecteur par un scalaire
	Vecteur3D r;
	r.setX(k * x);
	r.setY(k * y);
	r.setZ(k * z);
	return r;
}

Vecteur3D Vecteur3D::operator/(float k)
{
	// Division d'un vecteur par un scalaire
	Vecteur3D r;
	r.setX(x / k);
	r.setY(y / k);
	r.setZ(z / k);
	return r;
}

Vecteur3D Vecteur3D::operator^(Vecteur3D q)
{
	// Produit vectoriel de deux vecteurs
	Vecteur3D r;
	r.setX(y * q.getZ() - z * q.getY());
	r.setY(z * q.getX() - x * q.getZ());
	r.setZ(x * q.getY() - y * q.getX());
	return r;
}

bool Vecteur3D::operator!=(Vecteur3D q)
{
	if (x == q.getX() && y == q.getY() && z == q.getZ())
	{
		return false ;
	}
	else
	{
		return true;
	}
}

float Vecteur3D::ProduitScalaire(Vecteur3D q)
{
	// Produit scalaire de deux vecteurs
	return x * q.getX() + y * q.getY() + z * q.getZ();

}

Vecteur3D Vecteur3D::sub(Vecteur3D q)
{
	// Substraction de deux vecteurs
	Vecteur3D r;
	r.setX(x - q.getX());
	r.setY(y - q.getY());
	r.setZ(z - q.getZ());
	return r;
}

bool Vecteur3D::operator==(const Vecteur3D& v) const
{
	// Comparaison de deux vecteurs
	return (x == v.x && y == v.y && z == v.z);
}

float Vecteur3D::distance(Vecteur3D q)
{
	// Distance entre deux vecteurs
	return sqrt(pow(x - q.getX(), 2) + pow(y - q.getY(), 2) + pow(z - q.getZ(), 2));
}


void Vecteur3D::setIndex(int index, float value)
{
	// Set value of vector at index
	if (index == 0)
	{
		x = value;
	}
	else if (index == 1)
	{
		y = value;
	}
	else if (index == 2)
	{
		z = value;
	}
	else
	{
		cout << "Error: index out of range" << endl;
	}
	return;
}

float Vecteur3D::getIndex(int index)
{
	// Get value of vector at index
	if (index == 0)
	{
		return x;
	}
	else if (index == 1)
	{
		return y;
	}
	else if (index == 2)
	{
		return z;
	}
	else
	{
		cout << "Error: index out of range" << endl;
		return 0;
	}
}
