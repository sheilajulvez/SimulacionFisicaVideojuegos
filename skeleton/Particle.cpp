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
}
Particle::~Particle() {
	DeregisterRenderItem(renderItem);

}
void Particle::integrate(double t) {
	timer += t;
	vel += acelera * t;
	vel *= pow(damping, t);
	trans.p += vel * t;
	if (timer > time) muere = true;


	/*if (timer >= time) return true;
	else return false;*/

}

