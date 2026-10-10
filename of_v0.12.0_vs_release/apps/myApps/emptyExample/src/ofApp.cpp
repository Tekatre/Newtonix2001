#include "ofApp.h"




void ofApp::initializeParticles() {
	//Scene de depart pour bien voir les collisions (touche 'r' pour la relancer)
	//Gravite de 100 unites/s^2 : avec 9.81 et des objets de 50 unites, tout semblait au ralenti
	sceneGravity = new GravityGenerator(Vecteur3D(0, -100, 0));
	ownedForceGenerators.push_back(sceneGravity);

	//Sol : boite statique (masse infinie), dessus a y = -100
	BoxRigidBody* floor = new BoxRigidBody();
	floor->setWidth(1400);
	floor->setHeight(20);
	floor->setDepth(700);
	setupRigidBody(floor, Vecteur3D(0, -110, 0), Vecteur3D(0, 0, 0), 0, ofColor(150, 150, 150));

	//A. Pendule de Newton : 3 spheres suspendues par des ressorts, la premiere est ecartee
	double cradleX[3] = { -341, -300, -259 };
	for (int i = 0; i < 3; i++) {
		SphereRigidBody* sphere = new SphereRigidBody();
		sphere->setRadius(20);
		Vecteur3D anchor(cradleX[i], 200, 0);
		//au repos le ressort est etire de m*g/k = 1*100/30 : y = 200 - 150 - 3.3
		Vecteur3D position = (i == 0) ? Vecteur3D(cradleX[i] - 130, 125, 0) : Vecteur3D(cradleX[i], 46.7, 0);
		setupRigidBody(sphere, position, Vecteur3D(0, 0, 0), 1, ofColor(60, 120, 220));
		addAnchorLink(sphere, Vecteur3D(0, 0, 0), anchor, 30, 150);
	}

	//B. Tour de 3 boites percutee par une sphere lancee
	for (int i = 0; i < 3; i++) {
		BoxRigidBody* box = new BoxRigidBody();
		box->setWidth(50);
		box->setHeight(50);
		box->setDepth(50);
		setupRigidBody(box, Vecteur3D(250, -74 + 51 * i, 0), Vecteur3D(0, 0, 0), 0.5, ofColor(240, 150, 40));
	}
	SphereRigidBody* projectile = new SphereRigidBody();
	projectile->setRadius(15);
	setupRigidBody(projectile, Vecteur3D(50, -20, 0), Vecteur3D(250, 60, 0), 0.5, ofColor(220, 40, 40));

	//C. Deux boites reliees par un ressort accroche a leurs coins (ce qui les fait tourner)
	BoxRigidBody* linkedA = new BoxRigidBody();
	linkedA->setWidth(40);
	linkedA->setHeight(40);
	linkedA->setDepth(40);
	setupRigidBody(linkedA, Vecteur3D(-80, 80, 150), Vecteur3D(0, 0, 0), 0.5, ofColor(60, 180, 90));
	BoxRigidBody* linkedB = new BoxRigidBody();
	linkedB->setWidth(40);
	linkedB->setHeight(40);
	linkedB->setDepth(40);
	setupRigidBody(linkedB, Vecteur3D(80, 80, 150), Vecteur3D(0, 0, 0), 0.5, ofColor(60, 180, 90));
	addSpringLink(linkedA, Vecteur3D(20, 20, 20), linkedB, Vecteur3D(-20, 20, 20), 2, 60);

	//D. Pendule : cylindre accroche par le haut qui vient percuter une boite posee au sol
	CylinderRigidBody* pendulum = new CylinderRigidBody();
	pendulum->setRadius(15);
	pendulum->setHeight(60);
	setupRigidBody(pendulum, Vecteur3D(-200, 70, -150), Vecteur3D(0, 0, 0), 0.5, ofColor(150, 70, 200));
	addAnchorLink(pendulum, Vecteur3D(0, 30, 0), Vecteur3D(0, 250, -150), 20, 250);
	BoxRigidBody* target = new BoxRigidBody();
	target->setWidth(50);
	target->setHeight(50);
	target->setDepth(50);
	setupRigidBody(target, Vecteur3D(60, -74, -150), Vecteur3D(0, 0, 0), 0.5, ofColor(240, 210, 60));
}

void ofApp::setupRigidBody(RigidBody* rb, Vecteur3D position, Vecteur3D velocity, double inverseMass, ofColor color) {
	rb->setPosition(position);
	rb->setVelocity(velocity);
	rb->setInverseMass(inverseMass);
	rb->setLinearDamping(0.9);
	rb->setAngularDamping(0.6);
	rb->setOrientation(Quaternion());
	rb->setRotation(Vecteur3D(0, 0, 0));
	//pas de temps nul : calcule la matrice de transformation et le tenseur d'inertie avant la premiere frame
	rb->integrate(0);

	listRigidBodies.push_back(rb);
	rigidBodyColors.push_back(color);
	if (inverseMass != 0) {
		rigidRegistry->my_RigidRegistry.push_back({ rb, sceneGravity });
	}
}

void ofApp::addAnchorLink(RigidBody* rb, Vecteur3D bodyAnchor, Vecteur3D worldAnchor, float k, float restLength) {
	AnchorForceGenerator* anchorForce = new AnchorForceGenerator(worldAnchor, bodyAnchor, k, restLength);
	ownedForceGenerators.push_back(anchorForce);
	rigidRegistry->my_RigidRegistry.push_back({ rb, anchorForce });
	rigidLinks.push_back({ rb, bodyAnchor, nullptr, worldAnchor });
}

void ofApp::addSpringLink(RigidBody* a, Vecteur3D anchorA, RigidBody* b, Vecteur3D anchorB, float k, float restLength) {
	//un generateur par corps : chacun subit la force du ressort
	SpringForceGenerator* forceOnA = new SpringForceGenerator(anchorA, b, anchorB, k, restLength);
	SpringForceGenerator* forceOnB = new SpringForceGenerator(anchorB, a, anchorA, k, restLength);
	ownedForceGenerators.push_back(forceOnA);
	ownedForceGenerators.push_back(forceOnB);
	rigidRegistry->my_RigidRegistry.push_back({ a, forceOnA });
	rigidRegistry->my_RigidRegistry.push_back({ b, forceOnB });
	rigidLinks.push_back({ a, anchorA, b, anchorB });
}



//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	//fond rose = pas de pause automatique a la collision (touche 'e' pour basculer)
	ofBackground(230, 150, 200);
	//resolutions des maillages en cache utilises par ofDrawSphere / ofDrawCylinder
	ofSetSphereResolution(24);
	ofSetCylinderResolution(32, 1, 1);
	//restartButton.addListener(this, &ofApp::restartButtonPressed);
	//addParticleButton.addListener(this, &ofApp::addParticleButtonPressed);
	

	initializeParticles();
	//camera placee pour voir toute la scene (sol de 1400 x 700)
	cam.setTarget(glm::vec3(0, 0, 0));
	cam.setPosition(0, 450, 1000);
	cam.lookAt(glm::vec3(0, 0, 0));
	ofDisableAlphaBlending();
	ofEnableDepthTest();
	light.enable();
	light.setPosition(ofVec3f(100, 100, 200));
	light.lookAt(ofVec3f(0, 0, 0));

	//gui.setup();
	//modify gui size
	/*gui.setSize(300, 300);
	gui.add(p2x.setup("Position (x) de la balle bleue", 0.0, -100.0, 100.0));
	gui.add(p2y.setup("Position (y) de la balle bleue", 30.0, -100.0, 100.0));
	gui.add(p2z.setup("Position (z) de la balle bleue", 0.0, -100.0, 100.0));
	gui.add(v2x.setup("Vitesse (x) de la balle bleue", 70.0, -100.0, 100.0));
	gui.add(v2y.setup("Vitesse (y) de la balle bleue", 0.0, -100.0, 100.0));
	gui.add(v2z.setup("Vitesse (z) de la balle bleue", 70.0, -100.0, 100.0));

	gui.add(addParticleButton.setup("add particle"));
	gui.add(restartButton.setup("restart"));*/


}

//--------------------------------------------------------------
void ofApp::update() {
	if (!paused) {
		return;
	}
	t = ofGetLastFrameTime()*accelerator;

	//cout << "Number of particles : " << listParticules.size() << endl;


	registry->updateForces(t);
	rigidRegistry->updateForces(t);
	particulesAnchor.clear();
	
	if (listParticules.size() != 0) {
		for (int m = 0; m < listParticules.size() - 1; m++) {
			for (int n = m + 1; n < listParticules.size(); n++) {
				if (collisionDetector.checkCollision(listParticules[m], listParticules[n])) {

					ParticleContact sphereContact;
					sphereContact.particle[0] = listParticules[m];
					sphereContact.particle[1] = listParticules[n];
					sphereContact.restitution = 0.8;
					sphereContact.penetration = listParticules[m]->getRayon() + listParticules[n]->getRayon() - (listParticules[m]->getPosition() - listParticules[n]->getPosition()).norme();
					sphereContact.contactNormal = (listParticules[m]->getPosition() - listParticules[n]->getPosition()) * (1 / (listParticules[m]->getPosition() - listParticules[n]->getPosition()).norme());
					//add sphereContact to contacts (contacts is not a vector)
					if (numberOfContacts < maxCollisions) {
						contacts[numberOfContacts] = sphereContact;
						numberOfContacts++;
					}
				}
			}
		}
	}
	

	for (int k = 0; k < numberOfCables; k++) {
		//addcontact
		numberOfContacts += cables[k]->addContact(contacts, numberOfContacts);
	}
	for (int l = 0; l < numberOfRods; l++) {
		//addcontact
		numberOfContacts += rods[l]->addContact(contacts, numberOfContacts);
	}
	/*if (numberOfContacts > 0) {
		cout << "Number of contacts : " << numberOfContacts << endl;
	}*/

	resolver->resolveContacts(contacts, numberOfContacts, t);
	numberOfContacts = 0;

	


	







	i = Integrateur();
	for (int k = 0; k < listParticules.size(); k++) {
		i.integrer(listParticules[k], t);
		trails.push_back(*listParticules[k]);
	}
	for (int l = 0; l < listRigidBodies.size(); l++) {
		//cout << t;
		i.integrer(listRigidBodies[l], t);
	}

	
	
	BSP* bsp = new BSP();
	bsp->GenerateBSP(listRigidBodies);

	vector<RigidContact*> rigidContacts;
	rigidContactGenerator->CreateContact(bsp);
	rigidContacts = rigidContactGenerator->getContacts();
	numberOfRigidContacts = rigidContacts.size();
	if (pauseAtCollision && numberOfRigidContacts != 0) {
		paused = !paused;
	}
	rigidResolver->resolveContacts(rigidContacts, numberOfRigidContacts, t, pauseAtCollision);

	numberOfRigidContacts = 0;
	rigidContactGenerator->clearContacts();
	rigidContacts.clear();
	delete bsp;



}

void ofApp::restartButtonPressed() {
	//supprime tous les corps rigides, liens et generateurs, puis recree la scene de depart
	rigidRegistry->my_RigidRegistry.clear();
	for (RigidBody* rb : listRigidBodies) {
		delete rb;
	}
	listRigidBodies.clear();
	rigidBodyColors.clear();
	rigidLinks.clear();
	for (ForceGenerator* fg : ownedForceGenerators) {
		delete fg;
	}
	ownedForceGenerators.clear();
	sceneGravity = nullptr;

	initializeParticles();
}







//--------------------------------------------------------------
void ofApp::draw() {
	//Draw a point at the position of particule p
	cam.begin();

	/*ofSetColor(0, 0, 0);
	ofDrawBox(ground.getX(), ground.getY(), ground.getZ(), ground.width, ground.height, ground.depth);*/
	ofSetColor(255, 255, 255);
	ofSetColor(255, 0, 0);
	ofDrawArrow(glm::vec3(0, 0, 0), glm::vec3(300, 0, 0), 10);
	ofSetColor(0, 255, 0);
	ofDrawArrow(glm::vec3(0, 0, 0), glm::vec3(0, 300, 0), 10);
	ofSetColor(0, 0, 255);
	ofDrawArrow(glm::vec3(0, 0, 0), glm::vec3(0, 0, 300), 10);
	//ofSetColor(0, 255, 255);
	//ofDrawArrow(glm::vec3(0, -125, 0), glm::vec3(0, -75, 0), 10);
	/*ofSetColor(150,0,160);
	ofDrawSphere(p1.getPosition().getX(), p1.getPosition().getY(), p1.getPosition().getZ(), 10);*/

	//draw the rigid body
	
	for (int i = 0; i < listRigidBodies.size(); i++) {
		ofSetColor(i < rigidBodyColors.size() ? rigidBodyColors[i] : ofColor::white);
		//draw a box with the position and the ORIENTATION of the rigid body using ofBoxPrimitive*

		//if listrigidbody[i] is a type BoxRigidBody

		//On place le repere du corps (position + orientation) puis on dessine avec ofDrawBox/Sphere/Cylinder,
		//qui reutilisent un maillage en cache. Creer un ofXxxPrimitive a chaque image regenerait tout le
		//maillage a chaque frame (tres couteux, surtout le cylindre en resolution 50x50x50).
		RigidBody* body = listRigidBodies[i];
		Quaternion q = body->getOrientation();
		ofPushMatrix();
		ofTranslate(body->getPosition().getX(), body->getPosition().getY(), body->getPosition().getZ());
		ofMultMatrix(glm::mat4_cast(glm::quat(q.getW(), q.getX(), q.getY(), q.getZ())));

		if (body->getShapeID() == 1) {
			BoxRigidBody* box = static_cast<BoxRigidBody*>(body);
			ofDrawBox(0, 0, 0, box->getWidth(), box->getHeight(), box->getDepth());
		}
		else if (body->getShapeID() == 3) {
			SphereRigidBody* sphere = static_cast<SphereRigidBody*>(body);
			ofDrawSphere(0, 0, 0, sphere->getRadius());
		}
		else if (body->getShapeID()== 2) {
			CylinderRigidBody* cylinder = static_cast<CylinderRigidBody*>(body);
			ofDrawCylinder(0, 0, 0, cylinder->getRadius(), cylinder->getHeight());
		}
		else {
			//do nothing
		}
		ofPopMatrix();





		
		
		

		
		//texture.bind();
			
		//texture.unbind();
		
	}

//draw the anchor of the rigid body
	for (int i = 0; i < particulesAnchor.size(); i++) {
		ofSetColor(255, 255, 0);
		ofDrawSphere(particulesAnchor[i].getPosition().getX(), particulesAnchor[i].getPosition().getY(), particulesAnchor[i].getPosition().getZ(), 2);
	}

	//draw the springs between the rigid bodies (or between a body and a fixed anchor)
	for (int k = 0; k < rigidLinks.size(); k++) {
		Vecteur3D pointA = rigidLinks[k].a->getTransformMatrix() * rigidLinks[k].anchorA;
		Vecteur3D pointB = rigidLinks[k].anchorB;
		if (rigidLinks[k].b != nullptr) {
			pointB = rigidLinks[k].b->getTransformMatrix() * rigidLinks[k].anchorB;
		}
		else {
			//point d'ancrage fixe
			ofSetColor(40, 40, 40);
			ofDrawBox(pointB.getX(), pointB.getY(), pointB.getZ(), 8);
		}
		ofSetColor(40, 40, 40);
		ofDrawLine(pointA.getX(), pointA.getY(), pointA.getZ(), pointB.getX(), pointB.getY(), pointB.getZ());
	}
	

	//Draw trails of particles
	/*for (int i = 0; i < trails.size(); i++) {


		ofSetColor(30, 150, 160);

		ofDrawSphere(trails[i].getPosition().getX(), trails[i].getPosition().getY(), trails[i].getPosition().getZ(), 1);
	}*/

	for (int k = 0; k < listParticules.size(); k++) {
		ofSetColor(listParticules[k]->getColor());
		ofDrawSphere(listParticules[k]->getPosition().getX(), listParticules[k]->getPosition().getY(), listParticules[k]->getPosition().getZ(), listParticules[k]->getRayon());
	}

	//Draw a line between the two particles
	ofSetColor(0, 255, 0);
	for (int i = 0; i < numberOfCables; i++) {
		ParticleCable* cable = cables[i];
		ofDrawLine(cable->particle[0]->getPosition().getX(), cable->particle[0]->getPosition().getY(), cable->particle[0]->getPosition().getZ(), cable->particle[1]->getPosition().getX(), cable->particle[1]->getPosition().getY(), cable->particle[1]->getPosition().getZ());
	}
	ofSetColor(255, 0, 0);
	for (int i = 0; i < numberOfRods; i++) {
		ParticleRod* rod = rods[i];
ofDrawLine(rod->particle[0]->getPosition().getX(), rod->particle[0]->getPosition().getY(), rod->particle[0]->getPosition().getZ(), rod->particle[1]->getPosition().getX(), rod->particle[1]->getPosition().getY(), rod->particle[1]->getPosition().getZ());
	}

	/*ofSetColor(0, 0, 255);
	for (int i = 0; i < anchorsLink.size(); i++) {
		ofDrawLine(anchorsLink[i].first.getPosition().getX(), anchorsLink[i].first.getPosition().getY(), anchorsLink[i].first.getPosition().getZ(), anchorsLink[i].second.getX(), anchorsLink[i].second.getY(), anchorsLink[i].second.getZ());
	}*/



	cam.end();

	//affichage des performances
	ofDisableDepthTest();
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("FPS : " + ofToString(ofGetFrameRate(), 0) + "   Corps : " + ofToString(listRigidBodies.size()) + "   Vitesse : x" + ofToString(accelerator) + (paused ? "" : "   [EN PAUSE]"), 10, 20);
	ofDrawBitmapString("Espace : lancer/pause   R : relancer la scene   A : ajouter un corps   E : pause a chaque collision   Haut/Bas : vitesse", 10, 38);
	ofEnableDepthTest();

	//gui.draw();
}


void ofApp::addRigidBody() {
	//forme, taille et masse aleatoires, lachee au-dessus du centre de la scene
	RigidBody* rb;
	int randshape = rand() % 3 + 1;
	if (randshape == 1) {
		BoxRigidBody* box = new BoxRigidBody();
		box->setDepth(rand() % 50 + 10);
		box->setHeight(rand() % 50 + 10);
		box->setWidth(rand() % 50 + 10);
		rb = box;
	}
	else if (randshape == 2) {
		CylinderRigidBody* cylinder = new CylinderRigidBody();
		cylinder->setRadius(rand() % 20 + 15);
		cylinder->setHeight(rand() % 40 + 20);
		rb = cylinder;
	}
	else {
		SphereRigidBody* sphere = new SphereRigidBody();
		sphere->setRadius(rand() % 30 + 10);
		rb = sphere;
	}
	float mass = rand() % 5 + 10;
	setupRigidBody(rb, Vecteur3D("random") + Vecteur3D(0, 150, 0), Vecteur3D("random"), 1 / mass, ofColor::fromHsb(rand() % 256, 160, 230));
	rb->setRotation(Vecteur3D("petit"));

	DragForceGenerator* rgdrag = new DragForceGenerator();
	ownedForceGenerators.push_back(rgdrag);
	rigidRegistry->my_RigidRegistry.push_back({ rb,rgdrag });

	cout << "Mass : " << mass << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	//quand on appuie sur espace, mets un pause la boucle
	if (key == ' ') {
		paused = !paused;
	}

	if (key == 'a') {
		addRigidBody();
	}

	if (key == 'e') {
		pauseAtCollision = !pauseAtCollision;
		if (pauseAtCollision) {
			ofBackground(230, 230, 250);
		}
		else {
			ofBackground(230, 150, 200);
		}

	}


	if (key == OF_KEY_UP) {
		accelerator++;
	}

	if (key == OF_KEY_DOWN && accelerator > 1) {
		//un accelerateur <= 0 donnerait un pas de temps nul ou negatif
		accelerator--;
	}

	if (key == OF_KEY_LEFT) {
		for (int i = 0; i < listParticules.size(); i++) {
			listParticules[i]->setVelocite(listParticules[i]->getVelocite() + Vecteur3D(-50, 0, 0));
		}
	}

	if (key == OF_KEY_RIGHT) {
		for (int i = 0; i < listParticules.size(); i++) {
			listParticules[i]->setVelocite(listParticules[i]->getVelocite() + Vecteur3D(50, 0, 0));
		}
	}

	if (key == 'r') {
		restartButtonPressed();
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
//void ofApp::mouseEntered(int x, int y) {
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseExited(int x, int y) {
//
//}
//
////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h) {
//
//}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

