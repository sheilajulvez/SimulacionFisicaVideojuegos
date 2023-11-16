#include "WhirlwindForceGenerator.h"
WhirlwindForceGenerator::WhirlwindForceGenerator(Vector3 f, Vector3 ini_pos, Vector3 tam, const float k1, const float k2):WindForceGenerator(f,ini_pos,tam,k1,0) {
	

}
WhirlwindForceGenerator::~WhirlwindForceGenerator() {

}
void WhirlwindForceGenerator::updateForce(Particle* particle, double t) {
	Vector3 position = particle->getTrans().p;
	//if (fabs(1 / particle->getMasa()) < 1e-10) return;

	Vector3 Velocity_WhirlWind = _k1 * Vector3(
		-(position.z - ini_pos.z), 
		50- (position.y - ini_pos.y/2), 
		(position.x - ini_pos.x));

	Vector3 Velocity = particle->getVel() - Velocity_WhirlWind;
	float drag_coef = Velocity.normalize();
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	Vector3 forces = -Velocity * drag_coef;

	particle->addForce(forces);
}