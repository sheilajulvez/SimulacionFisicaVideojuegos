#include "GravityFocreGenerator.h"
GravityForceGenerator::GravityForceGenerator(const Vector3& g) {
    gravity = g;
}
GravityForceGenerator::~GravityForceGenerator() {

}

void GravityForceGenerator::updateForce(Particle* p, double t) {
    p->addForce(gravity * p->getMasa());
}
void GravityForceGenerator::setGravity(const Vector3& g) {
    gravity = g;
}