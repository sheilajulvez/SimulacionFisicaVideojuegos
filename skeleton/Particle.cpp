#include "Particle.h"
Particle::Particle(Vector3 pos, Vector3 vel) {
	this->vel = vel;
	trans.p = pos;
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(10)),&trans, Vector4{ 255,0,255,1 });
	RegisterRenderItem(renderItem);
}
Particle::~Particle() {
	DeregisterRenderItem(renderItem);

}
void Particle::integrate(double t) {
	trans.p += vel;

}