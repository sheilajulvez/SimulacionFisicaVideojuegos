#include "RigidBodyForceRegistry.h"

void RigidBodyForceRegistry::updateForces(double duration) {
    for (auto it = begin(); it != end(); ++it) {
        it->first->updateForce(it->second, duration);
    }
}

void RigidBodyForceRegistry::addRegistry(RigidBodyForceGenerator* fg, RigidBodyParticle* rb) {
    insert({ fg, rb });
}

void RigidBodyForceRegistry::deleteRegistry(RigidBodyForceGenerator* fg, RigidBodyParticle* rb) {

}

void RigidBodyForceRegistry::deleteParticleRegistry(RigidBodyParticle* rb) {

}