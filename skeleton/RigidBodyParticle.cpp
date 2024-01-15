#include "RigidBodyParticle.h"

RigidBodyParticle::RigidBodyParticle(PxPhysics* gPhysics_, PxScene* gScene_, RenderItem* rItem_, PxRigidDynamic* dynamico) {
	gPhysicsRB = gPhysics_;
	gSceneRB = gScene_;
	rItem = rItem_;
	dynamicRB = dynamico;
}

RigidBodyParticle::RigidBodyParticle(PxPhysics* gPhysics_, PxScene* gScene_, RenderItem* rItem_, PxRigidStatic* statico) {
	gPhysicsRB = gPhysics_;
	gSceneRB = gScene_;
	rItem = rItem_;
	staticRB = statico;
}

void RigidBodyParticle::integrate(double t) {
	time += t;
	if (timeOfLife < time) death = true;
	if (dynamicRB != nullptr && dynamicRB->getGlobalPose().p.y > 10) {
		dynamicRB->setGlobalPose({ dynamicRB->getGlobalPose().p.x,10, dynamicRB->getGlobalPose().p.z });
	}
}

void RigidBodyParticle::addForce(Vector3 f) {
	if (dynamicRB != nullptr) {
		dynamicRB->addForce(f);
	}
}
void RigidBodyParticle::addForceLinear(Vector3 f) {
	if (dynamicRB != nullptr) {
		dynamicRB->setLinearVelocity(f);
	}
}

void RigidBodyParticle::clearForce() {
	if (dynamicRB != nullptr) {
		dynamicRB->clearForce();
	}
}
float RigidBodyParticle::getInvMss() {
	if (dynamicRB != nullptr) {
		return dynamicRB->getInvMass();
	}
}


Vector3 RigidBodyParticle::getDir() {
	if (dynamicRB != nullptr) {
		return dynamicRB->getLinearVelocity();
	}
}