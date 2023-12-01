#include "Particle.h"
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 acelera, int mas, Vector4 color, float timer, int payload, float radio):trans(Pos) {
	this->vel = Vel;
	this->acelera = acelera;
	masa = mas;
	this->acelera = acelera;
	this->color = color;
	this->time = timer;
	this->payload = payload;
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(radio)), &trans, color);
	muere = false;
	force = { 0,0,0 };
}
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 acelera, int mas, Vector4 color, float timer, int payload, Vector3 tam):trans(Pos) {
	this->vel = Vel;
	this->acelera = acelera;
	masa = mas;
	this->acelera = acelera;
	this->color = color;
	this->time = timer;
	this->payload = payload;
	renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(tam)), &trans, color);
	muere = false;
	force = { 0,0,0 };
}
Particle::~Particle() {
	DeregisterRenderItem(renderItem);

}
void Particle::integrate(double t) {
	/*timer += t;
	vel += acelera * t;
	vel *= pow(damping, t);
	trans.p += vel * t;
	if (timer > time) muere = true;*/


	// Semi-implicit Euler algorithm
	
// Get the accel considering the force accum
	Vector3 resulting_accel = force * masa;			//CORREGIR POR INVERSO DE LA MASA
	vel += resulting_accel * t; // Ex. 1.3 --> add acceleration
	vel *= powf(damping, t); // Exercise 1.3 --> adddamping
	trans.p += vel * t;
	timer += t;
	// Clear accum
	clearForce();
	if (timer >time) muere = true;


	/*if (timer >= time) return true;
	else return false;*/

}

// Clears accumulated force
void Particle::addForce(Vector3 f) {
	force += f;
}

// Add force to apply in next integration only
void Particle::clearForce() {
	force *= 0.0;
}



