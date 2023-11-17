#pragma once
#include "Vecteur3D.h"
#include <ofColor.h>


class Particule
{
	int id;
	float rayon = 10;
	float masse = 1;
	ofColor color = ofColor::white;


	// Attributs
	Vecteur3D position;
	Vecteur3D velocite;
	Vecteur3D acceleration;

	// Méthodes
public:
	// Constructeurs
	Particule();
	Particule(int* nbParticles,Vecteur3D position, Vecteur3D velocite, Vecteur3D acceleration, float rayon = 10, float masse = 1, ofColor color = (0,0,0));
	// Destructeur
	~Particule();
	// Accesseurs
	Vecteur3D getPosition() const;
	Vecteur3D getVelocite() const;
	Vecteur3D getAcceleration() const;
	// Mutateurs
	void setPosition(Vecteur3D position);
	void setVelocite(Vecteur3D velocite);
	void setAcceleration(Vecteur3D acceleration);
	// Autres méthodes
	void setRayon(float rayon);
	float getRayon() const;
	void setMasse(float masse);
	float getMasse() const;
	void addAcceleration(Vecteur3D acceleration);
	int getId() const;
	void setId(int id);
	//operator ==
	bool operator==(const Particule& p) const;
	void setColor(ofColor color);
	ofColor getColor() const;



};

