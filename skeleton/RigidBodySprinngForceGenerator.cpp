#include "RigidBodySprinngForceGenerator.h"
RigidBodySprinngForceGenerator::RigidBodySprinngForceGenerator(double k, double resting_length, RigidBodyParticle* other, Vector3 pos) {
	_k = k;
	_resting_length = resting_length;
	_other = other;
	this->pos = pos;
}
void RigidBodySprinngForceGenerator::updateForce(RigidBodyParticle* particle, double t) {
	particle->dinamico()->setGlobalPose({ pos.x,pos.y,particle->getTrans().p.z });
	
	// Particle is the particle to apply the force
	Vector3 relative_pos_vector = (_other->estatico()->getGlobalPose().p - particle->dinamico()->getGlobalPose().p);
	Vector3 force;

	// normalize: Normalize the relative_pos_vector and returns its length.
	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _resting_length;

	force = relative_pos_vector *- delta_x * _k;

	particle->addForce(force);
	

}
RigidBodySprinngForceGenerator::~RigidBodySprinngForceGenerator() {

}