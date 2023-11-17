//#pragma once
#include "ofMain.h"
//#include "ofxGui/src/ofxGui.h"
//#include "ofParameter.h"
//#include "ofxGui.h"
#include "../Vecteur3D.h"
#include "../Particule.h"
#include "../Integrateur.h"
#include "../Collision.h"
#include "../Ground.h"
#include "../ParticleContactGenerator.h"
#include "../ParticleCable.h"
#include "../ParticleForceGenerator.h"
#include "../ParticleGravity.h"

#include "../ParticleRod.h"

#include "../ParticleDrag.h"
#include "../ParticleSpring.h"
#include "../ParticleAnchorSpring.h"
#include "../ParticleForceRegistry.h"

#include "../RigidForceRegistry.h"
#include "../ParticleContactResolver.h"
#include "../RigidBody.h"
#include "../GravityForceGenerator.h"
#include "../AnchorForceGenerator.h"

class ofApp : public ofBaseApp {
public:


	bool paused = false ;

	//list of particles
	const int maxCollisions = 100;

	ParticleForceRegistry* registry = new ParticleForceRegistry;
	RigidForceRegistry* rigidRegistry= new RigidForceRegistry;
	vector<Particule*> listParticules;
	vector<RigidBody*> listRigidBodies;
	int* numberOfParticles= new int(0);
	vector<Particule> trails;
	ParticleContactResolver* resolver = new ParticleContactResolver();

	Vecteur3D gravite;
	double t;
	Integrateur i;

	ofEasyCam cam;

	Collision collisionDetector;
	ParticleContact* contacts = new ParticleContact();
	ParticleCable** cables = new ParticleCable*;
	ParticleRod** rods = new ParticleRod*;
	int numberOfCables = 0;


	vector<ParticleSpring> springs;
	int numberOfContacts = 0;

	int numberOfRods = 0;
	int numberOfSprings = 0;
	vector<std::pair<Particule, Vecteur3D>> anchorsLink;

	

	Ground ground;






	void setup();
	void update();
	void draw();
	void initializeParticles();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void restartButtonPressed();
	void addParticleButtonPressed();
	void addCableButtonPressed();
	void addRodButtonPressed();






	//ofxPanel gui;

	//ofxFloatSlider p2x;
	//ofxFloatSlider p2y;
	//ofxFloatSlider p2z;
	//ofxFloatSlider v2x;
	//ofxFloatSlider v2y;
	//ofxFloatSlider v2z;

	//ofxButton restartButton;
	//ofxButton addParticleButton;
};
