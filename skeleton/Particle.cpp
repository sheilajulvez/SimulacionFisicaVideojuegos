#include "Particle.h"
Particle::Particle(Vector3 pos, Vector3 vel, Vector3 aceler, int mas, Vector4 color):trans(pos) {
	this->vel = vel;
	//trans.p = pos;
	masa = mas;
	acelera = aceler;
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(10)), &trans, color);
}
Particle::~Particle() {
	DeregisterRenderItem(renderItem);

}
void Particle::integrate(double t) {
	timer += t;
	vel += acelera * t;
	vel *= pow(damping, t);
	trans.p += vel * t;

}

float Particle::gettimer() {
	return timer;
}