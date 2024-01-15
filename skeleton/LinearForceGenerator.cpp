#include "LinearForceGenerator.h"
LinearForceGenerator::LinearForceGenerator() {
	dir = { 0,0,0 };
}
LinearForceGenerator:: ~LinearForceGenerator() {

}
void LinearForceGenerator::updateForce(RigidBodyParticle* rb, double duration) {
	rb->addForceLinear(dir);
}