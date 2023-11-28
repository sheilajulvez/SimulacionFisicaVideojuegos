#include "SpringForceGenerator.h"
SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other) {
	_k = k;
	_resting_length = resting_length;
	_other = other;
}
void SpringForceGenerator::updateForce(Particle* particle, double t) {


		// Particle is the particle to apply the force
		Vector3 relative_pos_vector = (_other->getTrans().p - particle->getTrans().p);
		Vector3 force;

		// normalize: Normalize the relative_pos_vector and returns its length.
		const float length = relative_pos_vector.normalize();
		const float delta_x = length - _resting_length;

		force = relative_pos_vector * delta_x * _k;

		particle->addForce(force);
	
	
}
SpringForceGenerator::~SpringForceGenerator() {

}