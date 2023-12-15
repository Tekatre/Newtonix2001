#include "ofApp.h"




void ofApp::initializeParticles() {
	gravite = Vecteur3D(0, -9.8, 0);
	ParticleGravity* Pgravity = new ParticleGravity();
	ParticleDrag* Pdrag = new ParticleDrag();
	//Collisions classiques entre deux particules
	//*numberOfParticles = 0;


	//Particule* p1 = new Particule(numberOfParticles,Vecteur3D(50, 0, 0), Vecteur3D(-70, 70, 0), Vecteur3D(0, 0, 0), 10, 1, ofColor::blue);
	//Particule* p2 = new Particule(numberOfParticles,Vecteur3D(0, 0, 0), Vecteur3D(70, 70, 0), Vecteur3D(0, 0, 0), 10, 1, ofColor::blue);
	//Particule* p3 = new Particule(numberOfParticles,Vecteur3D(0, 0, 100), Vecteur3D(70, 30, 0), Vecteur3D(0, 0, 0), 10, 1, ofColor::yellow); //spring avec p4
	//Particule* p4 = new Particule(numberOfParticles,Vecteur3D(0, 0, 150), Vecteur3D(-70, -20, 0), Vecteur3D(0, 0, 0), 10, 1, ofColor::yellow); //spring avec p3
	//Particule* p5 = new Particule(numberOfParticles,Vecteur3D(-50, 0, 0), Vecteur3D(30, 70, 0), Vecteur3D(0, 0, 0), 10, 1, ofColor::blue); //anchor en 0 0 0

	//Particule* p6 = new Particule(numberOfParticles,Vecteur3D(-30, 0, -100), Vecteur3D(-70, 40, 0), Vecteur3D(0, 0, 0), 10, 1, ofColor::red);
	//Particule* p7 = new Particule(numberOfParticles,Vecteur3D(30, 0, -100), Vecteur3D(60, 80, 0), Vecteur3D(0, 0, 0), 10, 1, ofColor::red);

	//Particule* p8 = new Particule(numberOfParticles,Vecteur3D(-30, 0, -150), Vecteur3D(-70, 30, 0), Vecteur3D(0, 0, 0), 10, 1, ofColor::purple);
	//Particule* p9 = new Particule(numberOfParticles,Vecteur3D(30, 0, -150), Vecteur3D(60, 100, 0), Vecteur3D(0, 0, 0), 10, 1, ofColor::purple);
	//


	//ParticleCable* cable = new ParticleCable();

	//cable->particle[0] = p6;
	//cable->particle[1] = p7;
	//cable->maxLength = 200;
	//cable->restitution = 0.5;
	//cables[numberOfCables] = cable;
	//numberOfCables++;

	//ParticleRod* rod = new ParticleRod();
	//rod->particle[0] = p8;
	//rod->particle[1] = p9;
	//rod->length = 60;
	//rods[numberOfRods]=rod;
	//numberOfRods++;




	//ParticleSpring* Pspring4 = new ParticleSpring(p4, 1, 30);
	//ParticleSpring* Pspring3 = new ParticleSpring(p3, 1, 30);
	//ParticleSpring* Pspring8 = new ParticleSpring(p8, 1, 50);
	//ParticleSpring* Pspring7 = new ParticleSpring(p7, 1, 50);
	//ParticleAnchorSpring* anchor = new ParticleAnchorSpring(Vecteur3D(0, 0, 0), 1, 60);

	//registry->my_registry.push_back({p1,Pgravity});
	//registry->my_registry.push_back({ p1,Pdrag });
	//registry->my_registry.push_back({ p2,Pgravity });
	//registry->my_registry.push_back({ p3,Pgravity });
	//registry->my_registry.push_back({ p4,Pgravity });
	//registry->my_registry.push_back({ p3,Pspring4 });
	//registry->my_registry.push_back({ p4,Pspring3 });
	//registry->my_registry.push_back({ p5,Pgravity });
	//registry->my_registry.push_back({ p5,Pdrag });
	//registry->my_registry.push_back({ p5,anchor });
	//registry->my_registry.push_back({ p6,Pgravity });
	//registry->my_registry.push_back({ p7,Pgravity });
	//registry->my_registry.push_back({ p7,Pspring8 });
	//registry->my_registry.push_back({ p8, Pgravity });
	//registry->my_registry.push_back({ p8, Pspring7 });
	//registry->my_registry.push_back({ p9, Pgravity });



	//listParticules.push_back(p1);
	//listParticules.push_back(p2);
	//listParticules.push_back(p3);
	//listParticules.push_back(p4);
	//listParticules.push_back(p5);
	//listParticules.push_back(p6);
	//listParticules.push_back(p7);
	//listParticules.push_back(p8);
	//listParticules.push_back(p9);
	////listParticules.push_back(p10);
	////listParticules.push_back(p11);

	//
	//trails.push_back(*p1);
	//trails.push_back(*p2);
	//trails.push_back(*p3);
	//trails.push_back(*p4);
	//trails.push_back(*p5);
	//trails.push_back(*p6);
	//trails.push_back(*p7);
	//trails.push_back(*p8);
	//trails.push_back(*p9);
	////trails.push_back(p10)
	////trails.push_back(p11);


	BoxRigidBody * rb1 = new BoxRigidBody();
	rb1->setLinearDamping(0.95);
	rb1->setAngularDamping(0.5);
	rb1->setPosition(Vecteur3D(-100, 0, 0));
	rb1->setVelocity(Vecteur3D(0, 0, 0));
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

	Particule* particuletest = new Particule(numberOfParticles,Vecteur3D(-75,0,0), Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0),10, 1, ofColor::yellow);
	listParticules.push_back(particuletest);
	GravityGenerator* rggravity = new GravityGenerator();
	AnchorForceGenerator* anchorForce = new AnchorForceGenerator(Vecteur3D(0, 0, 0), Vecteur3D(25,0,0), 1, 50);
	DragForceGenerator* dragForce = new DragForceGenerator();
	rigidRegistry->my_RigidRegistry.push_back({ rb1,rggravity });
	//rigidRegistry->my_RigidRegistry.push_back({ rb1,dragForce });
	//rigidRegistry->my_RigidRegistry.push_back({ rb1,anchorForce });

	




	BoxRigidBody* rb2 = new BoxRigidBody();
	rb2->setInverseMass(1);
	rb2->setLinearDamping(0.95);
	rb2->setAngularDamping(0.5);
	rb2->setPosition(Vecteur3D(-100, 0, 30));
	rb2->setVelocity(Vecteur3D(50, 50, 0));
	rb2->setForceAccum(Vecteur3D(0, 0, 0));
	rb2->setTorqueAccum(Vecteur3D(0, 0, 0));
	rb2->setInverseMass(1);
	rb2->setDepth(50);
	rb2->setHeight(50);
	rb2->setWidth(50);
	Quaternion q2 = Quaternion(1, 0, 0, 0);
	q2.Normalized();
	rb2->setOrientation(q2);
	rb2->setRotation(Vecteur3D(0, 0, 0));
	tr.setOrientationAndPosition(q2, rb2->getPosition());
	rb2->setTransformMatrix(tr);

	rigidRegistry->my_RigidRegistry.push_back({ rb2,rggravity });
	
	BoxRigidBody* rb3 = new BoxRigidBody();
	rb3->setInverseMass(1);
	rb3->setLinearDamping(0.95);
	rb3->setAngularDamping(0.5);
	rb3->setPosition(Vecteur3D(100, 50, 100));
	rb3->setVelocity(Vecteur3D(50, 70, 0));
	rb3->setForceAccum(Vecteur3D(0, 0, 0));
	rb3->setTorqueAccum(Vecteur3D(0, 0, 0));
	rb3->setInverseMass(1);
	rb3->setDepth(50);
	rb3->setHeight(50);
	rb3->setWidth(50);
	Quaternion q3 = Quaternion(1, 0, 0, 0);
	q3.Normalized();
	rb3->setOrientation(q3);
	rb3->setRotation(Vecteur3D(0, 0, 0));
	tr.setOrientationAndPosition(q3, rb3->getPosition());
	rb3->setTransformMatrix(tr);

	
	rigidRegistry->my_RigidRegistry.push_back({ rb3,rggravity });



	BoxRigidBody* rb4 = new BoxRigidBody();
	rb4->setLinearDamping(0.95);
	rb4->setAngularDamping(0.5);
	rb4->setPosition(Vecteur3D(100, 50, 50));
	rb4->setVelocity(Vecteur3D(50, 50, 0));
	rb4->setForceAccum(Vecteur3D(0, 0, 0));
	rb4->setTorqueAccum(Vecteur3D(0, 0, 0));
	rb4->setInverseMass(1);
	rb4->setDepth(50);
	rb4->setHeight(50);
	rb4->setWidth(50);
	Quaternion q4 = Quaternion(1, 0, 0, 0);
	q4.Normalized();
	rb4->setOrientation(q4);
	rb4->setRotation(Vecteur3D(0, 0, 0));
	tr.setOrientationAndPosition(q4, rb4->getPosition());
	rb4->setTransformMatrix(tr);


	rigidRegistry->my_RigidRegistry.push_back({ rb4,rggravity });

	/*
	BoxRigidBody* rb5 = new BoxRigidBody();
	rb5->setLinearDamping(0.95);
	rb5->setAngularDamping(0.5);
	rb5->setPosition(Vecteur3D(0, 0, -200));
	rb5->setVelocity(Vecteur3D(50, 50, 0));
	rb5->setForceAccum(Vecteur3D(0, 0, 0));
	rb5->setTorqueAccum(Vecteur3D(0, 0, 0));
	rb5->setInverseMass(1);
	rb5->setDepth(50);
	rb5->setHeight(50);
	rb5->setWidth(50);
	Quaternion q5 = Quaternion(1, 0, 0, 0);
	q5.Normalized();
	rb5->setOrientation(q5);
	rb5->setRotation(Vecteur3D(0, 0, 0));
	rb5->setTransformMatrix(Matrix34());
	tr.setOrientationAndPosition(q5, rb5->getPosition());
	rb5->setTransformMatrix(tr);


	rigidRegistry->my_RigidRegistry.push_back({ rb5,rggravity });
	rigidRegistry->my_RigidRegistry.push_back({ rb5,dragForce });*/
	
	//anchorsLinkRigid.push_back({ rb1,Vecteur3D(0,0,0) });
	listRigidBodies.push_back(rb1);
	listRigidBodies.push_back(rb2);

	listRigidBodies.push_back(rb3);
	listRigidBodies.push_back(rb4);
	//listRigidBodies.push_back(rb5);

	
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
	t = ofGetLastFrameTime();

	//cout << "Number of particles : " << listParticules.size() << endl;


	registry->updateForces(t);
	rigidRegistry->updateForces(t);
	particulesAnchor.clear();
	for each ( auto ele in rigidRegistry->my_RigidRegistry)
	{
		RigidBody*rb = ele.rigidBody;
		Vecteur3D bdAnchor = ele.fg->getBodyAnchor();
		//si bdAnchor n'est pas null
		if (bdAnchor.getX() == NULL) {
			Particule p = Particule(numberOfParticles, rb->getTransformMatrix()*bdAnchor, Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0), 5, 1, ofColor::yellow);
			particulesAnchor.push_back(p);
		}
	}
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
	rigidResolver->resolveContacts(rigidContacts, numberOfRigidContacts, t);
	







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

		if (static_cast<BoxRigidBody*>(listRigidBodies[i])) {
			BoxRigidBody* box = static_cast<BoxRigidBody*>(listRigidBodies[i]);
			ofBoxPrimitive boxPrimitive;
			boxPrimitive.setHeight(box->getHeight());
			boxPrimitive.setWidth(box->getWidth());
			boxPrimitive.setDepth(box->getDepth());
			boxPrimitive.setPosition(box->getPosition().getX(), box->getPosition().getY(), box->getPosition().getZ());
			boxPrimitive.setOrientation(glm::quat(box->getOrientation().getW(), box->getOrientation().getX(), box->getOrientation().getY(), box->getOrientation().getZ()));
			boxPrimitive.draw();
		}
		/*else if (static_cast<SphereRigidBody*>(listRigidBodies[i])) {
			SphereRigidBody* sphere = static_cast<SphereRigidBody*>(listRigidBodies[i]);
			ofSpherePrimitive spherePrimitive;
			spherePrimitive.setRadius(sphere->getOuterRadius());
			spherePrimitive.setPosition(sphere->getPosition().getX(), sphere->getPosition().getY(), sphere->getPosition().getZ());
			spherePrimitive.setOrientation(glm::quat(sphere->getOrientation().getW(), sphere->getOrientation().getX(), sphere->getOrientation().getY(), sphere->getOrientation().getZ()));
			spherePrimitive.draw();
		}
		else if (static_cast<CylinderRigidBody*>(listRigidBodies[i])) {
			CylinderRigidBody* cylinder = static_cast<CylinderRigidBody*>(listRigidBodies[i]);
			ofCylinderPrimitive cylinderPrimitive;
			cylinderPrimitive.setResolution(50, 50, 50);
			cylinderPrimitive.setRadius(cylinder->getOuterRadius());
			cylinderPrimitive.setHeight(cylinder->getHeight());
			cylinderPrimitive.setResolutionCap(50);
			cylinderPrimitive.setPosition(cylinder->getPosition().getX(), cylinder->getPosition().getY(), cylinder->getPosition().getZ());
			cylinderPrimitive.setOrientation(glm::quat(cylinder->getOrientation().getW(), cylinder->getOrientation().getX(), cylinder->getOrientation().getY(), cylinder->getOrientation().getZ()));
			cylinderPrimitive.draw();
		}*/
		else {
			//do nothing
		}



		/*if (listRigidBodies[i]->getShape() == 1) {
			ofBoxPrimitive box;
			box.setHeight(50);
			box.setWidth(50);
			box.setDepth(50);
			box.setPosition(listRigidBodies[i]->getPosition().getX(), listRigidBodies[i]->getPosition().getY(), listRigidBodies[i]->getPosition().getZ());
			box.setOrientation(glm::quat(listRigidBodies[i]->getOrientation().getW(), listRigidBodies[i]->getOrientation().getX(), listRigidBodies[i]->getOrientation().getY(), listRigidBodies[i]->getOrientation().getZ()));
			box.draw();
		}
		else if (listRigidBodies[i]->getShape() == 2) {
			ofCylinderPrimitive cylindre;
			cylindre.setResolution(50, 50, 50);

			cylindre.setRadius(50);
			cylindre.setHeight(50);
			cylindre.setResolutionCap(50);
			cylindre.setPosition(listRigidBodies[i]->getPosition().getX(), listRigidBodies[i]->getPosition().getY(), listRigidBodies[i]->getPosition().getZ());
			cylindre.setOrientation(glm::quat(listRigidBodies[i]->getOrientation().getW(), listRigidBodies[i]->getOrientation().getX(), listRigidBodies[i]->getOrientation().getY(), listRigidBodies[i]->getOrientation().getZ()));
			cylindre.draw();
		}
		else {
			ofSpherePrimitive sphere;
			sphere.setRadius(50);
			sphere.setPosition(listRigidBodies[i]->getPosition().getX(), listRigidBodies[i]->getPosition().getY(), listRigidBodies[i]->getPosition().getZ());
			sphere.setOrientation(glm::quat(listRigidBodies[i]->getOrientation().getW(), listRigidBodies[i]->getOrientation().getX(), listRigidBodies[i]->getOrientation().getY(), listRigidBodies[i]->getOrientation().getZ()));
			sphere.draw();
		}*/


		
		
		

		
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	//quand on appuie sur espace, mets un pause la boucle
	if (key == ' ') {
		paused = !paused;
	}


	if (key == OF_KEY_UP) {
		for (int i = 0; i < listParticules.size(); i++) {
			listParticules[i]->setVelocite(listParticules[i]->getVelocite() + Vecteur3D(0, 50, 0));
		}
	}

	if (key == OF_KEY_DOWN) {
		for (int i = 0; i < listParticules.size(); i++) {
			listParticules[i]->setVelocite(listParticules[i]->getVelocite() + Vecteur3D(0, -50, 0));
		}
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

