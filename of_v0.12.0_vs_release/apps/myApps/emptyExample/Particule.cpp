#include "Particule.h"


Particule::Particule()
{
	// Constructeur par défaut
	position = Vecteur3D();
	velocite = Vecteur3D();
	acceleration = Vecteur3D();
}

Particule::Particule(int* nbParticles, Vecteur3D position, Vecteur3D velocite, Vecteur3D acceleration, float rayon, float masse, ofColor color)
{
	// Constructeur avec paramètres
	this->id = *nbParticles;
	(*nbParticles)++;
	this->position = position;
	this->velocite = velocite;
	this->acceleration = acceleration;
	this->rayon = rayon;
	this->masse = masse;
	this->color = color;

}

Particule::~Particule()
{
	// Destructeur
}

Vecteur3D Particule::getPosition() const
{
	// Accesseur
	return position;
}

Vecteur3D Particule::getVelocite() const
{
	// Accesseur
	return velocite;
}

Vecteur3D Particule::getAcceleration() const
{
	// Accesseur
	return acceleration;
}

void Particule::setPosition(Vecteur3D position)
{
	// Mutateur
	
	this->position = position;

	
}

void Particule::setVelocite(Vecteur3D velocite)
{
	// Mutateur
	
	this->velocite = velocite;
	

}

void Particule::setAcceleration(Vecteur3D acceleration)
{
	// Mutateur
	
	this->acceleration = acceleration;
	

}

void Particule::addAcceleration(Vecteur3D acceleration)
{

	this->setAcceleration(this->acceleration + acceleration);
	
	
}

void Particule::setRayon(float rayon)
{
	// Mutateur
	this->rayon = rayon;
}

float Particule::getRayon() const
{
	// Accesseur
	return rayon;
}

void Particule::setMasse(float masse)
{
	// Mutateur
	this->masse = masse;
}

float Particule::getMasse() const
{
	// Accesseur
	return masse;
}

bool Particule::operator==(const Particule& p) const
{
	return (this->position == p.position && this->velocite == p.velocite && this->acceleration == p.acceleration);
}

int Particule::getId() const
{
	return id;
}

void Particule::setId(int id)
{
	this->id = id;
}

void Particule::setColor(ofColor color)
{
	this->color = color;
}

ofColor Particule::getColor() const
{
	return color;
}



