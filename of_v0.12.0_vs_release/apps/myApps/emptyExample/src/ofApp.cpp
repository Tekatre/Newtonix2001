#include "ofApp.h"




void ofApp::initializeParticles() {
	gravite = Vecteur3D(0, -9.8, 0);
	ParticleGravity* Pgravity = new ParticleGravity();
	ParticleDrag* Pdrag = new ParticleDrag();


	BoxRigidBody * rb1 = new BoxRigidBody();
	rb1->setLinearDamping(0.95);
	rb1->setAngularDamping(0.5);
	rb1->setPosition(Vecteur3D(-100, 0, 0));
	rb1->setVelocity(Vecteur3D(-30, 0, 0));
	rb1->setForceAccum(Vecteur3D(0, 0, 0));
	rb1->setTorqueAccum(Vecteur3D(0, 0, 0));
	rb1->setInverseMass(1);
	rb1->setDepth(50);
	rb1->setHeight(50);
	rb1->setWidth(50);
	Quaternion q = Quaternion(1, 0, 0, 0);
	q.Normalized();
	rb1->setOrientation(q);
	rb1->setRotation(Vecteur3D(0,0, 0));
	Matrix34 tr;
	tr.setOrientationAndPosition(q, rb1->getPosition());
	rb1->setTransformMatrix(tr);
	

	/*Particule* particuletest = new Particule(numberOfParticles,Vecteur3D(-75,0,0), Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0),10, 1, ofColor::yellow);
	listParticules.push_back(particuletest);*/
	GravityGenerator* rggravity = new GravityGenerator();
	AnchorForceGenerator* rganchor = new AnchorForceGenerator(Vecteur3D(0, 0, 0), Vecteur3D(0,0,0),3,100);

	rigidRegistry->my_RigidRegistry.push_back({ rb1,rggravity });
	//rigidRegistry->my_RigidRegistry.push_back({ rb1,rganchor });


	




	BoxRigidBody* rb2 = new BoxRigidBody();
	rb2->setInverseMass(1);
	rb2->setLinearDamping(0.95);
	rb2->setAngularDamping(0.5);
	rb2->setPosition(Vecteur3D(-250, 0, 0));
	rb2->setVelocity(Vecteur3D(30, 0, 0));
	rb2->setForceAccum(Vecteur3D(0, 0, 0));
	rb2->setTorqueAccum(Vecteur3D(0, 0, 0));
	rb2->setInverseMass(0.5);
	rb2->setHeight(50);
	rb2->setWidth(50);
	rb2->setDepth(50);
	Quaternion q2 = Quaternion(1, 0, 0, 0);
	q2.Normalized();
	rb2->setOrientation(q2);
	rb2->setRotation(Vecteur3D(0, 2, 1));
	tr.setOrientationAndPosition(q2, rb2->getPosition());
	rb2->setTransformMatrix(tr);

	rigidRegistry->my_RigidRegistry.push_back({ rb2,rggravity });


	SpringForceGenerator* springForce1 = new SpringForceGenerator(Vecteur3D(20,25,15), rb2, Vecteur3D(0, 0, 0), 3, 100);
	SpringForceGenerator* springForce2 = new SpringForceGenerator(Vecteur3D(0, 0, 0), rb1, Vecteur3D(20,25, 15),3 , 100);
	//rigidRegistry->my_RigidRegistry.push_back({ rb1,springForce1 });
	//rigidRegistry->my_RigidRegistry.push_back({ rb2,springForce2 });
	
	
	listRigidBodies.push_back(rb1);
	listRigidBodies.push_back(rb2);

	/*CylinderRigidBody* dragRB = new CylinderRigidBody();
	dragRB->setInverseMass(0.05f);
	dragRB->setLinearDamping(0.95);
	dragRB->setAngularDamping(0.5);
	dragRB->setPosition(Vecteur3D(400, 0, 0));
	dragRB->setVelocity(Vecteur3D(50, 50, 0));
	dragRB->setForceAccum(Vecteur3D(0, 0, 0));
	dragRB->setTorqueAccum(Vecteur3D(0, 0, 0));
	dragRB->setRadius(20);
	dragRB->setHeight(50);
	Quaternion q3 = Quaternion(1, 0, 0, 0);
	q3.Normalized();
	dragRB->setOrientation(q3);
	dragRB->setRotation(Vecteur3D(0, 0, 0));
	tr.setOrientationAndPosition(q3, dragRB->getPosition());
	dragRB->setTransformMatrix(tr);

	rigidRegistry->my_RigidRegistry.push_back({ dragRB,rggravity });

	DragForceGenerator* dragForce = new DragForceGenerator();
	rigidRegistry->my_RigidRegistry.push_back({ dragRB,dragForce });

	listRigidBodies.push_back(dragRB);


	CylinderRigidBody* notDragRB = new CylinderRigidBody();
	notDragRB->setInverseMass(0.05f);
	notDragRB->setLinearDamping(0.95);
	notDragRB->setAngularDamping(0.5);
	notDragRB->setPosition(Vecteur3D(400, 0, 100));
	notDragRB->setVelocity(Vecteur3D(50, 50, 0));
	notDragRB->setForceAccum(Vecteur3D(0, 0, 0));
	notDragRB->setTorqueAccum(Vecteur3D(0, 0, 0));
	notDragRB->setRadius(20);
	notDragRB->setHeight(50);
	notDragRB->setOrientation(q3);
	notDragRB->setRotation(Vecteur3D(0, 0, 0));
	tr.setOrientationAndPosition(q3, notDragRB->getPosition());
	notDragRB->setTransformMatrix(tr);

	rigidRegistry->my_RigidRegistry.push_back({ notDragRB,rggravity });

	listRigidBodies.push_back(notDragRB);*/
}



//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(230, 230, 250);
	//restartButton.addListener(this, &ofApp::restartButtonPressed);
	//addParticleButton.addListener(this, &ofApp::addParticleButtonPressed);
	

	initializeParticles();
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

	


	BSP* bsp = new BSP();
	bsp->GenerateBSP(listRigidBodies);
	
	vector<RigidContact*> rigidContacts;
	rigidContactGenerator->CreateContact(bsp);
	rigidContacts = rigidContactGenerator->getContacts();
	numberOfRigidContacts=rigidContacts.size();
 	if (pauseAtCollision && numberOfRigidContacts != 0) {
		paused = !paused;
	}
	rigidResolver->resolveContacts(rigidContacts, numberOfRigidContacts, t, pauseAtCollision);

	numberOfRigidContacts = 0;
	rigidContactGenerator->clearContacts();
	rigidContacts.clear(); 







	i = Integrateur();
	for (int k = 0; k < listParticules.size(); k++) {
		i.integrer(listParticules[k], t);
		trails.push_back(*listParticules[k]);
	}
	for (int l = 0; l < listRigidBodies.size(); l++) {
		//cout << t;
		i.integrer(listRigidBodies[l], t);
	}

	
	




}

void ofApp::restartButtonPressed() {


	//listParticules.clear();
	//trails.clear();
	//numberOfContacts = 0;

	//registry->my_registry.clear();
	//springs.clear();
	//anchorsLink.clear();
	//numberOfParticles = 0;
	//numberOfCables = 0;
	//numberOfRods = 0;
	//numberOfSprings = 0;

	//initializeParticles();





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
		ofSetColor(255, 255, 255);
		//draw a box with the position and the ORIENTATION of the rigid body using ofBoxPrimitive*

		//if listrigidbody[i] is a type BoxRigidBody

		if (listRigidBodies[i]->getShapeID() == 1) {
			BoxRigidBody* box = static_cast<BoxRigidBody*>(listRigidBodies[i]);
			ofBoxPrimitive boxPrimitive;
			boxPrimitive.setHeight(box->getHeight());
			boxPrimitive.setWidth(box->getWidth());
			boxPrimitive.setDepth(box->getDepth());
			boxPrimitive.setPosition(box->getPosition().getX(), box->getPosition().getY(), box->getPosition().getZ());
			boxPrimitive.setOrientation(glm::quat(box->getOrientation().getW(), box->getOrientation().getX(), box->getOrientation().getY(), box->getOrientation().getZ()));
			boxPrimitive.draw();
		}
		else if (listRigidBodies[i]->getShapeID() == 3) {
			SphereRigidBody* sphere = static_cast<SphereRigidBody*>(listRigidBodies[i]);
			ofSpherePrimitive spherePrimitive;
			spherePrimitive.setRadius(sphere->getOuterRadius());
			spherePrimitive.setPosition(sphere->getPosition().getX(), sphere->getPosition().getY(), sphere->getPosition().getZ());
			spherePrimitive.setOrientation(glm::quat(sphere->getOrientation().getW(), sphere->getOrientation().getX(), sphere->getOrientation().getY(), sphere->getOrientation().getZ()));
			spherePrimitive.draw();
		}
		else if (listRigidBodies[i]->getShapeID()== 2) {
			CylinderRigidBody* cylinder = static_cast<CylinderRigidBody*>(listRigidBodies[i]);
			ofCylinderPrimitive cylinderPrimitive;
			cylinderPrimitive.setResolution(50, 50, 50);
			cylinderPrimitive.setRadius(cylinder->getOuterRadius());
			cylinderPrimitive.setHeight(cylinder->getHeight());
			cylinderPrimitive.setResolutionCap(50);
			cylinderPrimitive.setPosition(cylinder->getPosition().getX(), cylinder->getPosition().getY(), cylinder->getPosition().getZ());
			cylinderPrimitive.setOrientation(glm::quat(cylinder->getOrientation().getW(), cylinder->getOrientation().getX(), cylinder->getOrientation().getY(), cylinder->getOrientation().getZ()));
			cylinderPrimitive.draw();
		}
		else {
			//do nothing
		}





		
		
		

		
		//texture.bind();
			
		//texture.unbind();
		
	}

//draw the anchor of the rigid body
	for (int i = 0; i < particulesAnchor.size(); i++) {
		ofSetColor(255, 255, 0);
		ofDrawSphere(particulesAnchor[i].getPosition().getX(), particulesAnchor[i].getPosition().getY(), particulesAnchor[i].getPosition().getZ(), 2);
	}

	for (int k = 0; k < anchorsLinkRigid.size(); k++) {
		ofSetColor(255, 255, 0);
		Vecteur3D pos= listRigidBodies[0]->getTransformMatrix()* Vecteur3D(0, 30, 40);
		ofDrawLine(pos.getX(), pos.getY(),pos.getZ(), anchorsLinkRigid[k].second.getX(), anchorsLinkRigid[k].second.getY(), anchorsLinkRigid[k].second.getZ());
		
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

	//gui.draw();
}


void ofApp::addRigidBody() {

	int randshape = rand() % 3 + 1;
	if (randshape == 1) {
		BoxRigidBody* rb = new BoxRigidBody();
		rb->setLinearDamping(0.95);
		rb->setAngularDamping(0.5);
		rb->setPosition(Vecteur3D("random"));
		rb->setVelocity(Vecteur3D("random"));
		rb->setForceAccum(Vecteur3D(0, 0, 0));
		rb->setTorqueAccum(Vecteur3D(0, 0, 0));
		float mass = rand() % 5 + 10;
		rb->setInverseMass(1 / mass);
		rb->setDepth(rand() % 50 + 10);
		rb->setHeight(rand() % 50 + 10);
		rb->setWidth(rand() % 50 + 10);
		Quaternion q = Quaternion(1, 0, 0, 0);
		q.Normalized();
		rb->setOrientation(q);
		rb->setRotation(Vecteur3D("petit"));
		Matrix34 tr;
		tr.setOrientationAndPosition(q, rb->getPosition());
		rb->setTransformMatrix(tr);

		cout << "Mass : " << 1.0f/rb->getInverseMass() << endl;

		GravityGenerator* rggravity = new GravityGenerator();
		DragForceGenerator* rgdrag = new DragForceGenerator();
		rigidRegistry->my_RigidRegistry.push_back({ rb,rggravity });
		rigidRegistry->my_RigidRegistry.push_back({ rb,rgdrag });
		listRigidBodies.push_back(rb);
	}
	else if (randshape == 2) {
		CylinderRigidBody* rb = new CylinderRigidBody();
		rb->setLinearDamping(0.95);
		rb->setAngularDamping(0.5);
		rb->setPosition(Vecteur3D("random"));
		rb->setVelocity(Vecteur3D("random"));
		rb->setForceAccum(Vecteur3D(0, 0, 0));
		rb->setTorqueAccum(Vecteur3D(0, 0, 0));
		float mass = rand() % 5 + 10;
		rb->setInverseMass(1 / mass);
		rb->setRadius(rand() % 20 + 15);
		rb->setHeight(rand() % 40 + 20);
		
		Quaternion q = Quaternion(1, 0, 0, 0);
		q.Normalized();
		rb->setOrientation(q);
		rb->setRotation(Vecteur3D("petit"));
		Matrix34 tr;
		tr.setOrientationAndPosition(q, rb->getPosition());
		rb->setTransformMatrix(tr);

		cout << "Mass : " << 1.0f/rb->getInverseMass() << endl;

		GravityGenerator* rggravity = new GravityGenerator();
		DragForceGenerator* rgdrag = new DragForceGenerator();
		rigidRegistry->my_RigidRegistry.push_back({ rb,rggravity });
		rigidRegistry->my_RigidRegistry.push_back({ rb,rgdrag });
		listRigidBodies.push_back(rb);
	}
	else {
		SphereRigidBody* rb = new SphereRigidBody();
		rb->setLinearDamping(0.95);
		rb->setAngularDamping(0.5);
		rb->setPosition(Vecteur3D("random"));
		rb->setVelocity(Vecteur3D("random"));
		rb->setForceAccum(Vecteur3D(0, 0, 0));
		rb->setTorqueAccum(Vecteur3D(0, 0, 0));
		float mass = rand() % 5 + 10;
		rb->setInverseMass(1 / mass);
		rb->setRadius(rand() % 30 + 10);
		Quaternion q = Quaternion(1, 0, 0, 0);
		q.Normalized();
		rb->setOrientation(q);
		rb->setRotation(Vecteur3D("petit"));
		Matrix34 tr;
		tr.setOrientationAndPosition(q, rb->getPosition());
		rb->setTransformMatrix(tr);

		cout << "Mass : " << 1.0f/rb->getInverseMass() << endl;

		GravityGenerator* rggravity = new GravityGenerator();
		DragForceGenerator* rgdrag = new DragForceGenerator();
		rigidRegistry->my_RigidRegistry.push_back({ rb,rggravity });
		rigidRegistry->my_RigidRegistry.push_back({ rb,rgdrag });
		listRigidBodies.push_back(rb);
	}

	

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

	if (key == OF_KEY_DOWN) {
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

	/*if (key == 'r') {
		restartButtonPressed();
	}*/

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

