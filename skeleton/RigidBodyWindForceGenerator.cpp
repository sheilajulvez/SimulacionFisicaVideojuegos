#include "RigidBodyWindForceGenerator.h"
RigidBodyWindForceGenerator::RigidBodyWindForceGenerator(Vector3 f, Vector3 ini_pos, Vector3 tam, const float k1, const float k2) {
	_k1 = k1;
	_k2 = k2;
	this->f = f;
	this->ini_pos = ini_pos;
	this->longitud = tam;
}
RigidBodyWindForceGenerator::~RigidBodyWindForceGenerator() {



}
void RigidBodyWindForceGenerator::updateForce(RigidBodyParticle* particle, double t) {
	Vector3 pos = particle->getTrans().p;

	if ((pos.x >= ini_pos.x && pos.x <= ini_pos.x + longitud.x)
		&& (pos.y >= ini_pos.y && pos.y <= ini_pos.y + longitud.y)
		&& (pos.z >= ini_pos.z && pos.z <= ini_pos.z + longitud.z)) {

		Vector3 vel_result = (Vector3( f.x + particle->dinamico()->getLinearVelocity().x,
			0,f.z + particle->dinamico()->getLinearVelocity().z ));
		//compute drag force
		Vector3 dragF = _k1 * vel_result + _k2 * vel_result * vel_result.magnitude();
		particle->addForce(dragF);
	}
	else return;
}